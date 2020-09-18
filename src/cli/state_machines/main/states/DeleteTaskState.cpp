//
// Created by denis on 26.08.20.
//

#include "cli/CLITaskIO.h"
#include "cli/state_machines/main/ConsoleContext.h"
#include "utils/Utils.h"
#include "DeleteTaskState.h"
#include "ParseCommand.h"

DeleteTaskState::DeleteTaskState(std::unique_ptr<Tokenizer> tokenizer)
:
State(),
tokenizer_(std::move(tokenizer))
{}

void DeleteTaskState::print(ConsoleContextInterface &context) {
    context.getIO().putLine("You want to delete task: ");
    auto& service = context.getTaskService();
    std::optional<TaskDTO> task = service.getTaskByID(context.getBufferedId().value());
    if (task) {
        TaskDTO dto = task.value();
        cli_task_io::print(context.getIO(), dto);
        context.getIO().putLine("And all its subtasks:");
        for (TaskDTO subtask : service.getSubTasksRecursive(task->getId())) {
            cli_task_io::print(context.getIO(), dto);
        }
        context.getIO().putLine("Y - accept, n - decline");
    } else {
        context.getIO().putLine("###Unknown task###");
    }
}


std::shared_ptr<State> DeleteTaskState::execute(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    context.getIO().requestInputLine();
    Keyword spec_cmd = SpecwordFinder::findSpecWord(context.getIO().seeBuffer());
    if (spec_cmd != Keyword::NONE) {
        return dispatchSpecWord(spec_cmd, factory);
    }
    Keyword token = tokenizer_->read(context.getIO());
    if (token != Keyword::YES) {
        context.getIO().putLine("aborting...");
        return factory.getInstanceOfParseCommand();
    }
    if (context.getBufferedId()) {
        auto& service = context.getTaskService();
        auto result = service.deleteTask(context.getBufferedId().value());
        if (result.getSuccessStatus()) {
            context.getIO().putLine("Task successfully deleted");
        } else {
            context.getIO().putLine(result.getErrorMessage().value());
        }
    } else {
        context.getIO().putLine("System error: Task ID was not set correctly");
        return nullptr;
    }
    return factory.getInstanceOfParseCommand();
}

void DeleteTaskState::help(ConsoleContextInterface &context) {

}
