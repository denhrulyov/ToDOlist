//
// Created by denis on 29.07.20.
//

#ifndef TODOLIST_TAGPRIORITYVIEW_H
#define TODOLIST_TAGPRIORITYVIEW_H

#include <map>
#include <unordered_map>
#include "PriorityViewInterface.h"


using simple_priority_view = std::unordered_map<Task::Priority, std::vector<std::weak_ptr<TaskNode>>>;
using tag_priority_view = std::map<std::string, simple_priority_view>;

class TagPriorityView : PriorityViewInterface<std::string> {

public:
    void addToView(const std::weak_ptr<TaskNode>&) override;
    std::vector<std::weak_ptr<TaskNode>> getAll(const std::string& tag) override;
    ~TagPriorityView() = default;

private:
     tag_priority_view view_;
};


#endif //TODOLIST_TAGPRIORITYVIEW_H
