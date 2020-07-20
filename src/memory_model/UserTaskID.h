//
// Created by denis on 20.07.20.
//

#ifndef TODOLIST_USERTASKID_H
#define TODOLIST_USERTASKID_H

#include <vector>

class UserTaskID {

public:
    explicit UserTaskID(const std::vector<std::size_t>& level_index) :
    level_index_(level_index) {}
    std::vector<std::size_t> getLevelIndices();

private:
    std::vector<std::size_t> level_index_;
};


#endif //TODOLIST_USERTASKID_H
