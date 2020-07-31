//
// Created by denis on 31.07.20.
//



#include "Task.h"

Task::Task(std::string name, Task::Priority priority, std::string label, time_t date) :
        name_(name),
        priority_(priority),
        label_(label),
        date_(date)
        {}

Task Task::create(std::string name, Task::Priority priority, std::string label, time_t date) {
    return Task(name, priority, label, date);
}

std::string Task::getName() const {
    return name_;
}

Task::Priority Task::getPriority() const {
    return priority_;
}

std::string Task::getLabel() const {
    return label_;
}

time_t Task::getDate() const {
    return date_;
}