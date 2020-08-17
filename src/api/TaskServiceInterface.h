//
// Created by denis on 17.08.20.
//

#ifndef TODOLIST_TASKSERVICEINTERFACE_H
#define TODOLIST_TASKSERVICEINTERFACE_H

#include "TaskCreationResult.h"
#include "TaskModificationResult.h"
#include "TaskDTO.h"

#include <vector>

class TaskServiceInterface {


public:
    /*
     * Gives tasks for today already sorted by priority
     *
     * @return vector of TaskDTO
     */
    virtual std::vector<TaskDTO>                                    getToday() = 0;
    /*
     * Gives tasks for this week already sorted by priority
     *
     * @return vector of TaskDTO
     */
    virtual std::vector<TaskDTO>                                    getThisWeek() = 0;
    /*
     * Gives all tasks already sorted by priority.
     *
     * @return vector of TaskDTO.
     */
    virtual std::vector<TaskDTO>                                    getAllTasks() = 0;
    /*
     * Gives all tasks with given label already sorted by priority.
     *
     * @param task label.
     * @return vector of TaskDTO.
     */
    virtual std::vector<TaskDTO>                                    getAllWithLabel(const std::string& label) = 0;
    /*
     * Gives task with given id if such exists in system.
     *
     * @param task id.
     * @return task DTO if such task exists otherwise nullopt.
     */
    virtual std::optional<TaskDTO>                                  getTaskByID(TaskID id) = 0;

public:
    /*
     * Adds single task to system. It will not belong to any other task.
     *
     * @param DTO representing the task. ID will be ignored.
     *
     * @return object containing id of new created task or info about possible errors.
     */
    virtual TaskCreationResult                                      addTask(const TaskDTO &task_data) = 0;
    /*
     * Adds single task to system. It will belong to task with specified id.
     *
     * @param id of task, which will include the given as subtask.
     * @param DTO representing the task. ID will be ignored.
     *
     * @return object containing id of new created task or info about possible errors occurred.
     */
    virtual TaskCreationResult                                      addSubTask(TaskID parent, const TaskDTO &task_data) = 0;
    /*
     * Deletes task from system. All subtasks will be deleted recursively.
     *
     * @param id of task to delete.
     *
     * @return object containing id of new created task or info about possible error occurred.
     */
    virtual TaskModificationResult                                  deleteTask(TaskID id) = 0;
    /*
     * Postpones the task, changing its date to given.
     *
     * @param id of task to postpone.
     * @param new date to assign task.
     *
     * @return object containing id of modified task or info about possible error occurred.
     */
    virtual TaskModificationResult                                  postponeTask(TaskID id, BoostDate) = 0;
    /*
     * Mark task as completed. All subtasks will be deleted recursively.
     *
     * @param id of task to delete.
     *
     * @return object info about success or possible error occurred
     */
    virtual RequestResult                                           complete(TaskID id) = 0;

public:
    virtual ~TaskServiceInterface() =                               default;
};


#endif //TODOLIST_TASKSERVICEINTERFACE_H
