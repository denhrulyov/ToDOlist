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

class ConsoleContext;
class ParseState;

class InputTaskStateMachine {

public:
    enum class Result {
        SUCCESS,
        FAIL
    };

public:
    explicit        InputTaskStateMachine(const std::vector<std::shared_ptr<ParseState>>&, ConsoleContext&);

public:
    Result            run();

private:
    ConsoleContext&                              context_;
    std::vector<std::shared_ptr<ParseState>>     state_sequence_;
};


#endif //TODOLIST_INPUTTASKSTATEMACHINE_H
