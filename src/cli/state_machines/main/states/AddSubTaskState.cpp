//
// Created by denis on 21.08.20.
//

#include "AddSubTaskState.h"

#include "core/utils/task_io/ConsoleTaskIO.h"
#include "StartState.h"
#include "cli/state_machines/main/ConsoleContext.h"
#include "cli/state_machines/main/states/utils/Utils.h"


AddSubTaskState::AddSubTaskState(std::unique_ptr<Tokenizer> tokenizer)
:
State(),
tokenizer_(std::move(tokenizer))
{}

void
AddSubTaskState::print(ConsoleContextInterface &context) {
    auto buffer = context.getTaskBuffer();
    context.getIO().putLine("Main task: ");
    context.getIO().putLine(std::string("name :     ") + field_repr(buffer->getName()));
    context.getIO().putLine(std::string("priority : ") + field_repr(buffer->getPriority()));
    context.getIO().putLine(std::string("label :    ") + field_repr(buffer->getLabel()));
    context.getIO().putLine(std::string("date :     ") + field_repr(std::optional(buffer->getDate())));
    context.getIO().putLine("You specified subtask with following parameters:");
    context.getIO().putLine(std::string("name :     ") + field_repr(buffer->getName()));
    context.getIO().putLine(std::string("priority : ") + field_repr(buffer->getPriority()));
    context.getIO().putLine(std::string("label :    ") + field_repr(buffer->getLabel()));
    context.getIO().putLine(std::string("date :     ") + field_repr(std::optional(buffer->getDate())));
    context.getIO().putLine("Y - accept, n - decline");
}


std::shared_ptr<State>
AddSubTaskState::execute(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    context.getIO().requestInputLine();
    Keyword spec_cmd = SpecwordFinder::findSpecWord(context.getIO().seeBuffer());
    if (spec_cmd != Keyword::NONE) {
        return dispatchSpecWord(spec_cmd, factory);
    }
    Keyword token = tokenizer_->read(context.getIO());
    if (token != Keyword::YES) {
        context.getIO().putLine("aborting...");
        return factory.getInstance(Of<StartState>());
    }
    if (!context.getTaskBuffer().has_value()) {
        context.getIO().putLine("Some fields were not set correctly. Task can't be added!");
    } else {
        context.getIO().putLine("Task added successfully.");
    }
    return factory.getInstance(Of<ParseCommand>());
}

void AddSubTaskState::help(ConsoleContextInterface &) {

}
