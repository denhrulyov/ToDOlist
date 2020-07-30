//
// Created by denis on 10.07.20.
//

#include "TaskService.h"

TaskCreationResult TaskService::addTask(const TaskDTO &task_data) {
    Task task = task_creator_->createTask(task_data);
    TaskID generated_id = id_generator_->generateID();
    auto created_node = std::make_shared<TaskNode>(generated_id, task);
    // set links to new node
    nodes_[generated_id] = created_node;
    by_time_->addToView(created_node);

    return TaskCreationResult::success(generated_id);
}

TaskCreationResult TaskService::addSubTask(TaskID parent, const TaskDTO &task_data) {
    if (nodes_.count(parent) == 0) {
        return TaskCreationResult::taskNotFound();
    }
    // create Node
    auto result = addTask(task_data);
    TaskID generated_id = result.getCreatedTaskID().value();
    // tie new node with parent
    auto created_node = nodes_[generated_id];
    auto parent_node = nodes_[parent];
    parent_node->addSubtask(created_node);
    created_node->setParent(parent_node);

    return TaskCreationResult::success(generated_id);
}

void TaskService::deleteTask(TaskID id) {
    for (TaskID subtask : nodes_[id]->getSubtasks()) {
        deleteTask(subtask);
    }
    eraseAllReferences(id);
}

std::vector<TaskDTO> TaskService::getAllTasks() {
    auto result_set = by_time_->getAll(std::numeric_limits<time_t>::max());
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

TaskDTO TaskService::getTaskByID(TaskID id) {
    return TaskDTO(id, nodes_[id]->getTask());
}


void TaskService::postponeTask(TaskID id, time_t date_postpone) {
    auto old_node = nodes_[id];
    auto modified_node =
            std::make_shared<TaskNode>(
                    id,
                    task_creator_->createPostponedTask(old_node->getTask(), date_postpone)
                    );
    for (auto subnode : nodes_[id]->getSubNodes()) {
        modified_node->addSubtask(subnode);
        subnode->setParent(modified_node);
    }
    eraseAllReferences(id);
    nodes_[id] = modified_node;
    by_time_->addToView(modified_node);
}

void TaskService::eraseAllReferences(TaskID id) {
    auto parent = nodes_[id]->getParent();
    if (parent) {
        parent->eraseSubtask(id);
    }
    nodes_.erase(id);
    by_time_->removeFromView(id);
}


