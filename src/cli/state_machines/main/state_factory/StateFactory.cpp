//
// Created by denis on 03.09.20.
//

#include "StateFactory.h"
#include "Visitor.h"
#include "cli/state_machines/main/tokenization/KeywordTokenizer.h"
#include "cli/state_machines/main/states/AllStates.h"

StateFactory::StateFactory(ConsoleIOInterface &io)
:
io_(io)
{}


std::shared_ptr<State> StateFactory::getInstance(const Visitor<AddSubTaskState> &) {
    return std::make_shared<AddSubTaskState>(std::make_unique<KeywordTokenizer>());
}

std::shared_ptr<State> StateFactory::getInstance(const Visitor<AddTaskState> &) {
    return std::make_shared<AddTaskState>(std::make_unique<KeywordTokenizer>());
}

std::shared_ptr<State> StateFactory::getInstance(const Visitor<DeleteTaskState> &) {
    return std::make_shared<DeleteTaskState>();
}

std::shared_ptr<State> StateFactory::getInstance(const Visitor<InputState<AddTaskState, ParseCommand>> &) {
    return std::make_shared<
            InputState<AddTaskState, ParseCommand>
                >(std::move(
                        std::make_unique<InputTaskStateMachine>(
                                std::vector<std::shared_ptr<ParseState>> {
                                        std::make_shared<ParseTaskName>(),
                                        std::make_shared<ParseTaskPriority>(),
                                        std::make_shared<ParseTaskLabel>(),
                                        std::make_shared<ParseTaskDate>()
                                },
                                io_
                        )
                  )
                );
}

std::shared_ptr<State> StateFactory::getInstance(const Visitor<InputState<AddSubTaskState, ParseCommand>> &) {
    return std::make_shared<InputState<AddSubTaskState, ParseCommand>>(
            std::move(
            std::make_unique<InputTaskStateMachine>(
                    std::vector<std::shared_ptr<ParseState>> {
                            std::make_shared<ParseTaskName>(),
                            std::make_shared<ParseTaskPriority>(),
                            std::make_shared<ParseTaskLabel>(),
                            std::make_shared<ParseTaskDate>()
                    },
                    io_
                )
            )
    );
}

std::shared_ptr<State> StateFactory::getInstance(const Visitor<ParseAddType> &) {
    return std::make_shared<ParseAddType>(std::make_unique<KeywordTokenizer>());
}

std::shared_ptr<State> StateFactory::getInstance(const Visitor<ParseCommand> &) {
    return std::make_shared<ParseCommand>(std::make_unique<KeywordTokenizer>());
}

std::shared_ptr<State> StateFactory::getInstance(const Visitor<ParseShowTag> &) {
    return std::make_shared<ParseShowTag>();
}

std::shared_ptr<State> StateFactory::getInstance(const Visitor<ShowState> &) {
    return std::make_shared<ShowState>(std::make_unique<KeywordTokenizer>());
}

std::shared_ptr<State> StateFactory::getInstance(const Visitor<StartState> &) {
    return std::make_shared<StartState>();
}

std::shared_ptr<State> StateFactory::getInstance(const Visitor<DeleteStateParseID> &) {
    return std::make_shared<DeleteStateParseID>();
}

std::shared_ptr<State> StateFactory::getInstance(const Visitor<InputTaskParseID> &) {
    return std::make_shared<InputTaskParseID>();
}

