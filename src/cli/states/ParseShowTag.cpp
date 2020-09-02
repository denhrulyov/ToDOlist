// Created by denis on 25.08.20.
//

#include "cli/ConsoleContext.h"
#include "ParseShowTag.h"
#include "ParseCommand.h"

ParseShowTag::ParseShowTag()
: State() {}

void ParseShowTag::print(ConsoleContext &context) {
    // must not modify output stream
}

std::shared_ptr<State> ParseShowTag::execute(ConsoleContext &context) {
    if (context.getIO().isEmpty()) {
        context.getIO().putLine("\nNo tag specified!");
        return std::make_shared<ParseCommand>();
    }
    std::string tag = context.getIO().readRestBuffer();
    context.getIO().putLine(std::string("Tasks with tag \"") + tag + "\" : ");
    return std::make_shared<ParseCommand>();
}

void ParseShowTag::help(ConsoleContext &) {

}
