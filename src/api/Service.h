//
// Created by denis on 23.07.20.
//

#ifndef TODOLIST_SERVICE_H
#define TODOLIST_SERVICE_H

#include "TaskService.h"
#include "memory_model/view/DatePriorityView.h"
#include "memory_model/view/TagPriorityView.h"
#include "memory_model/data/TaskStorage.h"
#include "memory_model/data/TaskIDFactory.h"

/*
 * TaskService injector
 *
 */

namespace service {


    /*
     * Function to create default task service.
     *
     * @ return new TaskService instance ready for usage.
     */
    TaskService createService() {
        auto storage =      std::make_unique<TaskStorage>();
        auto view_time =    std::make_unique<DatePriorityView>();
        auto view_label =   std::make_unique<TagPriorityView>();
        auto handler =      std::make_unique<LinkManager>(*view_time, *view_label);
        return TaskService(std::move(storage), std::move(view_time), std::move(view_label), std::move(handler));
    }

}

#endif //TODOLIST_SERVICE_H
