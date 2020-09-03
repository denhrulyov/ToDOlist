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
#include "InputTaskContext.h"
#include "core/api/TaskDTO.h"

class ParseState;

class InputTaskStateMachine {

public:
    enum class Result {
        SUCCESS,
        FAIL
    };

public:
    explicit          InputTaskStateMachine(const std::vector<std::shared_ptr<ParseState>>&, ConsoleContext&);

public:
    Result            run();
    TaskDTO           extractTask();

private:
    std::unique_ptr<InputTaskContext>            context_;
    std::vector<std::shared_ptr<ParseState>>     state_sequence_;
};


#endif //TODOLIST_INPUTTASKSTATEMACHINE_H
