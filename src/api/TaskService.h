//
// Created by denis on 10.07.20.
//

#ifndef EVAL_TASKSERVICE_H
#define EVAL_TASKSERVICE_H
#include "memory_model/TaskNode.h"
#include "memory_model/TaskStorageInterface.h"
#include "TaskCreationResult.h"
#include "memory_model/TaskIDFactory.h"
#include "memory_model/LinkManager.h"
#include "TaskDTOConverter.h"
#include "TaskModificationResult.h"
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <optional>

/*
 * Public api for manipulating tasks.
 *
 * @author Denys Hrulov
 */
class TaskService {

public:
    TaskService(
            std::unique_ptr<TaskStorageInterface>                   storage,
            std::unique_ptr<PriorityViewInterface<BoostDate>>       view_time,
            std::unique_ptr<PriorityViewInterface<std::string>>     view_label,
            std::unique_ptr<LinkManagerInterface>                   link_manger)
    :
    storage_(std::move(storage)),
    by_time_(std::move(view_time)),
    by_label_(std::move(view_label)),
    link_manager_(std::move(link_manger))
    {}

public:
    /*
     * Gives tasks for today already sorted by priority
     *
     * @return vector of TaskDTO
     */
    std::vector<TaskDTO>                                    getToday();
    /*
     * Gives tasks for this week already sorted by priority
     *
     * @return vector of TaskDTO
     */
    std::vector<TaskDTO>                                    getThisWeek();
    /*
     * Gives all tasks already sorted by priority.
     *
     * @return vector of TaskDTO.
     */
    std::vector<TaskDTO>                                    getAllTasks();
    /*
     * Gives all tasks with given label already sorted by priority.
     *
     * @param task label.
     * @return vector of TaskDTO.
     */
    std::vector<TaskDTO>                                    getAllWithLabel(const std::string& label);
    /*
     * Gives task with given id if such exists in system.
     *
     * @param task id.
     * @return task DTO if such task exists otherwise nullopt.
     */
    std::optional<TaskDTO>                                  getTaskByID(TaskID id);

public:
    /*
     * Adds single task to system. It will not belong to any other task.
     *
     * @param DTO representing the task. ID will be ignored.
     *
     * @return object containing id of new created task or info about possible errors.
     */
    TaskCreationResult                                      addTask(const TaskDTO &task_data);
    /*
     * Adds single task to system. It will belong to task with specified id.
     *
     * @param id of task, which will include the given as subtask.
     * @param DTO representing the task. ID will be ignored.
     *
     * @return object containing id of new created task or info about possible errors occurred.
     */
    TaskCreationResult                                      addSubTask(TaskID parent, const TaskDTO &task_data);
    /*
     * Deletes task from system. All subtasks will be deleted recursively.
     *
     * @param id of task to delete.
     *
     * @return object containing id of new created task or info about possible error occurred.
     */
    TaskModificationResult                                  deleteTask(TaskID id);
    /*
     * Postpones the task, changing its date to given.
     *
     * @param id of task to postpone.
     * @param new date to assign task.
     *
     * @return object containing id of modified task or info about possible error occurred.
     */
    TaskModificationResult                                  postponeTask(TaskID id, BoostDate);
    /*
     * Mark task as completed. All subtasks will be deleted recursively.
     *
     * @param id of task to delete.
     *
     * @return object info about success or possible error occurred
     */
    RequestResult                                           complete(TaskID id);

private:
    TaskIDFactory                                           id_generator_;
    std::unique_ptr<TaskStorageInterface>                   storage_;
    std::unique_ptr<PriorityViewInterface<BoostDate>>       by_time_;
    std::unique_ptr<PriorityViewInterface<std::string>>     by_label_;
    std::unique_ptr<LinkManagerInterface>                   link_manager_;
};


#endif //EVAL_TASKSERVICE_H
