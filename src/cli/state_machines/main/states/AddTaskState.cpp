//
// Created by denis on 20.08.20.
//

#include "AddTaskState.h"

//
// Created by denis on 18.08.20.
//

#include "core/utils/task_io/ConsoleTaskIO.h"
#include "ParseCommand.h"
#include "cli/CLITaskIO.h"
#include "cli/state_machines/main/ConsoleContext.h"
#include "cli/state_machines/main/states/utils/Utils.h"
#include "cli/tokenization/Tokenizer.h"



AddTaskState::AddTaskState(std::unique_ptr<Tokenizer> tokenizer)
:
tokenizer_(std::move(tokenizer)),
State()
{}

void
AddTaskState::print(ConsoleContextInterface &context) {
    context.getIO().putLine("You specified task with following parameters:");
    auto dto = context.getTaskBuffer().value();
    cli_task_io::print(context.getIO(), dto);
    context.getIO().putLine("Y - accept, n - decline");
}


std::shared_ptr<State>
AddTaskState::execute(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    context.getIO().requestInputLine();
    Keyword spec_cmd = SpecwordFinder::findSpecWord(context.getIO().seeBuffer());
    if (spec_cmd != Keyword::NONE) {
        return dispatchSpecWord(spec_cmd, factory);
    }
    Keyword token = tokenizer_->read(context.getIO());
    if (token != Keyword::YES) {
        context.getIO().putLine("aborting...");
        return factory.getInstanceOfParseCommand();
    }
    if (!context.getTaskBuffer().has_value()) {
        context.getIO().putLine("Some fields were not set correctly. Task can't be added!");
        return nullptr;
    } else {
        auto result = context
                        .getTaskService()
                        .addTask(context.getTaskBuffer().value());
        if (result.getSuccessStatus()) {
            context.getIO().putLine("Task added successfully.");
        } else {
            context.getIO().putLine(result.getErrorMessage().value());
        }
    }
    return factory.getInstanceOfParseCommand();
}

void AddTaskState::help(ConsoleContextInterface &) {

}


