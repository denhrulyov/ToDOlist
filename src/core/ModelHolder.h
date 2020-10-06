//
// Created by denis on 04.10.20.
//

#ifndef TODOLIST_MODELHOLDER_H
#define TODOLIST_MODELHOLDER_H

#include "ModelHolder.h"
#include "persistence/ModelPersister.h"
#include "persistence/StreamOwner.h"
#include "memory_model/ModelCreatorInterface.h"

class ModelHolder {

public:

    ModelHolder(
            std::unique_ptr<ModelCreatorInterface> creator,
            std::unique_ptr<ModelPersister> persister,
            StreamOwner& persistence_stream);

public:
    virtual TaskModelInterface&     GetModel();
    virtual bool                    LoadModelFromFile(const std::string& filepath);
    virtual bool                    SaveModelToFile(const std::string& filepath);
    virtual ~ModelHolder() = default;

private:
    std::unique_ptr<TaskModelInterface> model_;
    std::unique_ptr<ModelCreatorInterface> creator_;
    std::unique_ptr<ModelPersister> persister_;
    StreamOwner& persistence_stream_;

};


#endif //TODOLIST_MODELHOLDER_H
