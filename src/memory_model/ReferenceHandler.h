//
// Created by denis on 03.08.20.
//

#ifndef TODOLIST_REFERENCEHANDLER_H
#define TODOLIST_REFERENCEHANDLER_H

#include "TaskNode.h"
#include "PriorityViewInterface.h"

class ReferenceHandler {

public:
    ReferenceHandler(PriorityViewInterface<time_t>& by_time,
                     PriorityViewInterface<std::string>& by_label);

public:
    void linkSubTask(const std::shared_ptr<TaskNode>& main_task, const std::shared_ptr<TaskNode>& sub_task);
    void setReferences(const std::shared_ptr<TaskNode>& node);
    void removeRefrences(const std::shared_ptr<TaskNode>& node);
    void moveInternalRefrences(const std::shared_ptr<TaskNode>& from, const std::shared_ptr<TaskNode>& to);
    void copyExternalReferences(const std::shared_ptr<TaskNode>& from, const std::shared_ptr<TaskNode>& to);

private:
    PriorityViewInterface<time_t> &by_time_;
    PriorityViewInterface<std::string> &by_label_;
};


#endif //TODOLIST_REFERENCEHANDLER_H
