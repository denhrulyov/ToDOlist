//
// Created by denis on 22.10.20.
//

#include <iostream>
#include <memory>
#include <string>


#include <grpcpp/grpcpp.h>

#include "cli/ConsoleIO.h"
#include "cli/state_machines/main/ConsoleStateMachine.h"
#include "cli/state_machines/main/states/StartState.h"
#include "cli/state_machines/main/state_factory/StateFactory.h"
#include "cli/state_machines/main/ConsoleContext.h"
#include "client/TODOList.h"


#include "TODOList.h"
#include "core/utils/task_io/ConsoleTaskIO.h"

int main() {
    auto service = todo_list::createService();
    auto io      = std::make_unique<ConsoleIO>(std::cin, std::cout);
    auto context = std::make_unique<ConsoleContext>(
            std::move(service),
            std::move(io)
    );
    auto factory = std::make_unique<StateFactory>(context->getIO());
    auto& ref_context = *context;
    ConsoleStateMachine cli(
            std::move(context), std::move(factory), std::make_shared<StartState>()
    );
    cli.run();
    return 0;
}
