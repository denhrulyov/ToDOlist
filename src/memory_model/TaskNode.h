//
// Created by denis on 10.07.20.
//

#ifndef EVAL_TASKNODE_H
#define EVAL_TASKNODE_H
#include "Task.h"
#include <list>
#include <memory>

class TaskNode {

public:
    TaskNode(uint id, std::unique_ptr<Task> tptr) :
    id(id), root_task_(std::move(tptr)) {}
    const Task&                                 getTask() const;
    uint                                        getId() const;
    std::list<std::shared_ptr<TaskNode>>&       getSubtasks();
    const std::list<std::shared_ptr<TaskNode>>& getSubtasks() const;

public:
    void addSubtask(std::shared_ptr<TaskNode> subtask);

    //testing
    ~TaskNode() {std::cout << "Delete task node\n"; }

private:
    uint id;
    std::unique_ptr<Task> root_task_;
    std::list<std::shared_ptr<TaskNode>> subtasks_;
};


#endif //EVAL_TASKNODE_H
