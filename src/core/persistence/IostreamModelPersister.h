//
// Created by denis on 30.09.20.
//

#ifndef TODOLIST_IOSTREAMMODELPERSISTER_H
#define TODOLIST_IOSTREAMMODELPERSISTER_H

#include "ModelPersister.h"
#include "task.pb.h"

class IostreamModelPersister : public ModelPersister {

public:
    explicit IostreamModelPersister(TaskRepositoryInterface& model, std::shared_ptr<std::iostream> stream);

public:
    bool                                Save() override;
    bool                                Load() override;

private:
    bool RestoreTaskByMessage(TaskID id, const TaskMessage& message);
    bool WriteTaskToTaskMessage(const TaskDTO& task, TaskMessage* message);

private:
    TaskRepositoryInterface& model_;
    std::shared_ptr<std::iostream> stream_;
};



#endif //TODOLIST_IOSTREAMMODELPERSISTER_H
