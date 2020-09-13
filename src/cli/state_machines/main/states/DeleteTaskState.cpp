//
// Created by denis on 26.08.20.
//

#include "cli/state_machines/main/ConsoleContext.h"
#include "DeleteTaskState.h"
#include "ParseCommand.h"

DeleteTaskState::DeleteTaskState(std::unique_ptr<Tokenizer> tokenizer)
:
State(),
tokenizer_(std::move(tokenizer))
{}

void DeleteTaskState::print(ConsoleContextInterface &context) {
    context.getIO().putLine("You want to delete task: ");
    // 1. get task from context.getService().getTaskByID()
    // 2. print task fields

}


std::shared_ptr<State> DeleteTaskState::execute(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    context.getIO().requestInputLine();
    Keyword spec_cmd = SpecwordFinder::findSpecWord(context.getIO().seeBuffer());
    if (spec_cmd != Keyword::NONE) {
        return dispatchSpecWord(spec_cmd, factory);
    }
    Keyword token = tokenizer_->read(context.getIO());
    if (token != Keyword::YES) {
        context.getIO().putLine("aborting...");
    }
    return factory.getInstanceOfParseCommand();
}

void DeleteTaskState::help(ConsoleContextInterface &context) {

}
