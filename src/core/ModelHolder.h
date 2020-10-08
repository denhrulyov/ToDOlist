//
// Created by denis on 04.10.20.
//

#ifndef TODOLIST_MODELHOLDER_H
#define TODOLIST_MODELHOLDER_H

#include "ModelHolder.h"
#include "persistence/PersisterCreator.h"
#include "memory_model/ModelCreator.h"

class ModelHolder {

public:

    ModelHolder(
            std::unique_ptr<ModelCreator> creator,
            std::unique_ptr<PersisterCreator> persister_creator);

public:
    virtual TaskModelInterface&     GetModel();
    virtual bool                    LoadModelFromFile(const std::string& filepath);
    virtual bool                    SaveModelToFile(const std::string& filepath);
    virtual ~ModelHolder() = default;

private:
    std::unique_ptr<TaskModelInterface> model_;
    std::unique_ptr<ModelCreator> creator_;
    std::unique_ptr<PersisterCreator> persister_creator_;

};


#endif //TODOLIST_MODELHOLDER_H
