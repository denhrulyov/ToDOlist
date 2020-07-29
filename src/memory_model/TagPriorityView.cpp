//
// Created by denis on 29.07.20.
//

#include "TagPriorityView.h"

const simple_priority_view blank_priority_container =
        {
          {Task::Priority::FIRST    , std::vector<std::weak_ptr<TaskNode>>()   },
          {Task::Priority::SECOND   , std::vector<std::weak_ptr<TaskNode>>()   },
          {Task::Priority::THIRD    , std::vector<std::weak_ptr<TaskNode>>()   },
          {Task::Priority::NONE     , std::vector<std::weak_ptr<TaskNode>>()   }
        };

auto filter(const std::vector<std::weak_ptr<TaskNode>>& ls) {
    std::vector<std::weak_ptr<TaskNode>> filtered;
    for (const auto& ptr : ls) {
        if (!ptr.expired()) {
            filtered.push_back(ptr);
        }
    }
    return filtered;
}


auto collect(const simple_priority_view& priority_lists) {
    std::vector<std::weak_ptr<TaskNode>> collected;
    for (const auto& ls : priority_lists) {
        auto ls_valid = filter(ls.second);
        std::copy(  ls_valid.begin(), ls_valid.end(),
                    std::back_inserter(collected)    );
    }
    return collected;
}


/************************************************/

void TagPriorityView::addToView(const std::weak_ptr<TaskNode>& node) {
    const Task& task = node.lock()->getTask();
    if (view_.count(task.label) == 0) {
        view_[task.label] = blank_priority_container;
    }
    view_[task.label][task.priority].push_back(node);
}

std::vector<std::weak_ptr<TaskNode>> TagPriorityView::getAllWithTag(const std::string &tag) {
    return  view_.count(tag) ?
            collect(view_.at(tag)) :
            std::vector<std::weak_ptr<TaskNode>>();
}
