//
// Created by denis on 04.10.20.
//

#ifndef TODOLIST_REPOSITORYHOLDER_H
#define TODOLIST_REPOSITORYHOLDER_H

#include "RepositoryHolder.h"
#include "persistence/PersisterCreator.h"
#include "memory_model/RepositoryCreator.h"

class RepositoryHolder {

public:

    RepositoryHolder(
            std::unique_ptr<RepositoryCreator> creator,
            std::unique_ptr<PersisterCreator> persister_creator);

public:
    virtual TaskRepositoryInterface&     GetRepository();
    virtual bool                         LoadRepositoryFromFile(const std::string& filepath);
    virtual bool                         SaveRepositoryToFile(const std::string& filepath);
    virtual ~RepositoryHolder() = default;

private:
    std::unique_ptr<TaskRepositoryInterface> repository_;
    std::unique_ptr<RepositoryCreator> creator_;
    std::unique_ptr<PersisterCreator> persister_creator_;

};


#endif //TODOLIST_REPOSITORYHOLDER_H
