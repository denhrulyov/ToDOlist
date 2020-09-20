//
// Created by denis on 18.09.20.
//

#include "LoadFromFileState.h"


void LoadFromFileState::print(ConsoleContextInterface &context) {

}

std::shared_ptr<State> LoadFromFileState::execute(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    std::string path = context.getIO().readRestBuffer();
    std::fstream file;
    try {
        file.open(path);
    } catch (const std::exception& e) {
        context.getIO().putLine("Cannot open file!");
        return factory.getInstanceOfParseCommand();
    }
    try {
        auto deserialized_service = context.getDeserializer().deserialize(file);
        if (!deserialized_service) {
            context.getIO().putLine("Invalid data!");
            return factory.getInstanceOfParseCommand();
        }
        context.setTaskService(std::move(deserialized_service));
    } catch (const std::exception& e) {
        context.getIO().putLine("Cannot read from file!");
        return factory.getInstanceOfParseCommand();
    }
    context.getIO().putLine("Tasks loaded");
    return factory.getInstanceOfParseCommand();
}

void LoadFromFileState::help(ConsoleContextInterface &) {

}