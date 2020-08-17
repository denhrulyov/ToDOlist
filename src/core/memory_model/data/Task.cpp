//
// Created by denis on 31.07.20.
//



#include "Task.h"

Task::Task(const std::string& name, TaskPriority priority, const std::string& label, BoostDate date) :
        name_(name),
        priority_(priority),
        label_(label),
        date_(date)
        {}

Task Task::create(std::string name, TaskPriority priority, std::string label, BoostDate date) {
    return Task(name, priority, label, date);
}

std::string Task::getName() const {
    return name_;
}

TaskPriority Task::getPriority() const {
    return priority_;
}

std::string Task::getLabel() const {
    return label_;
}

BoostDate Task::getDate() const {
    return date_;
}