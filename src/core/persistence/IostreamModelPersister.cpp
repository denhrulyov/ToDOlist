//
// Created by denis on 30.09.20.
//

#include "IostreamModelPersister.h"
#include "core/memory_model/view/DatePriorityView.h"
#include "core/memory_model/view/TagPriorityView.h"
#include "core/memory_model/data/TaskStorage.h"
#include "core/memory_model/structure/LinkManager.h"
#include "core/memory_model/api/TaskRespository.h"
#include "core/persistence/ProtoConvert.h"


IostreamModelPersister::IostreamModelPersister(
        TaskRepositoryInterface &model,
        std::shared_ptr<std::iostream> stream)
        :
        model_(model),
        stream_(stream)
        {}

bool IostreamModelPersister::WriteTaskToTaskMessage(const TaskDTO& task, TaskMessage* message) {
    message->set_allocated_task(new TaskData);
    proto_convert::WriteToMessage(task, message->mutable_task());
    for (const auto& subtask : model_.getSubTasks(task.getId())) {
        TaskMessage* subtask_dump = message->add_subtasks();
        if (!WriteTaskToTaskMessage(subtask, subtask_dump)) {
            return false;
        }
    }
    return true;
}

bool IostreamModelPersister::Save() {
    TaskModelMessage assembled_model_message;
    for (const auto& task : model_.getAllTasks()) {
        if (!model_.getParentTask(task.getId())) {
            TaskMessage* assembled_task_message = assembled_model_message.add_tasks();
            if (!WriteTaskToTaskMessage(task, assembled_task_message)) {
                return false;
            }
        }
    }
    return assembled_model_message.SerializeToOstream(stream_.get());
}

bool IostreamModelPersister::RestoreTaskByMessage(TaskID id, const TaskMessage& message) {
    for (const TaskMessage& subtask_load : message.subtasks()) {
        TaskDTO subtask = proto_convert::RestoreFromMessage(subtask_load.task());
        TaskCreationResult result = model_.addSubTask(id, subtask);
        if (!result.getCreatedTaskID()) {
            return false;
        }
        TaskID id_subtask = result.getCreatedTaskID().value();
        if (!RestoreTaskByMessage(id_subtask, subtask_load)) {
            // failed to deserialize subtasks hierarchy at any point
            return false;
        }
    }
    // all is OK
    return true;
}

bool IostreamModelPersister::Load() {
    TaskModelMessage loaded_model;
    if (!loaded_model.ParseFromIstream(stream_.get())) {
        return false;
    }
    for (const TaskMessage& task_load : loaded_model.tasks()) {
        TaskDTO task = proto_convert::RestoreFromMessage(task_load.task());
        TaskCreationResult result = model_.addTask(task);

        if (!result.getCreatedTaskID()) {
            return false;
        }
        if (!RestoreTaskByMessage(result.getCreatedTaskID().value(), task_load)) {
            // failed to deserialize subtasks hierarchy at any point
            return false;
        }
    }
    return true;
}




