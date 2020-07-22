//
// Created by denis on 10.07.20.
//

#ifndef EVAL_TASKSERVICE_H
#define EVAL_TASKSERVICE_H
#include "memory_model/TaskNode.h"
#include "memory_model/TaskFactory.h"
#include "memory_model/TaskController.h"
#include "memory_model/PriorityView.h"
#include "memory_model/TaskID.h"
#include "TaskIDConverter.h"
#include <unordered_map>
#include <algorithm>
#include <memory>

class TaskService {

public:
    TaskService() : id_converter_(task_tree_) {}
    std::vector<TaskDTO> getAllTasks();

public:
    UserTaskID      addTask(const std::string& name, Task::Priority priority, const std::string& label, time_t date);
    UserTaskID      addSubTask(UserTaskID parent, const std::string &name, Task::Priority priority, const std::string &label, time_t date);
    void            deleteTask(TaskID id_task);


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

    void inspectRoot() {
        task_tree_.see();
    }
private:
    TaskFactory         task_creator_;
    TaskController      task_tree_;
    TaskIDConverter     id_converter_;
    PriorityView        by_priority_;
};


#endif //EVAL_TASKSERVICE_H
