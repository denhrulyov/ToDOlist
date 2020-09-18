//
// Created by denis on 03.09.20.
//

#ifndef TODOLIST_INPUTTASKCONTEXT_H
#define TODOLIST_INPUTTASKCONTEXT_H

#include "InputTaskContextInterface.h"

class InputTaskContext : public InputTaskContextInterface{

public:
    explicit InputTaskContext(ConsoleIOInterface &);

public:
    ConsoleIOInterface&             getIO() const override;

public:
    std::optional<std::string>      getName() const override ;

    std::optional<TaskPriority>     getPriority() const override ;

    std::optional<std::string>      getLabel() const override ;

    std::optional<BoostDate>        getDate() const override ;

    void setName(const std::optional<std::string> &name) override ;

    void setPriority(const std::optional<TaskPriority> &priority) override ;

    void setLabel(const std::optional<std::string> &label) override ;

    void setDate(const std::optional<BoostDate> &date) override ;

private:
    ConsoleIOInterface&             io_;


private:
    std::optional<std::string>      name_;
    std::optional<TaskPriority>     priority_;
    std::optional<std::string>      label_;
    std::optional<BoostDate>        date_;
};


#endif //TODOLIST_INPUTTASKCONTEXT_H
