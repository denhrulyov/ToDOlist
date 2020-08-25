//
// Created by denis on 25.08.20.
//

#include "cli/ConsoleContext.h"
#include "ParseShowTag.h"
#include "ParseCommand.h"

ParseShowTag::ParseShowTag(const std::shared_ptr<State> &next_state)
: State(next_state) {}

void ParseShowTag::print(ConsoleContext &context) {
    // must not modify output stream
}

void ParseShowTag::execute(ConsoleContext &context) {
    next_state_ = std::make_shared<ParseCommand>(nullptr);
    if (context.getIO().isEmpty()) {
        context.getIO().log("\nNo tag specified!");
        return;
    }
    std::string tag = context.getIO().readRestBuffer();
    context.getIO().log(std::string("Tasks with tag \"") + tag + "\" : ");
}

void ParseShowTag::help(ConsoleContext &) {

}
