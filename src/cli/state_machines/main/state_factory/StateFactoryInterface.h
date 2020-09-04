//
// Created by denis on 03.09.20.
//

#ifndef TODOLIST_STATEFACTORYINTERFACE_H
#define TODOLIST_STATEFACTORYINTERFACE_H

class AddSubTaskState;
class AddTaskState;
class DeleteTaskState;
template<class T_next, class T_exit> class InputState;
class ParseAddType;
class ParseCommand;
class ParseShowTag;
class ShowState;
class StartState;
class State;

class DeleteStateParseID;
class InputTaskParseID;
#include <memory>

template<class T> class Visitor;

class StateFactoryInterface {

public:
    virtual std::shared_ptr<State> getInstance(const Visitor<AddSubTaskState>&) = 0;
    virtual std::shared_ptr<State> getInstance(const Visitor<AddTaskState>&) = 0;
    virtual std::shared_ptr<State> getInstance(const Visitor<DeleteTaskState>&) = 0;
    virtual std::shared_ptr<State> getInstance(const Visitor<InputState<AddTaskState, ParseCommand>>&) = 0;
    virtual std::shared_ptr<State> getInstance(const Visitor<InputState<AddSubTaskState, ParseCommand>>&) = 0;
    virtual std::shared_ptr<State> getInstance(const Visitor<ParseAddType>&) = 0;
    virtual std::shared_ptr<State> getInstance(const Visitor<ParseCommand>&) = 0;
    virtual std::shared_ptr<State> getInstance(const Visitor<ParseShowTag>&) = 0;
    virtual std::shared_ptr<State> getInstance(const Visitor<ShowState>&) = 0;
    virtual std::shared_ptr<State> getInstance(const Visitor<StartState>&) = 0;
    virtual std::shared_ptr<State> getInstance(const Visitor<DeleteStateParseID>&) = 0;
    virtual std::shared_ptr<State> getInstance(const Visitor<InputTaskParseID>&) = 0;

    virtual ~StateFactoryInterface() = default;
};


#endif //TODOLIST_STATEFACTORYINTERFACE_H
