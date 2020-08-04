//
// Created by denis on 10.07.20.
//

#ifndef EVAL_TASKNODE_H
#define EVAL_TASKNODE_H
#include "Task.h"
#include "TaskID.h"
#include <list>
#include <memory>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

class TaskNode {

public:
    TaskNode(TaskID id, const Task& tptr) :
    id(id), root_task_(tptr), subtasks_() {}
    TaskNode(TaskID id, const Task& tptr, const std::map<TaskID, std::shared_ptr<TaskNode>>& subtasks):
    id(id), root_task_(tptr), subtasks_(subtasks)
    {}

public:
    Task                                        getTask() const;
    TaskID                                      getId() const;
    bool                                        isComplete() const;
    std::vector<TaskID>                         getSubtasks() const;
    std::vector<std::shared_ptr<TaskNode>>      getSubNodes() const;
    std::shared_ptr<TaskNode>                   getParent() const ;
    std::shared_ptr<TaskNode>                   getSubtaskByID(TaskID id);
    void                                        setParent(std::weak_ptr<TaskNode>);

public:
    std::shared_ptr<TaskNode>                   clone(const Task& new_data);
    void                                        complete();

public:
    void addSubtask(std::shared_ptr<TaskNode> subtask);
    void eraseSubtask(TaskID id_erase);

    //testing
    ~TaskNode() {std::cout << "Delete task node\n"; }

private:
    TaskID                                          id;
    Task                                            root_task_;
    bool                                            complete_ = false;
    std::weak_ptr<TaskNode>                         parent_;
    std::map<TaskID, std::shared_ptr<TaskNode>>     subtasks_;
};


#endif //EVAL_TASKNODE_H
