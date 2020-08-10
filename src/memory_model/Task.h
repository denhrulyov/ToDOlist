//
// Created by denis on 10.07.20.
//

#ifndef EVAL_TASK_H
#define EVAL_TASK_H

#include <string>
#include <boost/date_time.hpp>
#include "TaskPriority.h"

using Gregorian = boost::gregorian::date;

class Task {

public:
    static Task create(std::string name, TaskPriority priority, std::string label, Gregorian date);

public:


private:
    Task(const std::string& name, TaskPriority priority, const std::string& label, Gregorian date);

    std::string       name_;
public:
    std::string       getName() const;
    TaskPriority      getPriority() const;
    std::string       getLabel() const;
    Gregorian         getDate() const;

private:
    TaskPriority      priority_;
    std::string       label_;
    Gregorian         date_;
};




#endif //EVAL_TASK_H
