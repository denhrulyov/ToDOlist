//
// Created by denis on 23.07.20.
//

#ifndef TODOLIST_TODOLIST_H
#define TODOLIST_TODOLIST_H

#include "TaskService.h"
#include "core/memory_model/view/DatePriorityView.h"
#include "core/memory_model/view/TagPriorityView.h"
#include "core/memory_model/data/TaskStorage.h"
#include "core/memory_model/data/TaskIDFactory.h"

/*
 * TaskService injector
 *
 */

namespace todo_list {


    /*
     * Function to create default task service.
     *
     * @ return new TaskService instance ready for usage.
     */
    std::unique_ptr<TaskServiceInterface> createService();

}

#endif //TODOLIST_TODOLIST_H
