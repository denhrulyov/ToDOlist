//
// Created by denis on 23.09.20.
//

#ifndef TODOLIST_TASKMODEL_H
#define TODOLIST_TASKMODEL_H

#include "core/memory_model/data/TaskIDFactory.h"
#include "TaskModelInterface.h"

class TaskModel : public TaskModelInterface {

public:
    TaskModel(
            std::unique_ptr<TaskStorageInterface>                   storage,
            std::unique_ptr<PriorityViewInterface<BoostDate>>       view_date,
            std::unique_ptr<PriorityViewInterface<std::string>>     view_label,
            std::unique_ptr<LinkManagerInterface>                   link_manger)
    :
    storage_(std::move(storage)),
    by_date_(std::move(view_date)),
    by_label_(std::move(view_label)),
    link_manager_(std::move(link_manger))
    {}

public:
    TaskCreationResult                          addTask(const TaskDTO&);
    TaskCreationResult                          addSubTask(TaskID, const TaskDTO&);
    TaskModificationResult                      setTaskData(TaskID, const TaskDTO&);
    std::optional<TaskDTO>                      getTaskData(TaskID);
    TaskModificationResult                      dropTask(TaskID);
    TaskModificationResult                      setCompleted(TaskID);
    const PriorityViewInterface<BoostDate>&     dateFilter();
    const PriorityViewInterface<std::string>&   labelFilter();

private:
    std::unique_ptr<TaskStorageInterface>                   storage_;
    TaskIDFactory                                           id_generator_;
    std::unique_ptr<PriorityViewInterface<BoostDate>>       by_date_;
    std::unique_ptr<PriorityViewInterface<std::string>>     by_label_;
    std::unique_ptr<LinkManagerInterface>                   link_manager_;
};


#endif //TODOLIST_TASKMODEL_H
