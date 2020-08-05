//
// Created by denis on 13.07.20.
//

#include "DatePriorityView.h"



DatePriorityView::DatePriorityView() {
    for (auto prior : priorities_by_order) {
        view[prior] = multimap_by_date();
    }
}

void DatePriorityView::addToView(const std::weak_ptr<TaskNode>& pnode) {
    auto shared_node = pnode.lock();
    multimap_by_date& map_to_insert = view[shared_node->getTask().getPriority()];
    auto inserted_entry =
                map_to_insert.emplace(shared_node->getTask().getDate(), pnode);
    TaskID id = shared_node->getId();
    place_of_[id] = {&map_to_insert, inserted_entry};
}

std::vector<std::weak_ptr<TaskNode>> DatePriorityView::getAllWithConstraint(const time_t& date) {
    std::vector<std::weak_ptr<TaskNode>> result_set;
    time_t current_time;
    time(&current_time); //  get current time
    for (auto prior : priorities_by_order) {
        for (const auto& [its_date, p_task] : view[prior]) {
            if (its_date > date) {
                break;
            }
            result_set.push_back(p_task);
        }
    }
    return result_set;
}

void DatePriorityView::removeFromView(TaskID id) {
    auto [container, iterator] = place_of_[id];
    container->erase(iterator);
}

