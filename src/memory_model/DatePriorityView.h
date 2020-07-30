//
// Created by denis on 13.07.20.
//

#ifndef TODOLIST_DATEPRIORITYVIEW_H
#define TODOLIST_DATEPRIORITYVIEW_H
#include "PriorityViewInterface.h"
#include "api/TaskDTO.h"
#include <functional>
#include <set>



const std::vector<Task::Priority> priorities_by_order = { Task::Priority::FIRST,
                                                          Task::Priority::SECOND,
                                                          Task::Priority::THIRD,
                                                          Task::Priority::NONE };

using multimap_by_date = std::multimap<
        time_t,
        std::weak_ptr<TaskNode>
>;

using multimap_iterator_type = decltype(multimap_by_date().emplace(0, std::shared_ptr<TaskNode>(nullptr)));

using priority_map =    std::map<Task::Priority, multimap_by_date>;
using id_map =          std::map<TaskID, std::pair<multimap_by_date*, multimap_iterator_type>>;

/********************************************************************************************/

class DatePriorityView : public PriorityViewInterface<time_t> {

public:
    DatePriorityView();

public:
    void                                        addToView(const std::weak_ptr<TaskNode>& pnode) override ;
    std::vector<std::weak_ptr<TaskNode>>        getAll(const time_t& date) override;
    void                                        removeFromView(TaskID id) override;
private:
    priority_map                                view;
    id_map                                      place_of_;

public:
    ~DatePriorityView() override = default;
};


#endif //TODOLIST_DATEPRIORITYVIEW_H
