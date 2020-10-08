//
// Created by denis on 30.09.20.
//

#ifndef TODOLIST_MODELPERSISTER_H
#define TODOLIST_MODELPERSISTER_H

#include "core/memory_model/api/TaskModelInterface.h"

class ModelPersister {

public:
    virtual bool Save() = 0;
    virtual bool Load() = 0;
    virtual ~ModelPersister() = default;
};

#endif //TODOLIST_PROTOBUFMODELPERSISTER_H
