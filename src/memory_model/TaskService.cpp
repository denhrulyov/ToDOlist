//
// Created by denis on 10.07.20.
//

#include "TaskService.h"

TaskID TaskService::addTask(const std::string &name, Task::Priority priority, const std::string &label, time_t date) {
    Task ptask = task_creator_.createTask(name, priority, label, date);
    auto created_node = task_tree_.createNodeAndAddToRoot(ptask);
    by_priority_.addToView(created_node);
    // extract and return id_ of the node
    TaskID created_id = created_node.lock()->getId();
    return created_id;
}

TaskID TaskService::addSubTask(TaskID id_parent, const std::string &name, Task::Priority priority, const std::string &label, time_t date) {
    Task ptask = task_creator_.createTask(name, priority, label, date);
    auto created_node = task_tree_.createSubNode(id_parent, ptask);
    by_priority_.addToView(created_node);
    // extract and return id_ of the node
    TaskID created_id = created_node.lock()->getId();
    return created_id;
}

void TaskService::popTask(TaskID id_task) {
    task_tree_.eraseNode(id_task);
}

std::vector<TaskDTO> TaskService::getAllTasks() {
    auto result_set = by_priority_.getAllToDate(std::numeric_limits<time_t>::max());
    std::vector<TaskDTO> user_result_set;
    std::transform(result_set.begin(), result_set.end(),
                    std::back_inserter(user_result_set),
                    [] (std::weak_ptr<TaskNode> p_node) {
                        auto pnode_access = p_node.lock();
                        return TaskDTO(pnode_access->getId(), pnode_access->getTask());
                    }
                   );
    return user_result_set;
}

