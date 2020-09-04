//
// Created by denis on 25.08.20.
//

#include "ShowState.h"
#include "StartState.h"
#include "ParseShowTag.h"
#include "ParseCommand.h"
#include "cli/state_machines/main/ConsoleContext.h"
#include "cli/state_machines/main/tokenization/KeywordTokenizer.h"

ShowState::ShowState() :
State(),
tokenizer_(std::move(std::make_unique<KeywordTokenizer>()))
{}

void ShowState::print(ConsoleContext &context) {

}

std::shared_ptr<State> ShowState::execute(ConsoleContext &context, StateFactoryInterface &factory) {
    if (context.getIO().isEmpty()) {
        context.getIO().putLine("No show option specified!");
        help(context);
        return Visitor<ParseCommand>().visit(factory);
    }
    Keyword token = tokenizer_->read(context.getIO());
    if (token == Keyword::TODAY) {
        context.getIO().putLine("Tasks for today:");
    } else if (token == Keyword::THIS_WEEK) {
        context.getIO().putLine("Tasks for this week:");
    } else if (token == Keyword::ALL) {
        context.getIO().putLine("All tasks:");
    } else if (token == Keyword::TAG) {
        return Visitor<ParseShowTag>().visit(factory);
    } else if (token == Keyword::CURRENT_LIST) {
        context.getIO().putLine("Active list of tasks:");
    } else {
        context.getIO().putLine("Incorrect show options!");
        help(context);
    }
    return Visitor<ParseCommand>().visit(factory);
}

void ShowState::help(ConsoleContext& context) {
    context.getIO().putLine("Available options:");
    context.getIO().putLine("-  today");
    context.getIO().putLine("-  this_week");
    context.getIO().putLine("-  all");
    context.getIO().putLine("-  tag <tg>, where <tg> is a desired label");
}
