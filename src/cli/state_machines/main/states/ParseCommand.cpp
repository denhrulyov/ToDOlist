//
// Created by denis on 25.08.20.
//

#include "cli/state_machines/main/ConsoleContext.h"
#include "ParseCommand.h"
#include "ParseAddType.h"
#include "ShowState.h"
#include "DeleteTaskState.h"
#include "cli/state_machines/main/tokenization/Tokenizer.h"
#include "parse_id/DeleteStateParseID.h"

ParseCommand::ParseCommand(std::unique_ptr<Tokenizer> tokenizer)
: State(),
tokenizer_(std::move(tokenizer))
{}

void ParseCommand::print(ConsoleContext &context) {
    context.getIO().putLine("Input command to execute");
}

std::shared_ptr<State> ParseCommand::execute(ConsoleContext &context, StateFactoryInterface &factory) {
    context.getIO().requestInputLine();
    Keyword token = tokenizer_->read(context.getIO());
    switch (token) {
        case Keyword::ADD:
            return Visitor<ParseAddType>().visit(factory);
        case Keyword::SHOW:
            return Visitor<ShowState>().visit(factory);
        case Keyword::DELETE:
            return Visitor<DeleteStateParseID>().visit(factory);
        default:
            context.getIO().putLine("Unknown command!");
            help(context);
            context.getIO().clear();
            return Visitor<ParseCommand>().visit(factory);
    }
}

void ParseCommand::help(ConsoleContext &context) {
    context.getIO().putLine("Available commands:");
    context.getIO().putLine("-  add");
    context.getIO().putLine("-  show");
    context.getIO().putLine("-  postpone");
    context.getIO().putLine("-  delete");
}
