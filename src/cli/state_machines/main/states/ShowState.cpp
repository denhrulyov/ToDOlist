//
// Created by denis on 25.08.20.
//

#include "ShowState.h"
#include "StartState.h"
#include "ParseShowTag.h"
#include "ParseCommand.h"
#include "cli/state_machines/main/ConsoleContext.h"
#include "cli/state_machines/main/tokenization/KeywordTokenizer.h"

ShowState::ShowState(std::unique_ptr<Tokenizer> tokenizer) :
State(),
tokenizer_(std::move(tokenizer))
{}

void ShowState::print(ConsoleContextInterface &context) {

}

std::shared_ptr<State> ShowState::execute(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    if (context.getIO().isEmpty()) {
        context.getIO().putLine("No show option specified!");
        help(context);
        return Visitor<ParseCommand>().visit(factory);
    }
    Keyword token = tokenizer_->read(context.getIO());
    switch (token) {
        case Keyword::TODAY:
            context.getIO().putLine("Tasks for today:");
            break;
        case Keyword::THIS_WEEK:
            context.getIO().putLine("Tasks for this week:");
            break;
        case Keyword::ALL:
            context.getIO().putLine("All tasks:");
            break;
        case Keyword::TAG:
            return Visitor<ParseShowTag>().visit(factory);
        case Keyword::CURRENT_LIST:
            context.getIO().putLine("Active list of tasks:");
            break;
        default:
            context.getIO().putLine("Incorrect show options!");
            help(context);
            break;
    }
    return Visitor<ParseCommand>().visit(factory);
}

void ShowState::help(ConsoleContextInterface &context) {
    context.getIO().putLine("Available options:");
    context.getIO().putLine("-  today");
    context.getIO().putLine("-  this_week");
    context.getIO().putLine("-  all");
    context.getIO().putLine("-  tag <tg>, where <tg> is a desired label");
}

