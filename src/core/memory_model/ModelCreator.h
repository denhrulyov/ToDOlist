//
// Created by denis on 02.10.20.
//

#ifndef TODOLIST_MODELCREATOR_H
#define TODOLIST_MODELCREATOR_H

#include "api/TaskModel.h"
#include "data/TaskStorage.h"
#include "structure/LinkManager.h"
#include "view/TagPriorityView.h"
#include "view/DatePriorityView.h"

class ModelCreator {

public:
    virtual std::unique_ptr<TaskModelInterface> CreateModel();
    virtual ~ModelCreator() = default;
};


#endif //TODOLIST_MODELCREATOR_H
