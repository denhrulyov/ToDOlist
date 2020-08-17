//
// Created by denis on 23.07.20.
//

#ifndef TODOLIST_TODOLIST_H
#define TODOLIST_TODOLIST_H

#include "TaskService.h"
#include "todo_list/memory_model/view/DatePriorityView.h"
#include "todo_list/memory_model/view/TagPriorityView.h"
#include "todo_list/memory_model/data/TaskStorage.h"
#include "todo_list/memory_model/data/TaskIDFactory.h"

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
    std::unique_ptr<TaskServiceInterface> createService() {
        auto storage =      std::make_unique<TaskStorage>();
        auto view_time =    std::make_unique<DatePriorityView>();
        auto view_label =   std::make_unique<TagPriorityView>();
        auto handler =      std::make_unique<LinkManager>(*view_time, *view_label);
        return
            std::make_unique<TaskService>(
                    std::move(storage),
                    std::move(view_time),
                    std::move(view_label),
                    std::move(handler));
    }

}

#endif //TODOLIST_TODOLIST_H
