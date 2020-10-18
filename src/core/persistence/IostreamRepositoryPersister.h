//
// Created by denis on 30.09.20.
//

#ifndef TODOLIST_IOSTREAMREPOSITORYPERSISTER_H
#define TODOLIST_IOSTREAMREPOSITORYPERSISTER_H

#include "Persister.h"
#include "task.pb.h"

class IostreamRepositoryPersister : public Persister {

public:
    explicit IostreamRepositoryPersister(TaskRepositoryInterface& model, std::shared_ptr<std::iostream> stream);

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



#endif //TODOLIST_IOSTREAMREPOSITORYPERSISTER_H
