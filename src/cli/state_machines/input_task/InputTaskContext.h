//
// Created by denis on 03.09.20.
//

#ifndef TODOLIST_INPUTTASKCONTEXT_H
#define TODOLIST_INPUTTASKCONTEXT_H

#include "cli/ConsoleIOInterface.h"
#include "core/memory_model/data/Task.h"

class InputTaskContext {

public:
    explicit InputTaskContext(ConsoleIOInterface &);

public:
    ConsoleIOInterface &getIO() const;

public:
    std::optional<std::string>      getName() const;

    std::optional<TaskPriority>     getPriority() const;

    std::optional<std::string>      getLabel() const;

    std::optional<BoostDate>        getDate() const;

    void setName(const std::optional<std::string> &name);

    void setPriority(const std::optional<TaskPriority> &priority);

    void setLabel(const std::optional<std::string> &label);

    void setDate(const std::optional<BoostDate> &date);

private:
    ConsoleIOInterface&             io_;


private:
    std::optional<std::string>      name_;
    std::optional<TaskPriority>     priority_;
    std::optional<std::string>      label_;
    std::optional<BoostDate>        date_;
};


#endif //TODOLIST_INPUTTASKCONTEXT_H
