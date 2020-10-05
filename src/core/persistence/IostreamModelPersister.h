//
// Created by denis on 30.09.20.
//

#ifndef TODOLIST_IOSTREAMMODELPERSISTER_H
#define TODOLIST_IOSTREAMMODELPERSISTER_H

#include "ModelPersister.h"
#include "StreamOwner.h"
#include "task.pb.h"

class IostreamModelPersister : public ModelPersister, public StreamOwner {

public:
    bool                                Save(const TaskModelInterface &model) override;
    bool                                Load(TaskModelInterface &model) override;
    void                                SetStream(std::unique_ptr<std::iostream>) override;

private:
    bool RestoreTaskByMessage(TaskModelInterface& model, TaskID id, const TaskMessage& message);
    bool WriteTaskToTaskMessage(const TaskModelInterface& model, const TaskDTO& task, TaskMessage* message);

private:
    std::shared_ptr<std::iostream> stream_;
};



#endif //TODOLIST_IOSTREAMMODELPERSISTER_H
