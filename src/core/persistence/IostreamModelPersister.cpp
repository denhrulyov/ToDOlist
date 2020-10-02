//
// Created by denis on 30.09.20.
//

#include "IostreamModelPersister.h"
#include "core/memory_model/view/DatePriorityView.h"
#include "core/memory_model/view/TagPriorityView.h"
#include "core/memory_model/data/TaskStorage.h"
#include "core/memory_model/structure/LinkManager.h"
#include "core/memory_model/api/TaskModel.h"

IostreamModelPersister::IostreamModelPersister
        (std::unique_ptr<TaskDataConverterInterface> data_converter)
        :
        data_converter_(std::move(data_converter))
{}

bool IostreamModelPersister::WriteTaskToTaskMessage(const TaskModelInterface& model, const TaskDTO& task, TaskMessage* message) {
    message->set_allocated_task(new TaskData);
    data_converter_->WriteToMessage(task, message->mutable_task());
    for (const auto& subtask : model.getSubTasks(task.getId())) {
        TaskMessage* subtask_dump = message->add_subtasks();
        if (!WriteTaskToTaskMessage(model, subtask, subtask_dump)) {
            return false;
        }
    }
    return true;
}

bool IostreamModelPersister::Save(const TaskModelInterface &model) {
    TaskModelMessage assembled_model_message;
    for (const auto& task : model.getAllTasks()) {
        if (!model.getParentTask(task.getId())) {
            TaskMessage* assembled_task_message = assembled_model_message.add_tasks();
            if (!WriteTaskToTaskMessage(model, task, assembled_task_message)) {
                return false;
            }
        }
    }
    return assembled_model_message.SerializeToOstream(stream_.get());
}

bool IostreamModelPersister::RestoreTaskByMessage(TaskModelInterface& model, TaskID id, const TaskMessage& message) {
    for (const TaskMessage& subtask_load : message.subtasks()) {
        TaskDTO subtask = data_converter_->RestoreFromMessage(subtask_load.task());
        TaskCreationResult result = model.addSubTask(id, subtask);
        if (!result.getCreatedTaskID()) {
            return false;
        }
        TaskID id_subtask = result.getCreatedTaskID().value();
        if (!RestoreTaskByMessage(model, id_subtask, subtask_load)) {
            // failed to deserialize subtasks hierarchy at any point
            return false;
        }
    }
    // all is OK
    return true;
}

bool IostreamModelPersister::Load(TaskModelInterface &model) {
    TaskModelMessage loaded_model;
    if (!loaded_model.ParseFromIstream(stream_.get())) {
        return false;
    }
    for (const TaskMessage& task_load : loaded_model.tasks()) {
        TaskDTO task = data_converter_->RestoreFromMessage(task_load.task());
        TaskCreationResult result = model.addTask(task);

        if (!result.getCreatedTaskID()) {
            return false;
        }
        if (!RestoreTaskByMessage(model, result.getCreatedTaskID().value(), task_load)) {
            // failed to deserialize subtasks hierarchy at any point
            return false;
        }
    }
    return true;
}

void IostreamModelPersister::SetStream(std::unique_ptr<std::iostream> stream) {
    stream_ = std::move(stream);
}


