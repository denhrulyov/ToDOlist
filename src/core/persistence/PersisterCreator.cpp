//
// Created by denis on 07.10.20.
//

#include "PersisterCreator.h"
#include "IostreamRepositoryPersister.h"

std::unique_ptr<Persister> PersisterCreator::CreatePersister(
        TaskRepositoryInterface& model,
        std::shared_ptr<std::iostream> stream) {
    return std::make_unique<IostreamRepositoryPersister>(model, stream);
}
