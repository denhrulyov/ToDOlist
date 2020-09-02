//
// Created by denis on 01.09.20.
//

#ifndef TODOLIST_INPUTSTATEMACHINE_H
#define TODOLIST_INPUTSTATEMACHINE_H

#include <vector>
#include <memory>
#include "ParseTaskLabel.h"
#include "ParseID.h"
#include "ParseTaskDate.h"
#include "ParseTaskPriority.h"
#include "ParseTaskName.h"

class ConsoleContext;
class ParseState;

class InputStateMachine {

public:
    enum class Result {
        SUCCESS,
        FAIL
    };

public:
    explicit        InputStateMachine(const std::vector<std::shared_ptr<ParseState>>&, ConsoleContext&);

public:
    Result            run();

private:
    ConsoleContext&                              context_;
    std::vector<std::shared_ptr<ParseState>>     state_sequence_;
};


#endif //TODOLIST_INPUTSTATEMACHINE_H
