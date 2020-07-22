//
// Created by denis on 10.07.20.
//

#include "TaskService.h"

UserTaskID TaskService::addTask(const std::string &name, Task::Priority priority, const std::string &label, time_t date) {
    Task ptask = task_creator_.createTask(name, priority, label, date);
    auto created_node = task_tree_.createNodeAndAddToRoot(ptask);
    by_priority_.addToView(created_node);
    // extract and return id_ of the node
    TaskID created_id = created_node.lock()->getId();
    return id_converter_.getUserTaskID(created_id);
}

UserTaskID TaskService::addSubTask(UserTaskID id_parent, const std::string &name, Task::Priority priority, const std::string &label, time_t date) {
    Task ptask = task_creator_.createTask(name, priority, label, date);
    auto created_node = task_tree_
                        .createSubNode(id_converter_.getTaskID(id_parent),
                                        ptask);
    by_priority_.addToView(created_node);
    // extract and return id_ of the node
    TaskID created_id = created_node.lock()->getId();
    return id_converter_.getUserTaskID(created_id);
}

void TaskService::deleteTask(TaskID id_task) {
    task_tree_.eraseNode(id_task);
}

std::vector<TaskDTO> TaskService::getAllTasks() {
    auto result_set = by_priority_.getAllToDate(std::numeric_limits<time_t>::max());
    std::vector<TaskDTO> user_result_set;
    std::transform(result_set.begin(), result_set.end(),
                    std::back_inserter(user_result_set),
                    [this] (std::weak_ptr<TaskNode> p_node) {
                        auto pnode_access = p_node.lock();
                        UserTaskID id_for_user = id_converter_
                                                    .getUserTaskID(pnode_access->getId());
                        return TaskDTO(id_for_user, pnode_access->getTask());
                    }
                   );
    return user_result_set;
}

