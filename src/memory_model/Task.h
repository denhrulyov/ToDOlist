//
// Created by denis on 10.07.20.
//

#ifndef EVAL_TASK_H
#define EVAL_TASK_H

#include <string>
#include <boost/date_time.hpp>

using Gregorian = boost::gregorian::date;

class Task {
public:

    enum class Priority {

        FIRST,
        SECOND,
        THIRD,
        NONE
    };

public:
    static Task create(std::string name, Task::Priority priority, std::string label, Gregorian date);

public:


private:
    Task(std::string name, Task::Priority priority, std::string label, Gregorian date);

    std::string       name_;
public:
    std::string       getName() const;
    Priority          getPriority() const;
    std::string       getLabel() const;
    Gregorian         getDate() const;

private:
    Task::Priority    priority_;
    std::string       label_;
    Gregorian         date_;
};




#endif //EVAL_TASK_H
