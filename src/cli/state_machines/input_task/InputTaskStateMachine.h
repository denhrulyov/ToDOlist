//
// Created by denis on 01.09.20.
//

#ifndef TODOLIST_INPUTTASKSTATEMACHINE_H
#define TODOLIST_INPUTTASKSTATEMACHINE_H

#include <vector>
#include <memory>
#include "ParseTaskLabel.h"
#include "ParseTaskDate.h"
#include "ParseTaskPriority.h"
#include "ParseTaskName.h"
#include "InputTaskContextInterface.h"
#include "core/api/TaskDTO.h"
#include "ParseStateFactoryInterface.h"

class ParseState;

class InputTaskStateMachine {

public:
    enum class Result {
        SUCCESS,
        FAIL,
        EXIT_PROGRAM
    };

public:
    explicit          InputTaskStateMachine(std::unique_ptr<ParseStateFactoryInterface>,
                                            std::unique_ptr<InputTaskContextInterface>);

public:
    virtual Result            run();
    virtual TaskDTO           extractTask();

    virtual ~InputTaskStateMachine() = default;
private:
    std::unique_ptr<InputTaskContextInterface>   context_;
    std::unique_ptr<ParseStateFactoryInterface>  factory_;
};


#endif //TODOLIST_INPUTTASKSTATEMACHINE_H
