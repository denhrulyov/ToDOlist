//
// Created by denis on 23.09.20.
//

#ifndef TODOLIST_TASKMODEL_H
#define TODOLIST_TASKMODEL_H

#include "core/utils/data_transfer/TaskDTOConverter.h"
#include "core/memory_model/data/TaskIDFactory.h"
#include "core/memory_model/data/TaskStorageInterface.h"
#include "core/memory_model/structure/LinkManagerInterface.h"
#include "view/DatePriorityView.h"
#include "view/TagPriorityView.h"
#include "core/api/TaskCreationResult.h"
#include "core/api/TaskModificationResult.h"

class TaskModel {

public:
    TaskCreationResult                          addTask(const TaskDTO&);
    TaskCreationResult                          addSubTask(TaskID, const TaskDTO&);
    TaskModificationResult                      setTaskData(TaskID, const TaskDTO&);
    std::optional<TaskDTO>                      getTaskData(TaskID);
    TaskModificationResult                      dropTask(TaskID);
    TaskModificationResult                      setPostponed(TaskID);
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
