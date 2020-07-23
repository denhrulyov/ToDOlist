//
// Created by denis on 23.07.20.
//

#ifndef TODOLIST_TASKFACTORYINTERFACE_H
#define TODOLIST_TASKFACTORYINTERFACE_H


class TaskFactoryInterface {
public:
    virtual Task createTask(const std::string& name,
                            Task::Priority priority,
                            const std::string& label,
                            time_t date) = 0;

    virtual ~TaskFactoryInterface() = default;
};


#endif //TODOLIST_TASKFACTORYINTERFACE_H
