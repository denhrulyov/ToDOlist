//
// Created by denis on 02.10.20.
//

#ifndef TODOLIST_MODELCREATOR_H
#define TODOLIST_MODELCREATOR_H

#include "ModelCreatorInterface.h"
#include "api/TaskModel.h"
#include "data/TaskStorage.h"
#include "structure/LinkManager.h"
#include "view/TagPriorityView.h"
#include "view/DatePriorityView.h"

class ModelCreator : public ModelCreatorInterface {

public:
    std::unique_ptr<TaskModelInterface> CreateModel() override;
};


#endif //TODOLIST_MODELCREATOR_H
