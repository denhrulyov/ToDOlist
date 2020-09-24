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

/*
 * Api for manipulating structure of tasks.
 *
 * @author Denys Hrulov
 */

class TaskModelInterface {

public:
    /*
    * Adds single task to system. It will not belong to any other task.
    *
    * @param DTO representing the task. ID will be ignored.
    *
    * @return object containing id of new created task or info about possible errors.
    */
    virtual TaskCreationResult                          addTask(const TaskDTO&) = 0;
    /*
     * Adds single task to system. It will belong to task with specified id.
     *
     * @param id of task, which will include the given as subtask.
     * @param DTO representing the task. ID will be ignored.
     *
     * @return object containing id of new created task or info about possible errors occurred.
     */
    virtual TaskCreationResult                          addSubTask(TaskID, const TaskDTO&) = 0;
    /*
     * Replace existing task data with the given. ID will be ignored
     *
     * @param task id.
     * @param DTO representing the task. ID will be ignored.
     *
     * @return object representing result of execution
     */
    virtual TaskModificationResult                      setTaskData(TaskID, const TaskDTO&) = 0;
    /*
     * Gives task with given id if such exists in system.
     *
     * @param task id.
     * @return task DTO if such task exists otherwise nullopt.
     */
    virtual std::optional<TaskDTO>                      getTaskData(TaskID) = 0;
    /*
     * Deletes task from system. All subtasks will be deleted recursively.
     *
     * @param id of task to delete.
     *
     * @return object representing result of execution
     */
    virtual TaskModificationResult                      dropTask(TaskID) = 0;
    /*
     * Set concrete task status to completed
     *
     * @param id of task to set completed.
     *
     * @return object representing result of execution
     */
    virtual TaskModificationResult                      setCompleted(TaskID) = 0;
    /*
     * Returns reference to view sorted by priority
     * and allowing to get selection with date constraint
     *
     * @return date task view
     */
    virtual const PriorityViewInterface<BoostDate>&     dateFilter() = 0;
    /*
     * Returns reference to view sorted by priority
     * and allowing to get selection with specific label
     *
     * @return label task view
     */
    virtual const PriorityViewInterface<std::string>&   labelFilter() = 0;
};


#endif //TODOLIST_TASKMODELINTERFACE_H
