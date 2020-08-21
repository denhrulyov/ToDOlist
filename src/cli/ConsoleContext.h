//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_CONSOLECONTEXT_H
#define TODOLIST_CONSOLECONTEXT_H


#include "core/api/TaskServiceInterface.h"
#include "ConsoleIO.h"
#include "TaskBuffer.h"

class State;

typedef uint32_t TaskNumber;

class ConsoleContext {

public:
    explicit
    ConsoleContext(std::unique_ptr<TaskServiceInterface>);

public:

    TaskBuffer&                             getTaskBuffer();
    TaskServiceInterface&                   getTaskService();
    ConsoleIO&                              getIO();
    std::map<TaskNumber, TaskID>&           getTaskTable();
    std::map<TaskID, TaskNumber>&           getIDTable();

    std::optional<TaskID>                   getBufferedId() const;

private:


    std::map<TaskNumber, TaskID>            task_table_;
    std::map<TaskID, TaskNumber>            id_table_;
    ConsoleIO                               console_;

private:
    std::optional<TaskID>                   id_buffer_;
    TaskBuffer                              task_buffer_;
    std::unique_ptr<TaskServiceInterface>   service_;

};



#endif //TODOLIST_CONSOLECONTEXT_H
