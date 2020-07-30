//
// Created by denis on 10.07.20.
//

#ifndef EVAL_TASK_H
#define EVAL_TASK_H

#include <string>
#include <ctime>


class Task {
public:

    enum class Priority {

        FIRST,
        SECOND,
        THIRD,
        NONE
    };

public:
    static Task create(std::string name, Task::Priority priority, std::string label, time_t date);

public:


private:
    Task(std::string name, Task::Priority priority, std::string label, time_t date) :
    name_(name),
    priority_(priority),
    label_(label),
    date_(date)
    {}

    std::string       name_;
public:
    std::string getName() const;
    Priority getPriority() const;
    std::string getLabel() const;
    time_t getDate() const;

private:
    Task::Priority    priority_;
    std::string       label_;
    time_t            date_;
};




#endif //EVAL_TASK_H
