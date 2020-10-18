//
// Created by denis on 07.10.20.
//

#ifndef TODOLIST_PERSISTERCREATOR_H
#define TODOLIST_PERSISTERCREATOR_H

#include "Persister.h"

class PersisterCreator {

public:
    virtual std::unique_ptr<Persister> CreatePersister(
            TaskRepositoryInterface& model,
            std::shared_ptr<std::iostream> stream);
    virtual ~PersisterCreator() = default;
};


#endif //TODOLIST_PERSISTERCREATOR_H
