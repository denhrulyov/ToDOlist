//
// Created by denis on 19.07.20.
//

#ifndef TODOLIST_TASKID_H
#define TODOLIST_TASKID_H


#include <iostream>
#include <limits>

class TaskID;
class TaskIDFactory;

class TaskID {
public:
    static const unsigned int id_invalid_;
    TaskID() {
        id_ = id_invalid_;
    }

public:
    unsigned int getInt() const {
        return id_;
    }
    bool vaild() {
        return id_ != id_invalid_;
    }

public:
    bool operator < (TaskID rhs) const {
        return id_ < rhs.id_;
    }
    bool operator > (TaskID rhs) const {
        return id_ > rhs.id_;
    }
    bool operator <= (TaskID rhs) const {
        return id_ <= rhs.id_;
    }
    bool operator >= (TaskID rhs) const {
        return id_ >= rhs.id_;
    }
    bool operator == (TaskID rhs) const {
        return id_ == rhs.id_;
    }
    // ??????????????
    operator unsigned int () const {
        return id_;
    }



private:
    explicit TaskID(unsigned int id_create) : id_(id_create) {}

private:
    unsigned int id_;

    friend class TaskIDFactory;
};

class TaskIDFactory {
public:
    explicit TaskIDFactory(unsigned int initial_id = 0) : current_id_(initial_id) {};
    TaskID generateID();

private:
    unsigned int current_id_;
};

#endif //TODOLIST_TASKID_H
