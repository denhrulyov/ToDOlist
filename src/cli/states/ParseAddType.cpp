//
// Created by denis on 18.08.20.
//

#include "ParseAddType.h"
#include "State.h"
ParseAddType::ParseAddType(Console &console)
:
State(console)
{}

void ParseAddType::print() {

}

std::shared_ptr<State> ParseAddType::read() {
    return std::shared_ptr<State>();
}
