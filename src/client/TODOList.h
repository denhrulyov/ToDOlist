//
// Created by denis on 23.07.20.
//

#ifndef TODOLIST_TODOLIST_H
#define TODOLIST_TODOLIST_H

#include "core/api/TaskService.h"
#include "core/memory_model/RepositoryCreator.h"
#include "core/persistence/PersisterCreator.h"
#include "core/persistence/ProtoConvert.h"
#include "core/RepositoryHolder.h"

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
