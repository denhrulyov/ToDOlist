//
// Created by denis on 04.10.20.
//

#ifndef TODOLIST_MODELHOLDER_H
#define TODOLIST_MODELHOLDER_H

#include "ModelHolderInterface.h"
#include "persistence/ModelPersister.h"
#include "persistence/StreamOwner.h"
#include "memory_model/ModelCreator.h"

class ModelHolder : public ModelHolderInterface {

public:
    explicit ModelHolder(
            std::unique_ptr<ModelCreator> creator,
            std::unique_ptr<ModelPersister> persister,
            StreamOwner& persistence_stream);

public:
    TaskModelInterface&     GetModel() override;
    bool                    LoadModelFromFile(const std::string& filepath) override;
    bool                    SaveModelToFile(const std::string& filepath) override;

private:
    std::unique_ptr<TaskModelInterface> model_;
    std::unique_ptr<ModelCreator> creator_;
    std::unique_ptr<ModelPersister> persister_;
    StreamOwner& persistence_stream_;

};


#endif //TODOLIST_MODELHOLDER_H
