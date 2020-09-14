//
// Created by denis on 14.09.20.
//

#include "CompleteState.h"

void CompleteState::print(ConsoleContextInterface &context) {

}

std::shared_ptr<State> CompleteState::execute(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    if (context.getBufferedId()) {
        auto& service = context.getTaskService();
        RequestResult result = service.complete(context.getBufferedId().value());
        if (result.getSuccessStatus()) {
            context.getIO().putLine("Task completed");
        } else {
            context.getIO().putLine(result.getErrorMessage().value());
        }
    } else {
        context.getIO().putLine("System error: Task ID was not set correctly");
        return nullptr;
    }
    return factory.getInstanceOfParseCommand();
}

void CompleteState::help(ConsoleContextInterface &) {

}
