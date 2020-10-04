//
// Created by denis on 09.09.20.
//

#include "TODOList.h"

std::unique_ptr<TaskServiceInterface> todo_list::createService() {
    auto creator =      std::make_unique<ModelCreator>();
    auto persister =    std::make_unique<IostreamModelPersister>(
                            std::make_unique<TaskDataConverter>()
                        );
    StreamOwner& persistence_stream = *persister;
    auto holder =       std::make_unique<ModelHolder>(
                            std::move(creator),
                            std::move(persister),
                            persistence_stream);
    return
    std::make_unique<TaskService>(std::move(holder));
}
