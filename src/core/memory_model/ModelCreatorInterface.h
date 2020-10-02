//
// Created by denis on 02.10.20.
//

#ifndef TODOLIST_MODELCREATORINTERFACE_H
#define TODOLIST_MODELCREATORINTERFACE_H

#include "api/TaskModelInterface.h"

class ModelCreatorInterface {

public:
    virtual std::unique_ptr<TaskModelInterface> CreateModel() = 0;
};



#endif //TODOLIST_MODELCREATORINTERFACE_H
