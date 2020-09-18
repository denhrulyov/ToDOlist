//
// Created by denis on 15.09.20.
//

#include "ShowSubTasksState.h"
#include "cli/state_machines/main/TaskTableIO.h"

void ShowSubTasksState::print(ConsoleContextInterface &) {

}

std::shared_ptr<State>
ShowSubTasksState::execute(ConsoleContextInterface &context, StateFactoryInterface &factory) {
    if (!context.getBufferedId()) {
        context.getIO().putLine("Task id was not set correctly. Program will exit");
        return nullptr;
    }
    TaskID task_id = context.getBufferedId().value();
    auto& service = context.getTaskService();
    std::optional<TaskDTO> maybe_task = service.getTaskByID(task_id);
    if (!maybe_task) {
        context.getIO().putLine("Task not found");
        return factory.getInstanceOfParseCommand();
    }
    context.fillTable(service.getSubTasks(task_id));
    context.getIO().putLine(std::string("Subtasks of task ") + maybe_task.value().getName());
    task_table_io::print(context);
    return factory.getInstanceOfParseCommand();;
}

void ShowSubTasksState::help(ConsoleContextInterface &) {

}
