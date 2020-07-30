//
// Created by denis on 29.07.20.
//

#ifndef TODOLIST_TAGPRIORITYVIEW_H
#define TODOLIST_TAGPRIORITYVIEW_H

#include <map>
#include <unordered_map>
#include "PriorityViewInterface.h"


using simple_priority_view =    std::unordered_map<Task::Priority, std::vector<std::weak_ptr<TaskNode>>>;
using tag_map =                 std::map<std::string, simple_priority_view>;
using id_map =                  std::map<TaskID, tag_map::iterator>;

class TagPriorityView : PriorityViewInterface<std::string> {

public:
    void                                        addToView(const std::weak_ptr<TaskNode>&) override;
    std::vector<std::weak_ptr<TaskNode>>        getAll(const std::string& tag) override;
    void                                        removeFromView(TaskID id) override;
    ~TagPriorityView() = default;

private:
    tag_map     view_;
    id_map      place_of_;
};


#endif //TODOLIST_TAGPRIORITYVIEW_H
