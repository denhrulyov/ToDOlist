//
// Created by denis on 10.07.20.
//

#ifndef EVAL_TASK_H
#define EVAL_TASK_H

#include <bits/stdc++.h>


struct Task {
    enum class Priority {
        NONE,
        FIRST,
        SECOND,
        THIRD
    };

    static std::vector<Priority> allPriorities() {
        return { Priority::FIRST, Priority::SECOND, Priority::THIRD, Priority::NONE };
    }

    const std::string       name;
    const Task::Priority    priority;
    const std::string       label;
    const time_t            date;
};


#endif //EVAL_TASK_H
