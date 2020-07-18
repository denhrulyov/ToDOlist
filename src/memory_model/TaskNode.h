//
// Created by denis on 10.07.20.
//

#ifndef EVAL_TASKNODE_H
#define EVAL_TASKNODE_H
#include "TaskEntity.h"
#include <list>
#include <memory>
#include <iostream>
#include <map>
#include <vector>

class TaskNode {

public:
    TaskNode(uint id, const Task& tptr) :
    id(id), root_task_(tptr), subtasks_() {}
    Task                                        getTask() const;
    uint                                        getId() const;
    std::vector<uint> getSubtasks() const;
    std::shared_ptr<TaskNode> getParent();
    void setParent(std::weak_ptr<TaskNode>);

public:
    void addSubtask(std::shared_ptr<TaskNode> subtask);
    void eraseSubtask(uint id_erase);

    //testing
    ~TaskNode() {std::cout << "Delete task node\n"; }

private:
    uint                                        id;
    Task                                        root_task_;
    std::weak_ptr<TaskNode>                     parent_;
    std::map<uint, std::shared_ptr<TaskNode>>   subtasks_;
};


#endif //EVAL_TASKNODE_H
