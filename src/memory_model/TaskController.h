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
    std::vector<uint>                              getAllSubtasks(uint id_parent);
    std::shared_ptr<TaskNode>                      getNodeById(uint id_node);

public:

    std::weak_ptr<TaskNode>       createSubNode(uint id_parent, const Task& tptr);
    std::weak_ptr<TaskNode>       createNodeAndAddToRoot(const Task& tptr);

    void                          eraseNode(uint id_erase);


    void see() {
        auto sb = getAllSubtasks(0);
        for (uint id : sb) {
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
    void __find_all_children(const TaskNode& tnode, std::vector<uint>& buf);
    void __bind_parent(std::list<std::shared_ptr<TaskNode>>*, const std::shared_ptr<TaskNode>&);
    void __erase_node_references(uint node_id);
    void __remove_from_tree(uint);

    std::shared_ptr<TaskNode> root_task_;
    std::map<uint, std::shared_ptr<TaskNode>> id_to_node_;
};


#endif //TODOLIST_TASKCONTROLLER_H
