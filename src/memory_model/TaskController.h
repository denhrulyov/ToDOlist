//
// Created by denis on 13.07.20.
//

#ifndef TODOLIST_TASKCONTROLLER_H
#define TODOLIST_TASKCONTROLLER_H
#include "TaskControllerInterface.h"

#include <vector>
#include <map>
#include <unordered_map>

class TaskController : public TaskControllerInterface {

public:
    TaskController();
    std::vector<TaskID>                            getAllSubtasks(TaskID id_parent);
    std::shared_ptr<TaskNode>                      getNodeById(TaskID id_node) const;
    std::shared_ptr<TaskNode>                      getRoot() const;

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
    void registerNode(const std::shared_ptr<TaskNode>& node);

private:
    std::shared_ptr<TaskNode> createNode(const Task& tptr);

    // stateful functions that require careful usage
    void findAllChildren(const TaskNode& tnode, std::vector<TaskID>& buf);
    void eraseNodeReferences(TaskID node_id);
    void removeFromTree(TaskID);

private:
    TaskIDFactory                               id_generator_;
    std::shared_ptr<TaskNode>                   root_task_;
    std::map<TaskID, std::shared_ptr<TaskNode>> id_to_node_;
};


#endif //TODOLIST_TASKCONTROLLER_H
