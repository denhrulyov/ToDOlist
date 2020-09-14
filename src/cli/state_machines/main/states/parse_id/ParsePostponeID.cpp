//
// Created by denis on 15.09.20.
//

#include "ParsePostponeID.h"

std::shared_ptr<State> ParsePostponeID::switchGood(ConsoleContextInterface &, StateFactoryInterface &factory) {
    return factory.getInstanceOfParsePostponeDate();
}
