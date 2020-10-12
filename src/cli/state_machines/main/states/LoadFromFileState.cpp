//
// Created by denis on 05.10.20.
//

#include "LoadFromFileState.h"


void LoadFromFileState::print(ConsoleContextInterface &context) {

}

std::shared_ptr<State> LoadFromFileState::execute(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    std::string filepath = context.getIO().readRestBuffer();
    auto result = context.getTaskService().loadFromFile(filepath);
    if (!result.getSuccessStatus()) {
        context.getIO().putLine(result.getErrorMessage().value());
    } else {
        context.getIO().putLine("Tasks loaded");
    }
    return factory.getInstanceOfParseCommand();
}

void LoadFromFileState::help(ConsoleContextInterface &) {

}