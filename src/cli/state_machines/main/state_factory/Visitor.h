//
// Created by denis on 03.09.20.
//

#ifndef TODOLIST_VISITOR_H
#define TODOLIST_VISITOR_H

template <class T>
class Visitor {
public:
    std::shared_ptr<State> visit(StateFactoryInterface& factory) {
        return factory.getInstance(*this);
    }
};


#endif //TODOLIST_VISITOR_H
