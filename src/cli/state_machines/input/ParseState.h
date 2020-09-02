//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_PARSESTATE_H
#define TODOLIST_PARSESTATE_H


class ConsoleContext;

class ParseState {

public:
    enum class Event {
        SUCCESS,
        FAIL,
        EXIT
    };

public:
    explicit ParseState();

public:
    virtual void                         print(ConsoleContext&) = 0;
    virtual Event                        execute(ConsoleContext&) = 0;
    virtual void                         help(ConsoleContext&) = 0;

    virtual ~ParseState() = default;
};


#endif //TODOLIST_PARSESTATE_H
