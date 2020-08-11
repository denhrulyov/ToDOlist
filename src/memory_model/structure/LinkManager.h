//
// Created by denis on 03.08.20.
//

#ifndef TODOLIST_LINKMANAGER_H
#define TODOLIST_LINKMANAGER_H

#include "LinkManagerInterface.h"
#include "memory_model/view/PriorityViewInterface.h"

class LinkManager : public LinkManagerInterface {

public:
    LinkManager(PriorityViewInterface<BoostDate>& by_time,
                PriorityViewInterface<std::string>& by_label);

public:
    void linkSubTask(const std::weak_ptr<TaskNode>& main_task, const std::weak_ptr<TaskNode>& sub_task) override;
    void setLinks(const std::weak_ptr<TaskNode>& node) override;
    void removeLinks(const std::weak_ptr<TaskNode>& node) override;
    void moveInboundLinks(const std::weak_ptr<TaskNode>& from, const std::weak_ptr<TaskNode>& to) override;

private:
    PriorityViewInterface<BoostDate> &by_time_;
    PriorityViewInterface<std::string> &by_label_;
};


#endif //TODOLIST_LINKMANAGER_H
