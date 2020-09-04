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

std::shared_ptr<State> ParseCommand::execute(ConsoleContext &context, StateFactoryInterface &factory) {
    context.getIO().requestInputLine();
    Keyword token = tokenizer_->read(context.getIO());
    if (token == Keyword::ADD) {
        return Visitor<ParseAddType>().visit(factory);
    } else if (token == Keyword::SHOW) {
        return Visitor<ShowState>().visit(factory);
    } else if (token == Keyword::DELETE) {
        return Visitor<DeleteStateParseID>().visit(factory);
    } else {
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
