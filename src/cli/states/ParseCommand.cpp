//
// Created by denis on 25.08.20.
//

#include "cli/ConsoleContext.h"
#include "ParseCommand.h"
#include "ParseAddType.h"
#include "ShowState.h"
#include "InputState.h"
#include "cli/state_machines/input_state_macine/InputStateMachine.h"
#include "DeleteTaskState.h"
#include "cli/tokenization/KeywordTokenizer.h"
#include "cli/states/utils/Utils.h"

ParseCommand::ParseCommand()
: State(),
tokenizer_(std::move(std::make_unique<KeywordTokenizer>()))
{}

void ParseCommand::print(ConsoleContext &context) {
    context.getIO().putLine("Input command to execute");
}

std::shared_ptr<State> ParseCommand::execute(ConsoleContext &context) {
    context.getIO().requestInputLine();
    Token token = tokenizer_->read(context.getIO());
    if (token.getType() == Keyword::ADD) {
        return std::make_shared<ParseAddType>();
    } else if (token.getType() == Keyword::SHOW) {
        return std::make_shared<ShowState>();
    } else if (token.getType() == Keyword::DELETE) {
        return std::make_shared<
                InputState<DeleteTaskState, ParseCommand>
                    >(
                        std::move(
                            std::make_unique<InputStateMachine>(
                                    std::vector<std::shared_ptr<ParseState>> {
                                        std::make_shared<ParseID>()
                                        },
                                    context
                                    )
                                )
                            );
    } else {
        context.getIO().putLine("Unknown command!");
        help(context);
        context.getIO().clear();
        return std::make_shared<ParseCommand>();
    }
}

void ParseCommand::help(ConsoleContext &context) {
    context.getIO().putLine("Available commands:");
    context.getIO().putLine("-  add");
    context.getIO().putLine("-  show");
    context.getIO().putLine("-  postpone");
    context.getIO().putLine("-  delete");
}
