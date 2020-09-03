//
// Created by denis on 25.08.20.
//

#include "cli/state_machines/main/ConsoleContext.h"
#include "ParseCommand.h"
#include "ParseAddType.h"
#include "ShowState.h"
#include "InputState.h"
#include "cli/state_machines/input_task/InputTaskStateMachine.h"
#include "DeleteTaskState.h"
#include "cli/state_machines/main/tokenization/KeywordTokenizer.h"
#include "cli/state_machines/main/states/utils/Utils.h"
#include "cli/state_machines/main/states/parse_id/DeleteStateParseID.h"

ParseCommand::ParseCommand()
: State(),
tokenizer_(std::move(std::make_unique<KeywordTokenizer>()))
{}

void ParseCommand::print(ConsoleContext &context) {
    context.getIO().putLine("Input command to execute");
}

std::shared_ptr<State> ParseCommand::execute(ConsoleContext &context) {
    context.getIO().requestInputLine();
    Keyword token = tokenizer_->read(context.getIO());
    if (token == Keyword::ADD) {
        return std::make_shared<ParseAddType>();
    } else if (token == Keyword::SHOW) {
        return std::make_shared<ShowState>();
    } else if (token == Keyword::DELETE) {
        return std::make_shared<DeleteStateParseID>();
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
