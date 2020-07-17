//
// Created by denis on 13.07.20.
//

#include "PriorityView.h"

const std::vector<Task::Priority> PriorityView::priorities_by_order = { Task::Priority::FIRST, Task::Priority::SECOND, Task::Priority::THIRD, Task::Priority::NONE };

PriorityView::PriorityView() {
    for (auto prior : priorities_by_order) {
        view[prior] = priority_view::multiset_type(priority_view::cmp_time);
    }
}

void PriorityView::addToView(std::weak_ptr<TaskNode> pnode) {
    auto pnode_access = pnode.lock();
    view[pnode_access->getTask().priority].insert(pnode);
}

std::vector<TaskEntity> PriorityView::getAllToDate(time_t date) {
    std::vector<TaskEntity> result_set;
    time_t current_time;
    time(&current_time); //  get current time
    for (auto prior : priorities_by_order) {
        for (const auto& ptask : view[prior]) {
            if (ptask.expired()) {
                continue;
            }
            auto ptask_access = ptask.lock();
            if (date < ptask_access->getTask().date) {
                break;
            }
            result_set.emplace_back(ptask_access->getId(), ptask_access->getTask());
        }
    }
    return result_set;
}

