//
// Created by denis on 03.08.20.
//

#ifndef TODOLIST_TASKDTOCONVERTER_H
#define TODOLIST_TASKDTOCONVERTER_H

#include "TaskDTO.h"
#include "memory_model/Task.h"
#include "memory_model/TaskNode.h"

/*
 * Class providing some conversions between Task, TaskNode, TaskDTO objects.
 *
 * @author Denys Hrulov
 */
class TaskDTOConverter {

public:
    /*
     * Method to create Task instance from DTO fields.
     *
     * @param DTO representing the task. Task ID will be ignored.
     *
     * @return Task instance built by dto fields.
     */
    static Task     getTask(const TaskDTO& dto);
    /*
     * Method to create Task instance from DTO fields.
     *
     * @param TaskNode to extract data.
     *
     * @return DTO describing task in the node.
     *
     */
    static TaskDTO  getDTO(const std::shared_ptr<TaskNode>& node);
};


#endif //TODOLIST_TASKDTOCONVERTER_H
