//
// Created by denis on 18.08.20.
//

#include "cli/state_machines/main/ConsoleContext.h"
#include "ParseAddType.h"
#include "State.h"
#include "ParseCommand.h"
#include "cli/state_machines/main/tokenization/KeywordTokenizer.h"
#include "InputState.h"
#include "cli/state_machines/input_task/InputTaskStateMachine.h"
#include "AddTaskState.h"
#include "AddSubTaskState.h"
#include "ParseID.h"

ParseAddType::ParseAddType()
:
State(),
tokenizer_(std::move(std::make_unique<KeywordTokenizer>()))
{}

void ParseAddType::print(ConsoleContext& context) {

}

std::shared_ptr<State> ParseAddType::execute(ConsoleContext& context) {
    if (context.getIO().isEmpty()) {
        context.getIO().putLine("Specify what to add!");
        help(context);
        return std::make_shared<ParseCommand>();
    }
    Keyword token = tokenizer_->read(context.getIO());
    if (token == Keyword::TASK) {
        return std::make_shared<
                InputState<AddTaskState, ParseCommand>
                    >(std::move(
                            std::make_unique<InputTaskStateMachine>(
                                    std::vector<std::shared_ptr<ParseState>> {
                                            std::make_shared<ParseTaskName>(),
                                            std::make_shared<ParseTaskPriority>(),
                                            std::make_shared<ParseTaskLabel>(),
                                            std::make_shared<ParseTaskDate>()
                                    },
                                    context
                            )
                      )
                );
    } else if (token == Keyword::SUBTASK) {
        return std::make_shared<ParseID>();
    } else {
        context.getIO().putLine("Invalid add parameter!");
        help(context);
        return std::make_shared<ParseCommand>();
    }
}

void ParseAddType::help(ConsoleContext &context) {
    context.getIO().putLine("Available parameters:");
    context.getIO().putLine("-  task");
    context.getIO().putLine("-  subtask");
}
