//
// Created by denis on 13.07.20.
//

#ifndef TODOLIST_PRIORITYVIEW_H
#define TODOLIST_PRIORITYVIEW_H
#include "TaskNode.h"
#include "TaskDTO.h"
#include <functional>
#include <set>


using multimap_by_date = std::multimap<
                                    time_t,
                                    std::weak_ptr<TaskNode>
                                    >;

class PriorityView {

public:
    PriorityView();

public:
    void addToView(std::weak_ptr<TaskNode> pnode);
    std::vector<std::weak_ptr<TaskNode>> getAllToDate(time_t date);

private:
    static const std::vector<Task::Priority> priorities_by_order;
    std::unordered_map<Task::Priority, multimap_by_date> view;
};


#endif //TODOLIST_PRIORITYVIEW_H
