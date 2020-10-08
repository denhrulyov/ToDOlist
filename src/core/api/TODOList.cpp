//
// Created by denis on 09.09.20.
//

#include "TODOList.h"

std::unique_ptr<TaskServiceInterface> todo_list::createService() {
    auto creator =      std::make_unique<ModelCreator>();
    auto pers_creator = std::make_unique<PersisterCreator>();
    auto holder =       std::make_unique<ModelHolder>(
                            std::move(creator),
                            std::move(pers_creator));
    return
    std::make_unique<TaskService>(std::move(holder));
}
