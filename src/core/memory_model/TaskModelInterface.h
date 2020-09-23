//
// Created by denis on 23.09.20.
//

#ifndef TODOLIST_TASKMODELINTERFACE_H
#define TODOLIST_TASKMODELINTERFACE_H
#include "core/utils/data_transfer/TaskDTOConverter.h"

#include "core/memory_model/data/TaskStorageInterface.h"
#include "core/memory_model/structure/LinkManagerInterface.h"
#include "view/DatePriorityView.h"
#include "view/TagPriorityView.h"
#include "core/api/TaskCreationResult.h"
#include "core/api/TaskModificationResult.h"

class TaskModelInterface {

public:
    virtual TaskCreationResult                          addTask(const TaskDTO&) = 0;
    virtual TaskCreationResult                          addSubTask(TaskID, const TaskDTO&) = 0;
    virtual TaskModificationResult                      setTaskData(TaskID, const TaskDTO&) = 0;
    virtual std::optional<TaskDTO>                      getTaskData(TaskID) = 0;
    virtual TaskModificationResult                      dropTask(TaskID) = 0;
    virtual TaskModificationResult                      setCompleted(TaskID) = 0;
    virtual const PriorityViewInterface<BoostDate>&     dateFilter() = 0;
    virtual const PriorityViewInterface<std::string>&   labelFilter() = 0;
};


#endif //TODOLIST_TASKMODELINTERFACE_H
