// Created by denis on 25.08.20.
//

#include "cli/state_machines/main/ConsoleContext.h"
#include "ParseShowTag.h"
#include "ParseCommand.h"

ParseShowTag::ParseShowTag()
: State() {}

void ParseShowTag::print(ConsoleContextInterface &context) {
    // must not modify output stream
}

std::shared_ptr<State> ParseShowTag::execute(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    if (context.getIO().isEmpty()) {
        context.getIO().putLine("\nNo tag specified!");
        return factory.getInstance(Of<ParseCommand>());
    }
    std::string tag = context.getIO().readRestBuffer();
    context.getIO().putLine(std::string("Tasks with tag \"") + tag + "\" : ");
    return factory.getInstance(Of<ParseCommand>());
}

void ParseShowTag::help(ConsoleContextInterface &) {

}
