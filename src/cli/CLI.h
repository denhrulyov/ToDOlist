//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_CLI_H
#define TODOLIST_CLI_H

#include "cli/ConsoleIO.h"
#include "cli/state_machines/main/ConsoleStateMachine.h"
#include "cli/state_machines/main/states/StartState.h"
#include "cli/state_machines/main/state_factory/StateFactory.h"
#include "cli/state_machines/main/ConsoleContext.h"
#include "serialization/ProtobufIstreamServiceDeserializer.h"
#include "serialization/ProtobufOstreamServiceSerializer.h"
#include "core/api/TODOList.h"

namespace todo_list_cli {

    ConsoleStateMachine createCLI() {
        auto io      = std::make_unique<ConsoleIO>(std::cin, std::cout);
        auto context = std::make_unique<ConsoleContext>(
                            std::move(todo_list::createService()),
                            std::move(io),
                            std::make_unique<ProtobufOstreamServiceSerializer>(
                                    std::make_unique<ProtoTaskSerializer>()),
                            std::make_unique<ProtobufIstreamServiceDeserializer>(
                                    std::make_unique<IstreamProtoFileLoader<TaskServiceProto>>(),
                                    std::make_unique<ProtoTaskDeserializer>())
                            );
        auto factory = std::make_unique<StateFactory>(*context);
        auto& ref_context = *context;
        ConsoleStateMachine cli(
                std::move(context), std::move(factory), std::make_shared<StartState>()
                );
        return cli;
    }
}


#endif //TODOLIST_CLI_H
