//
// Created by denis on 03.09.20.
//

#include "InputTaskParseID.h"
#include "cli/state_machines/main/states/AddSubTaskState.h"
#include "cli/state_machines/main/states/InputState.h"
#include "cli/state_machines/main/states/ParseCommand.h"
#include "cli/state_machines/input_task/InputTaskStateMachine.h"

std::shared_ptr<State> InputTaskParseID::switchGood(ConsoleContext &context) {
    return std::make_shared<InputState<AddSubTaskState, ParseCommand>>(
            std::move(
                    std::make_unique<InputTaskStateMachine>(
                            std::vector<std::shared_ptr<ParseState>> {
                                    std::make_shared<ParseTaskName>(),
                                    std::make_shared<ParseTaskPriority>(),
                                    std::make_shared<ParseTaskLabel>(),
                                    std::make_shared<ParseTaskDate>()
                            },
                            context
                    )
            )
    );
}
