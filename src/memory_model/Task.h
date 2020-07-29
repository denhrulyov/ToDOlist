//
// Created by denis on 10.07.20.
//

#ifndef EVAL_TASK_H
#define EVAL_TASK_H

#include <string>
#include <ctime>


struct Task {
    enum class Priority {

        FIRST,
        SECOND,
        THIRD,
        NONE
    };


    const std::string       name;
    const Task::Priority    priority;
    const std::string       label;
    const time_t            date;
};




#endif //EVAL_TASK_H
