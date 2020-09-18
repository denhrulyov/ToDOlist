//
// Created by denis on 15.09.20.
//

#include "ShowSubTasksParseID.h"

std::shared_ptr<State>
ShowSubTasksParseID::switchGood(ConsoleContextInterface &, StateFactoryInterface &factory) {
    return factory.getInstanceOfShowSubTasksState();
}
