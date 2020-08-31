//
// Created by denis on 25.08.20.
//

#include "ShowState.h"
#include "StartState.h"
#include "ParseShowTag.h"
#include "ParseCommand.h"
#include "cli/ConsoleContext.h"
#include "cli/tokenization/KeywordTokenizer.h"

ShowState::ShowState() :
State(),
tokenizer_(std::move(std::make_unique<KeywordTokenizer>()))
{}

void ShowState::print(ConsoleContext &context) {

}

std::shared_ptr<State> ShowState::execute(ConsoleContext &context) {
    if (context.getIO().isEmpty()) {
        context.getIO().log("No show option specified!");
        help(context);
        return std::make_shared<ParseCommand>();
    }
    Token token = tokenizer_->read(context.getIO());
    TypeToken type_token = token.getType();
    if (type_token == TypeToken::TODAY) {
        context.getIO().log("Tasks for today:");
    } else if (type_token == TypeToken::THIS_WEEK) {
        context.getIO().log("Tasks for this week:");
    } else if (type_token == TypeToken::ALL) {
        context.getIO().log("All tasks:");
    } else if (type_token == TypeToken::TAG) {
        return std::make_shared<ParseShowTag>();
    } else if (type_token == TypeToken::CURRENT_LIST) {
        context.getIO().log("Active list of tasks:");
    } else {
        context.getIO().log("Incorrect show options!");
        help(context);
    }
    return std::make_shared<ParseCommand>();
}

void ShowState::help(ConsoleContext& context) {
    context.getIO().log("Available options:");
    context.getIO().log("-  today");
    context.getIO().log("-  this_week");
    context.getIO().log("-  all");
    context.getIO().log("-  tag <tg>, where <tg> is a desired label");
}

