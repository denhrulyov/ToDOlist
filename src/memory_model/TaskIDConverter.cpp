//
// Created by denis on 20.07.20.
//

#include "TaskIDConverter.h"

bool prev_by_date(const TaskNode& lhs, const TaskNode& rhs) {
    return  (lhs.getTask().date < rhs.getTask().date) ||
            (lhs.getTask().date < rhs.getTask().date && lhs.getId() < rhs.getId());
}

std::size_t find_order_of_node_by_date(std::shared_ptr<TaskNode> node) {
    auto parent = node->getParent();
    std::size_t less = 0;
    for (auto id : parent->getSubtasks()) {
        if (prev_by_date(*parent->getSubtaskByID(id), *node)) {
            less++;
        }
    }
    return less + 1;
}

TaskID TaskIDConverter::getTaskID(UserTaskID user_id) {
    auto cur_node = ref_tree_.getRoot();
    for (auto level_id : user_id.getLevelIndices()) {
        cur_node = cur_node->getNthByDate(level_id);
    }
    return cur_node->getId();
}

UserTaskID TaskIDConverter::getUserTaskID(TaskID system_id) {
    std::vector<std::size_t> level_indcies;
    auto cur_node = ref_tree_.getNodeById(system_id);
    while (cur_node->getParent()) {
        level_indcies.push_back(find_order_of_node_by_date(cur_node));
        cur_node = cur_node->getParent();
    }
    return UserTaskID(level_indcies);
}
