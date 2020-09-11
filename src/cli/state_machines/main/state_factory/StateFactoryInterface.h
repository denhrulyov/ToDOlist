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

template<class T> class Of;

class StateFactoryInterface {

public:
    virtual std::shared_ptr<State> getInstance(const Of<AddSubTaskState>&) = 0;
    virtual std::shared_ptr<State> getInstance(const Of<AddTaskState>&) = 0;
    virtual std::shared_ptr<State> getInstance(const Of<DeleteTaskState>&) = 0;
    virtual std::shared_ptr<State> getInstance(const Of<InputState<AddTaskState, ParseCommand>>&) = 0;
    virtual std::shared_ptr<State> getInstance(const Of<InputState<AddSubTaskState, ParseCommand>>&) = 0;
    virtual std::shared_ptr<State> getInstance(const Of<ParseAddType>&) = 0;
    virtual std::shared_ptr<State> getInstance(const Of<ParseCommand>&) = 0;
    virtual std::shared_ptr<State> getInstance(const Of<ParseShowTag>&) = 0;
    virtual std::shared_ptr<State> getInstance(const Of<ShowState>&) = 0;
    virtual std::shared_ptr<State> getInstance(const Of<StartState>&) = 0;
    virtual std::shared_ptr<State> getInstance(const Of<DeleteStateParseID>&) = 0;
    virtual std::shared_ptr<State> getInstance(const Of<InputTaskParseID>&) = 0;

    virtual ~StateFactoryInterface() = default;
};


#endif //TODOLIST_STATEFACTORYINTERFACE_H
