//
// Created by denis on 30.09.20.
//

#ifndef TODOLIST_PERSISTER_H
#define TODOLIST_PERSISTER_H

#include "core/memory_model/api/TaskRepositoryInterface.h"

class Persister {

public:
    virtual bool Save() = 0;
    virtual bool Load() = 0;
    virtual ~Persister() = default;
};

#endif //TODOLIST_PROTOBUFMODELPERSISTER_H
