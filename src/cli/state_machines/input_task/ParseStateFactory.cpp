//
// Created by denis on 07.09.20.
//

#include "ParseStateFactory.h"
#include "ParseTaskName.h"
#include "ParseTaskPriority.h"
#include "ParseTaskLabel.h"
#include "ParseTaskDate.h"

ParseStateFactory::ParseStateFactory()
:
states_ {
    std::move(std::make_unique<ParseStateFactory::Initializer<ParseTaskName>>()),
    std::move(std::make_unique<ParseStateFactory::Initializer<ParseTaskPriority>>()),
    std::move(std::make_unique<ParseStateFactory::Initializer<ParseTaskLabel>>()),
    std::move(std::make_unique<ParseStateFactory::Initializer<ParseTaskDate>>())
},
current_state_(states_.begin())
{}

std::shared_ptr<ParseState> ParseStateFactory::getNextState() {
    if (current_state_ != states_.end()) {
        return (*(current_state_++))->get();
    }
    return nullptr;
}


