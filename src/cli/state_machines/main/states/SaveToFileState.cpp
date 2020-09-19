//
// Created by denis on 18.09.20.
//

#include "SaveToFileState.h"


void SaveToFileState::print(ConsoleContextInterface &context) {

}

std::shared_ptr<State> SaveToFileState::execute(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    std::string path = context.getIO().readRestBuffer();
    std::fstream file;
    try {
        file.open(path);
    } catch (const std::exception& e) {
        context.getIO().putLine("Cannot open file!");
        return factory.getInstanceOfParseCommand();
    }
    auto& service = context.getTaskService();
    try {
        context.getSerializer().serialize(file, service);
    } catch (const std::exception& e) {
        context.getIO().putLine("Cannot write to file!");
        return factory.getInstanceOfParseCommand();
    }
    context.getIO().putLine("Tasks saved");
    return factory.getInstanceOfParseCommand();
}

void SaveToFileState::help(ConsoleContextInterface &) {

}
