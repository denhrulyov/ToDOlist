//
// Created by denis on 13.07.20.
//

#ifndef TODOLIST_TASKCONTROLLER_H
#define TODOLIST_TASKCONTROLLER_H
#include "TaskControllerInterface.h"
#include "TaskIDFactory.h"

#include <vector>
#include <map>
#include <unordered_map>
#include <optional>

class TaskController : public TaskControllerInterface {

public:
    TaskController();
    std::vector<TaskID>                      getAllSubtasks(TaskID id_parent) override;
    std::shared_ptr<TaskNode>                getNodeById(TaskID id_node) const override;
    std::shared_ptr<TaskNode>                getRoot() const override;

public:

    std::weak_ptr<TaskNode>                  createSubNode(TaskID id_parent, const Task& tptr) override;
    std::weak_ptr<TaskNode>                  createNodeAndAddToRoot(const Task& tptr) override;

    void                                     modifyTaskData(TaskID id_modify, const Task& new_data) override;
    void                                     eraseNode(TaskID id_erase) override;
    void                                     completeTask(TaskID id_task);


private:
    void registerNode(const std::shared_ptr<TaskNode>& node);

private:
    std::shared_ptr<TaskNode> createFreeNode(TaskID id_newnode, const Task &tptr);
    std::shared_ptr<TaskNode> createNode(const Task& tptr);
    std::shared_ptr<TaskNode> createNode(TaskID id_newnode, const Task& tptr);
    void addNodeTo(TaskID id_parent, std::shared_ptr<TaskNode> p_node);

    // stateful functions that require careful usage
    void findAllChildren(const TaskNode& tnode, std::vector<TaskID>& buf);
    void eraseNodeReferences(TaskID node_id);
    void removeFromTree(TaskID);
    void removeFromTree(std::shared_ptr<TaskNode>);

private:
    TaskIDFactory                               id_generator_;
    std::shared_ptr<TaskNode>                   root_task_;
    std::map<TaskID, std::shared_ptr<TaskNode>> id_to_node_;
};


#endif //TODOLIST_TASKCONTROLLER_H
