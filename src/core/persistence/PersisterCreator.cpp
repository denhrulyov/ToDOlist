//
// Created by denis on 07.10.20.
//

#include "PersisterCreator.h"
#include "IostreamModelPersister.h"

std::unique_ptr<ModelPersister> PersisterCreator::CreatePersister(
        TaskModelInterface& model,
        std::shared_ptr<std::iostream> stream) {
    return std::make_unique<IostreamModelPersister>(model, stream);
}
