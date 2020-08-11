//
// Created by denis on 19.07.20.
//

#include "TaskID.h"


bool operator < (const TaskID& lhs, const TaskID& rhs) {
    return lhs.getInt() < rhs.getInt();
}
bool operator > (const TaskID& lhs, const TaskID& rhs) {
    return lhs.getInt() > rhs.getInt();
}
bool operator <= (const TaskID& lhs, const TaskID& rhs) {
    return lhs.getInt() <= rhs.getInt();
}
bool operator >= (const TaskID& lhs, const TaskID& rhs) {
    return lhs.getInt() >= rhs.getInt();
}
bool operator == (const TaskID& lhs, const TaskID& rhs) {
    return lhs.getInt() == rhs.getInt();
}