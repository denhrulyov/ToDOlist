//
// Created by denis on 23.09.20.
//

#ifndef TODOLIST_TASKREPOSITORYINTERFACE_H
#define TODOLIST_TASKREPOSITORYINTERFACE_H
#include "core/utils/data_transfer/TaskDTOConverter.h"

#include "core/memory_model/data/TaskStorageInterface.h"
#include "core/memory_model/structure/LinkManagerInterface.h"
#include "core/memory_model/view/DatePriorityView.h"
#include "core/memory_model/view/TagPriorityView.h"
#include "core/memory_model/api/TaskCreationResult.h"
#include "core/memory_model/api/TaskModificationResult.h"

/*
 * Api for manipulating structure of tasks.
 *
 * @author Denys Hrulov
 */

class TaskRepositoryInterface {

public:
    /*
    * Adds single task to system. It will not belong to any other task.
    *
    * @param DTO representing the task. ID will be ignored.
    *
    * @return object containing id of new created task or info about possible errors.
    */
    virtual TaskCreationResult                          addTask(const RepositoryTaskDTO&) = 0;
    /*
     * Adds single task to system. It will belong to task with specified id.
     *
     * @param id of task, which will include the given as subtask.
     * @param DTO representing the task. ID will be ignored.
     *
     * @return object containing id of new created task or info about possible errors occurred.
     */
    virtual TaskCreationResult                          addSubTask(TaskID, const RepositoryTaskDTO&) = 0;
    /*
     * Replace existing task data with the given. ID will be ignored
     *
     * @param task id.
     * @param DTO representing the task. ID will be ignored.
     *
     * @return object representing result of execution
     */
    virtual TaskModificationResult                      setTaskData(TaskID, const RepositoryTaskDTO&) = 0;
    /*
     * Gives task with given id if such exists in system.
     *
     * @param task id.
     * @return task DTO if such task exists otherwise nullopt.
     */
    virtual std::optional<RepositoryTaskDTO>            getTaskData(TaskID) const = 0;
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
    virtual std::vector<RepositoryTaskDTO>              getToDate(const BoostDate &date_to) const = 0;
    /*
     * Returns reference to view sorted by priority
     * and allowing to get selection with specific label
     *
     * @return label task view
     */
    virtual std::vector<RepositoryTaskDTO>              getWithLabel(const std::string &label) const = 0;
    /*
     * Gives all direct subtasks of task.
     *
     * @param task id.
     * @return vector of task DTO got from subtasks
     */
    virtual std::vector<RepositoryTaskDTO>              getSubTasks(TaskID id) const = 0;
    /*
     * Gives all subtasks, subtasks of subtasks and so on recursively.
     *
     * @param task id.
     * @return vector of task DTO got from subtasks
     */
    virtual std::vector<RepositoryTaskDTO>              getSubTasksRecursive(TaskID id) const = 0;
    /*
     * Gives all actual tasks present in system at the moment
     *
     * @return vector of task DTO corresponding to all tasks in system
     */
    virtual std::vector<RepositoryTaskDTO>              getAllTasks() const = 0;
    /*
     * Gives task which has a task with the given id as subtask,
     * or nothig if such does not exits. In terms of tree, method
     * gives a parent of the task.
     *
     * @return parent of task or nullopt if there is no.
     */
    virtual std::optional<RepositoryTaskDTO>            getParentTask(TaskID id) const = 0;

    virtual                                             ~TaskRepositoryInterface() = default;
};


#endif //TODOLIST_TASKREPOSITORYINTERFACE_H
