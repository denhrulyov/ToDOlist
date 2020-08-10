//
// Created by denis on 19.07.20.
//

#ifndef TODOLIST_TASKID_H
#define TODOLIST_TASKID_H


#include <iostream>
#include <limits>

const unsigned int id_invalid_ = std::numeric_limits<unsigned int>::max();

class TaskID {
public:
    TaskID() : id_(id_invalid_) {}
    explicit TaskID(unsigned int id_create) : id_(id_create) {}

public:
    unsigned int getInt() const {
        return id_;
    }
    bool vaild() const {
        return id_ != id_invalid_;
    }

public:

    // ??????????????
    operator unsigned int () const {
        return id_;
    }

private:
    unsigned int id_;

};


bool operator < (const TaskID&, const TaskID& );
bool operator > (const TaskID&, const TaskID& );
bool operator <= (const TaskID&, const TaskID& );
bool operator >= (const TaskID&, const TaskID& );
bool operator == (const TaskID&, const TaskID& );

#endif //TODOLIST_TASKID_H
