//
// Created by denis on 29.07.20.
//

#include "TagPriorityView.h"

using namespace tag_view;
using Prior = Task::Priority;

const simple_priority_view blank_priority_container =
        {
          {Task::Priority::FIRST    , task_list()   },
          {Task::Priority::SECOND   , task_list()   },
          {Task::Priority::THIRD    , task_list()   },
          {Task::Priority::NONE     , task_list()   }
        };


auto collect(const simple_priority_view& priority_lists) {
    std::vector<std::weak_ptr<TaskNode>> collected;
    for (const auto& prior : { Prior::FIRST, Prior::SECOND, Prior::THIRD, Prior::NONE }) {
        if (priority_lists.count(prior) == 0) {
            continue;
        }
        auto task_ls = priority_lists.at(prior);
        std::copy(  task_ls.begin(), task_ls.end(),
                    std::back_inserter(collected)    );
    }
    return collected;
}


/************************************************/

void TagPriorityView::addToView(const std::weak_ptr<TaskNode>& node) {
    // 1. Prepare insertion
    auto shared_node = node.lock();
    const Task& task = shared_node->getTask();
    if (view_.count(task.getLabel()) == 0) {
        view_[task.getLabel()] = blank_priority_container;
    }
    TaskID id = shared_node->getId();
    task_list& list_to_insert = view_[task.getLabel()][task.getPriority()];
    // 2. Insert the task into view
    list_to_insert.push_back(node);
    // 3. Memorize place of pointer in our view
    place_of_[id] = std::make_pair(&list_to_insert, std::prev(list_to_insert.end()));
}

std::vector<std::weak_ptr<TaskNode>> TagPriorityView::getAll(const std::string &tag) {
    return  view_.count(tag) ?
            collect(view_.at(tag)) :
            std::vector<std::weak_ptr<TaskNode>>();
}

void TagPriorityView::removeFromView(TaskID id) {
    auto [container, iterator] = place_of_[id];
    container->erase(iterator);
}
