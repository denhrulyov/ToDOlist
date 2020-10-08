//
// Created by denis on 07.10.20.
//

#ifndef TODOLIST_PERSISTERCREATOR_H
#define TODOLIST_PERSISTERCREATOR_H

#include "ModelPersister.h"

class PersisterCreator {

public:
    virtual std::unique_ptr<ModelPersister> CreatePersister(
            TaskModelInterface& model,
            std::shared_ptr<std::iostream> stream);
    virtual ~PersisterCreator() = default;
};


#endif //TODOLIST_PERSISTERCREATOR_H
