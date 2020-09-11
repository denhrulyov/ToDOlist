//
// Created by denis on 25.08.20.
//

#include "cli/state_machines/main/ConsoleContext.h"
#include "ParseCommand.h"
#include "ParseAddType.h"
#include "ShowState.h"
#include "DeleteTaskState.h"
#include "cli/tokenization/Tokenizer.h"
#include "parse_id/DeleteStateParseID.h"

ParseCommand::ParseCommand(std::unique_ptr<Tokenizer> tokenizer)
: State(),
tokenizer_(std::move(tokenizer))
{}

void ParseCommand::print(ConsoleContextInterface &context) {
    context.getIO().putLine("Input command to execute");
}

std::shared_ptr<State> ParseCommand::execute(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    context.getIO().requestInputLine();
    Keyword spec_cmd = SpecwordFinder::findSpecWord(context.getIO().seeBuffer());
    if (spec_cmd != Keyword::NONE) {
        return dispatchSpecWord(spec_cmd, factory);
    }
    Keyword token = tokenizer_->read(context.getIO());
    switch (token) {
        case Keyword::ADD:
            return factory.getInstance(Of<ParseAddType>());
        case Keyword::SHOW:
            return factory.getInstance(Of<ShowState>());
        case Keyword::DELETE:
            return factory.getInstance(Of<DeleteStateParseID>());
        default:
            context.getIO().putLine("Unknown command!");
            help(context);
            context.getIO().clear();
            return factory.getInstance(Of<ParseCommand>());
    }
}

void ParseCommand::help(ConsoleContextInterface &context) {
    context.getIO().putLine("Available commands:");
    context.getIO().putLine("-  add");
    context.getIO().putLine("-  show");
    context.getIO().putLine("-  postpone");
    context.getIO().putLine("-  delete");
}
