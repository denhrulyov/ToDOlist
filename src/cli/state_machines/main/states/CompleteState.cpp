//
// Created by denis on 14.09.20.
//

#include "CompleteState.h"
#include "cli/CLITaskIO.h"

void CompleteState::print(ConsoleContextInterface &context) {

}

std::shared_ptr<State> CompleteState::execute(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    if (context.getBufferedId()) {
        auto& service = context.getTaskService();
        TaskID task_id = context.getBufferedId().value();
        RequestResult result = service.complete(task_id);
        if (result.getSuccessStatus()) {
            context.getIO().putLine("Task completed");
            context.getIO().putLine("Also completed subtasks:");
            for (const TaskDTO& subtask : service.getSubTasksRecursive(task_id)) {
                cli_task_io::print_brief(context.getIO(), subtask);
            }
        } else {
            context.getIO().putLine(result.getErrorMessage().value());
        }
    } else {
        context.getIO().putLine("System error: Task ID was not set correctly");
        return nullptr;
    }
    return factory.getInstanceOfParseCommand();
}

void CompleteState::help(ConsoleContextInterface &) {

}
