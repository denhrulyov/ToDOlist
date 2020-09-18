//
// Created by denis on 14.09.20.
//

#include "PostponeState.h"

void PostponeState::print(ConsoleContextInterface &context) {

}

std::shared_ptr<State> PostponeState::execute(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    if (context.getBufferedId() && context.getTaskBuffer()) {
        auto& service = context.getTaskService();
        RequestResult result = service.postponeTask(
                                                context.getBufferedId().value(),
                                                context.getTaskBuffer()->getDate()
                                                );
        if (result.getSuccessStatus()) {
            context.getIO().putLine("Task postponed");
        } else {
            context.getIO().putLine(result.getErrorMessage().value());
        }
    } else {
        context.getIO().putLine("System error: Data was not set correctly");
        return nullptr;
    }
    return factory.getInstanceOfParseCommand();
}

void PostponeState::help(ConsoleContextInterface &) {

}
