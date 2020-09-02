//
// Created by denis on 18.08.20.
//

#include "cli/ConsoleContext.h"
#include "ParseAddType.h"
#include "State.h"
#include "ParseCommand.h"
#include "cli/tokenization/KeywordTokenizer.h"
#include "InputState.h"
#include "cli/state_machines/input_state_macine/InputStateMachine.h"
#include "AddTaskState.h"
#include "AddSubTaskState.h"

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

    }
    Token token = tokenizer_->read(context.getIO());
    if (token.getType() == Keyword::TASK) {
        return std::make_shared<
                InputState<AddTaskState, ParseCommand>
                    >(std::move(
                            std::make_unique<InputStateMachine>(
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
    } else if (token.getType() == Keyword::SUBTASK) {
        return std::make_shared<
                InputState<AddSubTaskState, ParseCommand>
                    >(std::move(
                            std::make_unique<InputStateMachine>(
                                    std::vector<std::shared_ptr<ParseState>> {
                                            std::make_shared<ParseID>(),
                                            std::make_shared<ParseTaskName>(),
                                            std::make_shared<ParseTaskPriority>(),
                                            std::make_shared<ParseTaskLabel>(),
                                            std::make_shared<ParseTaskDate>()
                                    },
                                    context
                            )
                      )
                );
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
