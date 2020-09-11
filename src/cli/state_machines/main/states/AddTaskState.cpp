//
// Created by denis on 20.08.20.
//

#include "AddTaskState.h"

//
// Created by denis on 18.08.20.
//

#include "core/utils/task_io/ConsoleTaskIO.h"
#include "ParseCommand.h"
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
    auto dto = context.getTaskBuffer().value();
    context.getIO().putLine("You specified task with following parameters:");
    context.getIO().putLine(std::string("name :     ")
                                                + field_repr(dto.getName()));
    context.getIO().putLine(std::string("priority : ")
                                                + field_repr(dto.getPriority()));
    context.getIO().putLine(std::string("label :    ")
                                                + field_repr(dto.getLabel()));
    context.getIO().putLine(std::string("date :     ")
                                                + field_repr(std::optional(dto.getDate())));
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
        return factory.getInstance(Of<ParseCommand>());
    }
    if (!context.getTaskBuffer().has_value()) {
        context.getIO().putLine("Some fields were not set correctly. Task can't be added!");
    } else {
        context.getIO().putLine("Task added successfully.");
    }
    return factory.getInstance(Of<ParseCommand>());
}

void AddTaskState::help(ConsoleContextInterface &) {

}


