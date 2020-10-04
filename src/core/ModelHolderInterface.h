//
// Created by denis on 04.10.20.
//

#ifndef TODOLIST_MODELHOLDERINTERFACE_H
#define TODOLIST_MODELHOLDERINTERFACE_H

#include "memory_model/api/TaskModelInterface.h"

class ModelHolderInterface {

public:
    virtual TaskModelInterface&     GetModel() = 0;
    virtual bool                    LoadModelFromFile(const std::string& filepath) = 0;
    virtual bool                    SaveModelToFile(const std::string& filepath) = 0;
    virtual ~ModelHolderInterface() = default;
};


#endif //TODOLIST_MODELHOLDERINTERFACE_H
