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

std::vector<std::weak_ptr<TaskNode>> DatePriorityView::getAllWithConstraint(const Gregorian& date) {
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

std::vector<std::weak_ptr<TaskNode>> DatePriorityView::getAllSortedByFirstParam() {
    std::vector<std::weak_ptr<TaskNode>> result_set;
    std::map<Task::Priority, multimap_by_date::iterator> prior_iterators;
    for (Task::Priority prior : priorities_by_order) {
        prior_iterators[prior] = view[prior].begin();
    }
    bool any_item_left = true;
    while (any_item_left) {
        any_item_left = false;
        Gregorian min_date = boost::gregorian::day_clock::local_day() +
                             boost::gregorian::years(100);
        Task::Priority best = Task::Priority::NONE;
        for (auto cur_prior : priorities_by_order) {
            auto cur = prior_iterators[cur_prior];
            if (cur != view[cur_prior].end()) {
                any_item_left = true;
                if (cur->first < min_date) {
                    min_date = cur->first;
                    best = cur_prior;
                }
            }
        }
        if (any_item_left) {
            result_set.push_back(prior_iterators[best]->second);
            prior_iterators[best]++;
        }
    }
    return result_set;
}

