//
// Created by denis on 25.08.20.
//

#include "cli/ConsoleContext.h"
#include "ParseCommand.h"
#include "ParseAddType.h"
#include "ShowState.h"
#include "ParseID.h"
#include "DeleteTaskState.h"
#include "cli/tokenization/KeywordTokenizer.h"
#include "cli/states/utils/Utils.h"

ParseCommand::ParseCommand()
: ParseState(),
tokenizer_(std::move(std::make_unique<KeywordTokenizer>()))
{}

void ParseCommand::print(ConsoleContext &context) {
    context.getIO().log("Input command to execute");
}

std::shared_ptr<State> ParseCommand::execute(ConsoleContext &context) {
    Token token = tokenizer_->read(context.getIO());
    if (token.getType() == TypeToken::ADD) {
        return std::make_shared<ParseAddType>();
    }
    else if (token.getType() == TypeToken::SHOW) {
        return std::make_shared<ShowState>();
    } else if (token.getType() == TypeToken::DELETE) {
        return std::make_shared<InputChain<pack<ParseID>, DeleteTaskState, ParseCommand>>();
    } else {
        context.getIO().log("Unknown command!");
        help(context);
        context.getIO().clear();
        return std::make_shared<ParseCommand>();
    }
}

void ParseCommand::help(ConsoleContext &context) {
    context.getIO().log("Available commands:");
    context.getIO().log("-  add");
    context.getIO().log("-  show");
    context.getIO().log("-  postpone");
    context.getIO().log("-  delete");
}
