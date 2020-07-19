//
// Created by denis on 13.07.20.
//

#ifndef TODOLIST_TASKCONTROLLER_H
#define TODOLIST_TASKCONTROLLER_H
#include "TaskNode.h"

#include <vector>
#include <map>
#include <unordered_map>

class TaskController {

public:
    TaskController();
    std::vector<TaskID>                            getAllSubtasks(TaskID id_parent);
    std::shared_ptr<TaskNode>                      getNodeById(TaskID id_node);

public:

    std::weak_ptr<TaskNode>       createSubNode(TaskID id_parent, const Task& tptr);
    std::weak_ptr<TaskNode>       createNodeAndAddToRoot(const Task& tptr);

    void                          eraseNode(TaskID id_erase);


    void see() {
        auto sb = getAllSubtasks(root_task_->getId());
        for (TaskID id : sb) {
            std::cout << "node " << id << " | ";
            for (const auto& nd : id_to_node_[id]->getSubtasks()) {
                std::cout << nd << ' ';
            }
            if (id) std::cout << "/ p = " << id_to_node_[id]->getParent()->getId();
            std::cout << std::endl;
        }
    }
private:
    uint getNextAvailableId();
    void registerNode(const std::shared_ptr<TaskNode>& node);

private:
    std::shared_ptr<TaskNode> createNode(const Task& tptr);

    // stateful functions that require careful usage
    void __find_all_children(const TaskNode& tnode, std::vector<TaskID>& buf);
    void __bind_parent(std::list<std::shared_ptr<TaskNode>>*, const std::shared_ptr<TaskNode>&);
    void __erase_node_references(TaskID node_id);
    void __remove_from_tree(TaskID);

private:
    TaskIDFactory                               id_generator_;
    std::shared_ptr<TaskNode>                   root_task_;
    std::map<TaskID, std::shared_ptr<TaskNode>> id_to_node_;
};


#endif //TODOLIST_TASKCONTROLLER_H
