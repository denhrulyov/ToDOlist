//
// Created by denis on 13.07.20.
//

#include "PriorityView.h"



PriorityView::PriorityView() {
    for (auto prior : priorities_by_order) {
        view[prior] = multimap_by_date();
    }
}

void PriorityView::addToView(std::weak_ptr<TaskNode> pnode) {
    auto pnode_access = pnode.lock();
    view[pnode_access->getTask().priority].emplace(pnode.lock()->getTask().date, pnode);
}

std::vector<std::weak_ptr<TaskNode>> PriorityView::getAllToDate(time_t date) {
    std::vector<std::weak_ptr<TaskNode>> result_set;
    time_t current_time;
    time(&current_time); //  get current time
    for (auto prior : priorities_by_order) {
        for (const auto& [its_date, p_task] : view[prior]) {
            if (p_task.expired()) {
                continue;
            }
            auto ptask_access = p_task.lock();
            if (its_date > date) {
                break;
            }
            result_set.push_back(p_task);
        }
    }
    return result_set;
}

