//
// Created by denis on 23.07.20.
//

#ifndef TODOLIST_TASKFACTORYINTERFACE_H
#define TODOLIST_TASKFACTORYINTERFACE_H

class TaskDTO;

class TaskFactoryInterface {
public:
    virtual Task createTask(const TaskDTO&) = 0;

    virtual ~TaskFactoryInterface() = default;
};


#endif //TODOLIST_TASKFACTORYINTERFACE_H
