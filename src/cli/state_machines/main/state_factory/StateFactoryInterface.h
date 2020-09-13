//
// Created by denis on 03.09.20.
//

#ifndef TODOLIST_STATEFACTORYINTERFACE_H
#define TODOLIST_STATEFACTORYINTERFACE_H

class AddSubTaskState;
class AddTaskState;
class DeleteTaskState;
class InputTaskState;
class InputSubTaskState;
class ParseAddType;
class ParseCommand;
class ParseShowTag;
class ParseShowParam;
class StartState;
class State;

class DeleteStateParseID;
class InputTaskParseID;
#include <memory>

template<class T> class Of;

class StateFactoryInterface {

public:
    virtual std::shared_ptr<State> getInstanceOfAddSubTaskState() = 0;
    virtual std::shared_ptr<State> getInstanceOfAddTaskState() = 0;
    virtual std::shared_ptr<State> getInstanceOfDeleteTaskState() = 0;
    virtual std::shared_ptr<State> getInstanceOfSubTaskInputChain() = 0;
    virtual std::shared_ptr<State> getInstanceOfTaskInputChain() = 0;
    virtual std::shared_ptr<State> getInstanceOfParseAddType() = 0;
    virtual std::shared_ptr<State> getInstanceOfParseCommand() = 0;
    virtual std::shared_ptr<State> getInstanceOfParseShowTag() = 0;
    virtual std::shared_ptr<State> getInstanceOfShowState() = 0;
    virtual std::shared_ptr<State> getInstanceOfStartState() = 0;
    virtual std::shared_ptr<State> getInstanceOfDeleteStateParseID() = 0;
    virtual std::shared_ptr<State> getInstanceOfInputTaskParseID() = 0;

    virtual ~StateFactoryInterface() = default;
};


#endif //TODOLIST_STATEFACTORYINTERFACE_H
