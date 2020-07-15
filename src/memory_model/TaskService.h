//
// Created by denis on 10.07.20.
//

#ifndef EVAL_TASKSERVICE_H
#define EVAL_TASKSERVICE_H
#include "TaskNode.h"
#include "TaskFactory.h"
#include "TaskController.h"
#include "PriorityView.h"
#include <unordered_map>
#include <algorithm>
#include <memory>

class TaskService {

public:
    std::vector<TaskEntity> getAllTasks();


public:
    uint    addTask(const std::string& name, Task::Priority priority, const std::string& label, time_t date);
    uint    addSubTask(uint parent, const std::string &name, Task::Priority priority, const std::string &label, time_t date);
    void    popTask(uint id_task);


    /*test ------------------------------------------------------------------
    void inspectRoot() {
        const auto& pp = *task_nodes_.begin();
        std::cout << "references : " << pp.use_count() << std::endl;
    }

    void inspectSize() {
        std::cout << "\nTEST___****\n";
        std::cout << "task_nodes_ : " << task_nodes_.size() << std::endl;
        std::cout << "id_to_node_ : " << id_to_node_.size() << std::endl;
        std::cout << "node_places_ : " << node_places_.size() << std::endl;
    }
    */
private:
    TaskController      tasks_;
    TaskFactory         storage_;
    PriorityView        order_;
};


#endif //EVAL_TASKSERVICE_H
