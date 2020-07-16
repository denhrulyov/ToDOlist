//
// Created by denis on 13.07.20.
//

#ifndef TODOLIST_PRIORITYVIEW_H
#define TODOLIST_PRIORITYVIEW_H
#include "TaskNode.h"
#include "TaskEntity.h"
#include <functional>
#include <set>

namespace priority_view {

    using order_cmp_type = std::function<
                                        bool(std::weak_ptr<TaskNode>,
                                             std::weak_ptr<TaskNode>)
                                        >;
    using multiset_type = std::multiset<
                                        std::weak_ptr<TaskNode>,
                                        order_cmp_type
                                        >;

    const order_cmp_type cmp_time =
            [] (const std::weak_ptr<TaskNode>& lhs, const std::weak_ptr<TaskNode>& rhs) {
                return lhs.lock()->getTask()->date < rhs.lock()->getTask()->date;
            }
    ;
}

class PriorityView {

public:
    PriorityView();

public:
    void addToView(std::weak_ptr<TaskNode> pnode);
    std::vector<TaskEntity> getAllToDate(time_t date);

private:
    static const std::vector<Task::Priority> priorities_by_order;
    std::unordered_map<Task::Priority, priority_view::multiset_type> view;
};


#endif //TODOLIST_PRIORITYVIEW_H
