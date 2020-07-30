//
// Created by denis on 10.07.20.
//

#include "TaskService.h"

TaskCreationResult TaskService::addTask(const TaskDTO &user_data) {
    Task ptask = task_creator_->createTask(user_data);
    auto created_node = task_tree_->createNodeAndAddToRoot(ptask);
    by_priority_->addToView(created_node);
    // extract and return id_ of the node
    return TaskCreationResult::success(created_node.lock()->getId());
}

TaskCreationResult TaskService::addSubTask(TaskID id_parent, const TaskDTO &user_data) {
    if (!task_tree_->getNodeById(id_parent)) {
        return TaskCreationResult::taskNotFound();
    }
    Task ptask = task_creator_->createTask(user_data);
    auto created_node = task_tree_
                        ->createSubNode(id_parent,
                                        ptask);
    by_priority_->addToView(created_node);
    // extract and return id_ of the node
    return TaskCreationResult::success(created_node.lock()->getId());
}

void TaskService::deleteTask(TaskID id_task) {
    task_tree_->eraseNode(id_task);
}

std::vector<TaskDTO> TaskService::getAllTasks() {
    auto result_set = by_priority_->getAll(std::numeric_limits<time_t>::max());
    std::vector<TaskDTO> user_result_set;
    std::transform(result_set.begin(), result_set.end(),
                    std::back_inserter(user_result_set),
                    [this] (std::weak_ptr<TaskNode> p_node) {
                        auto pnode_access = p_node.lock();
                        TaskID id_task = pnode_access->getId();
                        return TaskDTO(id_task, pnode_access->getTask());
                    }
                   );
    return user_result_set;
}

TaskDTO TaskService::getTaskBySystemID(TaskID id_task) {
    auto p_node = task_tree_->getNodeById(id_task);
    return TaskDTO(p_node->getId(),
                   p_node->getTask());
}

TaskDTO TaskService::getTaskByID(TaskID id_task) {
    return getTaskBySystemID(id_task);
}


void TaskService::postponeTask(TaskID id_task, time_t date_postpone) {
    TaskDTO task_data = getTaskByID(id_task);
    TaskID system_id_task = id_task;
    task_tree_->modifyTaskData(system_id_task,
                               task_creator_->createPostponedTask(task_data, date_postpone));
    by_priority_->addToView(task_tree_->getNodeById(system_id_task));
}




