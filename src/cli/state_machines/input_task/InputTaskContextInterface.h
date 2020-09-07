//
// Created by denis on 07.09.20.
//

#ifndef TODOLIST_INPUTTASKCONTEXTINTERFACE_H
#define TODOLIST_INPUTTASKCONTEXTINTERFACE_H

#include "cli/ConsoleIOInterface.h"
#include "core/memory_model/data/Task.h"

class InputTaskContextInterface {
public:
    virtual ConsoleIOInterface&             getIO() const = 0;

public:
    virtual std::optional<std::string>      getName() const = 0;
    virtual std::optional<TaskPriority>     getPriority() const = 0;
    virtual std::optional<std::string>      getLabel() const = 0;
    virtual std::optional<BoostDate>        getDate() const = 0;
    virtual void                            setName(const std::optional<std::string> &name) = 0;
    virtual void                            setPriority(const std::optional<TaskPriority> &priority) = 0;
    virtual void                            setLabel(const std::optional<std::string> &label) = 0;
    virtual void                            setDate(const std::optional<BoostDate> &date) = 0;

public:
    virtual ~InputTaskContextInterface() = default;
};


#endif //TODOLIST_INPUTTASKCONTEXTINTERFACE_H
