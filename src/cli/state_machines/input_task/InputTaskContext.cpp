//
// Created by denis on 03.09.20.
//

#include "InputTaskContext.h"



std::optional<std::string> InputTaskContext::getName() const {
    return name_;
}

std::optional<TaskPriority> InputTaskContext::getPriority() const {
    return priority_;
}

std::optional<std::string> InputTaskContext::getLabel() const {
    return label_;
}

std::optional<BoostDate> InputTaskContext::getDate() const {
    return date_;
}

void InputTaskContext::setName(const std::optional<std::string> &name) {
    name_ = name;
}

void InputTaskContext::setPriority(const std::optional<TaskPriority> &priority) {
    priority_ = priority;
}

void InputTaskContext::setLabel(const std::optional<std::string> &label) {
    label_ = label;
}

void InputTaskContext::setDate(const std::optional<BoostDate> &date) {
    date_ = date;
}

ConsoleIO &InputTaskContext::getIO() const {
    return io_;
}

InputTaskContext::InputTaskContext(ConsoleIO& io)
:
io_(io)
{}
