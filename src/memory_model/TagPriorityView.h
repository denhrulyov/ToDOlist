//
// Created by denis on 29.07.20.
//

#ifndef TODOLIST_TAGPRIORITYVIEW_H
#define TODOLIST_TAGPRIORITYVIEW_H

#include <map>
#include <unordered_map>
#include "PriorityViewInterface.h"
namespace tag_view {

    using task_list = std::list<std::weak_ptr<TaskNode>>;
    using simple_priority_view = std::unordered_map<Task::Priority, task_list>;
    using tag_map = std::map<std::string, simple_priority_view>;
    using id_map = std::map<TaskID, std::pair<task_list *, task_list::iterator>>;
}

/********************************************************************************************/

class TagPriorityView : public PriorityViewInterface<std::string> {

public:
    void                                        addToView(const std::weak_ptr<TaskNode>&) override;
    std::vector<std::weak_ptr<TaskNode>>        getAllWithConstraint(const std::string& tag) override;
    void                                        removeFromView(TaskID id) override;
    ~TagPriorityView() = default;

private:
    tag_view::tag_map                           view_;
    tag_view::id_map                            place_of_;
};


#endif //TODOLIST_TAGPRIORITYVIEW_H
