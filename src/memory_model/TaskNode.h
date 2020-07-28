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
    Task                                        getTask() const;
    TaskID                                      getId() const;
    std::vector<TaskID>                         getSubtasks() const;
    std::vector<std::shared_ptr<TaskNode>>      getSubNodes() const;
    std::shared_ptr<TaskNode>                   getParent();
    std::shared_ptr<TaskNode>                   getSubtaskByID(TaskID id);
    std::shared_ptr<TaskNode>                   getNthByDate(std::size_t N) const;
    void                                        setParent(std::weak_ptr<TaskNode>);
    std::shared_ptr<TaskNode>                   clone(const Task& new_data);

public:
    void disconnect();
    void addSubtask(std::shared_ptr<TaskNode> subtask);
    void eraseSubtask(TaskID id_erase);

    //testing
    ~TaskNode() {std::cout << "Delete task node\n"; }

private:
    TaskID                                          id;
    Task                                            root_task_;
    std::weak_ptr<TaskNode>                         parent_;
    std::map<TaskID, std::shared_ptr<TaskNode>>     subtasks_;
};


#endif //EVAL_TASKNODE_H
