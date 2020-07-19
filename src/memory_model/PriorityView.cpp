//
// Created by denis on 13.07.20.
//

#include "PriorityView.h"

const std::vector<Task::Priority> PriorityView::priorities_by_order = { Task::Priority::FIRST, Task::Priority::SECOND, Task::Priority::THIRD, Task::Priority::NONE };

PriorityView::PriorityView() {
    for (auto prior : priorities_by_order) {
        view[prior] = multimap_by_date();
    }
}

void PriorityView::addToView(std::weak_ptr<TaskNode> pnode) {
    auto pnode_access = pnode.lock();
    view[pnode_access->getTask().priority].emplace(pnode.lock()->getTask().date, pnode);
}

std::vector<TaskDTO> PriorityView::getAllToDate(time_t date) {
    std::vector<TaskDTO> result_set;
    time_t current_time;
    time(&current_time); //  get current time
    for (auto prior : priorities_by_order) {
        for (const auto& date_and_task : view[prior]) {
            auto p_task = date_and_task.second;
            time_t its_date = date_and_task.first;
            if (p_task.expired()) {
                continue;
            }
            auto ptask_access = p_task.lock();
            if (its_date > date) {
                break;
            }
            result_set.emplace_back(ptask_access->getId(), ptask_access->getTask());
        }
    }
    return result_set;
}

