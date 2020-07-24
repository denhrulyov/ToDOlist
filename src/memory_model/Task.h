//
// Created by denis on 10.07.20.
//

#ifndef EVAL_TASK_H
#define EVAL_TASK_H

#include <string>
#include <ctime>


struct Task {
    enum class Priority {
        NONE,
        FIRST,
        SECOND,
        THIRD
    };


    std::string       name;
    Task::Priority    priority;
    std::string       label;
    time_t            date;
};


#endif //EVAL_TASK_H
