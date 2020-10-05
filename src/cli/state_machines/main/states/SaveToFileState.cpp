//
// Created by denis on 05.10.20.
//

#include "SaveToFileState.h"


void SaveToFileState::print(ConsoleContextInterface &context) {

}

std::shared_ptr<State> SaveToFileState::execute(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    std::string filepath = context.getIO().readRestBuffer();
    auto result = context.getTaskService().saveToFile(filepath);
    if (!result.getSuccessStatus()) {
        context.getIO().putLine(result.getErrorMessage().value());
    } else {
        context.getIO().putLine("Tasks saved");
    }
    return factory.getInstanceOfParseCommand();
}

void SaveToFileState::help(ConsoleContextInterface &) {

}