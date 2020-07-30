//
// Created by denis on 28.07.20.
//

#ifndef TODOLIST_TASKIDFACTORY_H
#define TODOLIST_TASKIDFACTORY_H

#include "TaskIDFactoryInterface.h"

class TaskIDFactory : public TaskIDFactoryInterface {
public:
    explicit TaskIDFactory(unsigned int initial_id = 0) : current_id_(initial_id) {};
    TaskID generateID() override;
    ~TaskIDFactory() override = default;

private:
    unsigned int current_id_;
};


#endif //TODOLIST_TASKIDFACTORY_H
