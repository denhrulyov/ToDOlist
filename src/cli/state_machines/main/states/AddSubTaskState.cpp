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
    auto& service = context.getTaskService();
    std::optional<TaskDTO> task = service.getTaskByID(context.getBufferedId().value());
    if (task) {
        TaskDTO dto = task.value();
        context.getIO().putLine(std::string("name :     ")
                                + field_repr(dto.getName()));
        context.getIO().putLine(std::string("priority : ")
                                + field_repr(dto.getPriority()));
        context.getIO().putLine(std::string("label :    ")
                                + field_repr(dto.getLabel()));
        context.getIO().putLine(std::string("date :     ")
                                + field_repr(std::optional(dto.getDate())));
        context.getIO().putLine("Y - accept, n - decline");
    } else {
        context.getIO().putLine("###Unknown task###");
    }
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
        return factory.getInstanceOfParseCommand();
    }
    if (!context.getTaskBuffer().has_value()) {
        context.getIO().putLine("System error: some fields were not set correctly.");
        return nullptr;
    } else {
        auto result = context
                        .getTaskService()
                        .addSubTask(
                                context.getBufferedId().value(),
                                context.getTaskBuffer().value()
                         );
        if (result.getSuccessStatus()) {
            context.getIO().putLine("Task added successfully.");
        } else {
            context.getIO().putLine(result.getErrorMessage().value());
        }
    }
    return factory.getInstanceOfParseCommand();
}

void AddSubTaskState::help(ConsoleContextInterface &) {

}
