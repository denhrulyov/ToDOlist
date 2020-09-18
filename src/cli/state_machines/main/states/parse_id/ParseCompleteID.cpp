//
// Created by denis on 14.09.20.
//

#include "ParseCompleteID.h"

std::shared_ptr<State> ParseCompleteID::switchGood(ConsoleContextInterface &, StateFactoryInterface &factory) {
    return factory.getInstanceOfCompleteState();
}
