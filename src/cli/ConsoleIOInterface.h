//
// Created by denis on 04.09.20.
//

#ifndef TODOLIST_CONSOLEIOINTERFACE_H
#define TODOLIST_CONSOLEIOINTERFACE_H


#include <string>
class ConsoleIOInterface {

public:
    virtual void            putLine(const std::string& message) = 0;
    virtual std::string     readWord() = 0;
    virtual std::string     readRestBuffer() = 0;
    virtual void            requestInputLine() = 0;
public:
    virtual bool            isEmpty() = 0;
    virtual void            clear() = 0;

public:
    virtual std::string_view seeBuffer() = 0;
public:
    virtual ~ConsoleIOInterface() = default;
};


#endif //TODOLIST_CONSOLEIOINTERFACE_H
