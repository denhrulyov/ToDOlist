//
// Created by denis on 10.07.20.
//

#ifndef EVAL_TASKNODE_H
#define EVAL_TASKNODE_H
#include "core/memory_model/data/Task.h"
#include "core/memory_model/data/TaskID.h"
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

    TaskNode(TaskID id, const Task& tptr, const std::map<TaskID, std::weak_ptr<TaskNode>>& subtasks):
    id(id), root_task_(tptr), subtasks_(subtasks)
    {}

public:
    Task                                        getTask() const;
    TaskID                                      getId() const;
    bool                                        isComplete() const;
    std::vector<TaskID>                         getSubtasks() const;
    std::vector<std::weak_ptr<TaskNode>>        getSubNodes() const;
    std::weak_ptr<TaskNode>                     getParent() const ;
    std::weak_ptr<TaskNode>                     getSubtaskByID(TaskID id);
    void                                        setParent(std::weak_ptr<TaskNode>);

public:
    std::shared_ptr<TaskNode>                   clone(const Task& new_data);
    void                                        complete();

public:
    void addSubtask(const std::weak_ptr<TaskNode>&);
    void eraseSubtask(TaskID id_erase);

private:
    TaskID                                          id;
    Task                                            root_task_;
    bool                                            complete_ = false;
    std::weak_ptr<TaskNode>                         parent_;
    std::map<TaskID, std::weak_ptr<TaskNode>>       subtasks_;
};


#endif //EVAL_TASKNODE_H
