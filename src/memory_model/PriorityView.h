//
// Created by denis on 13.07.20.
//

#ifndef TODOLIST_PRIORITYVIEW_H
#define TODOLIST_PRIORITYVIEW_H
#include "PriorityViewInterface.h"
#include "api/TaskDTO.h"
#include <functional>
#include <set>


using multimap_by_date = std::multimap<
                                    time_t,
                                    std::weak_ptr<TaskNode>
                                    >;

const std::vector<Task::Priority> priorities_by_order = { Task::Priority::FIRST,
                                                          Task::Priority::SECOND,
                                                          Task::Priority::THIRD,
                                                          Task::Priority::NONE };

class PriorityView : public PriorityViewInterface {

public:
    PriorityView();

public:
    void addToView(std::weak_ptr<TaskNode> pnode) override ;
    std::vector<std::weak_ptr<TaskNode>> getAllToDate(time_t date) override;

private:
    std::unordered_map<Task::Priority, multimap_by_date> view;

public:
    ~PriorityView() override = default;
};


#endif //TODOLIST_PRIORITYVIEW_H
