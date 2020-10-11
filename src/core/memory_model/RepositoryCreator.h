//
// Created by denis on 02.10.20.
//

#ifndef TODOLIST_REPOSITORYCREATOR_H
#define TODOLIST_REPOSITORYCREATOR_H

#include "api/TaskRespository.h"
#include "data/TaskStorage.h"
#include "structure/LinkManager.h"
#include "view/TagPriorityView.h"
#include "view/DatePriorityView.h"

class RepositoryCreator {

public:
    virtual std::unique_ptr<TaskRepositoryInterface> CreateModel();
    virtual ~RepositoryCreator() = default;
};


#endif //TODOLIST_REPOSITORYCREATOR_H
