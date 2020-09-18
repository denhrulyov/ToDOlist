//
// Created by denis on 15.09.20.
//

#include "ParsePostponeDate.h"

void ParsePostponeDate::print(ConsoleContextInterface &context) {
    context.getIO().putLine("Input date:");
}

std::shared_ptr<State> ParsePostponeDate::execute(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    context.getIO().requestInputLine();
    Keyword spec_cmd = SpecwordFinder::findSpecWord(context.getIO().seeBuffer());
    if (spec_cmd != Keyword::NONE) {
        return dispatchSpecWord(spec_cmd, factory);
    }
    std::string input = context.getIO().readRestBuffer();
    if (input.empty()) {
        context.getIO().putLine("Task date must not be empty!");
        return factory.getInstanceOfParsePostponeDate();
    }
    using namespace boost::gregorian;
    try {
        context.fillTaskBuffer(
                TaskDTO::create("", TaskPriority::NONE, "",
                        BoostDate(from_string(input))));
    } catch (...) {
        context.getIO().putLine("Incorrect date!");
        return factory.getInstanceOfParsePostponeDate();
    }
    return factory.getInstanceOfPostponeState();
}

void ParsePostponeDate::help(ConsoleContextInterface &) {

}
