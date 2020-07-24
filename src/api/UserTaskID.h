//
// Created by denis on 20.07.20.
//

#ifndef TODOLIST_USERTASKID_H
#define TODOLIST_USERTASKID_H

#include <memory>
#include <vector>
#include "memory_model/TaskNode.h"

class UserTaskID {

public:
    UserTaskID() :
    level_index_({})
    {}
    explicit UserTaskID(const std::vector<std::size_t>& level_index) :
    level_index_(level_index)
    {}

    std::vector<std::size_t> getLevelIndices();

private:
    std::vector<std::size_t> level_index_;
};


#endif //TODOLIST_USERTASKID_H
