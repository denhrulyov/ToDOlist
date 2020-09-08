//
// Created by denis on 18.08.20.
//

#include "cli/state_machines/main/ConsoleContext.h"
#include "ParseAddType.h"
#include "State.h"
#include "ParseCommand.h"
#include "cli/tokenization/KeywordTokenizer.h"
#include "InputState.h"
#include "AddTaskState.h"
#include "AddSubTaskState.h"
#include "cli/state_machines/main/states/parse_id/InputTaskParseID.h"

ParseAddType::ParseAddType(std::unique_ptr<Tokenizer> tokenizer)
:
State(),
tokenizer_(std::move(tokenizer))
{}

void ParseAddType::print(ConsoleContextInterface &context) {

}

std::shared_ptr<State> ParseAddType::execute(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    if (context.getIO().isEmpty()) {
        context.getIO().putLine("Specify what to add!");
        help(context);
        return Visitor<ParseCommand>().visit(factory);
    }
    Keyword token = tokenizer_->read(context.getIO());
    switch (token) {
        case Keyword::TASK:
            return Visitor<InputState<AddTaskState, ParseCommand>>().visit(factory);
        case Keyword::SUBTASK:
            return Visitor<InputTaskParseID>().visit(factory);
        default:
            context.getIO().putLine("Invalid add parameter!");
            help(context);
            return Visitor<ParseCommand>().visit(factory);
    }
}

void ParseAddType::help(ConsoleContextInterface &context) {
    context.getIO().putLine("Available parameters:");
    context.getIO().putLine("-  task");
    context.getIO().putLine("-  subtask");
}
