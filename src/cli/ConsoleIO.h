//
// Created by denis on 20.08.20.
//

#ifndef TODOLIST_CONSOLEIO_H
#define TODOLIST_CONSOLEIO_H

#include <iostream>

class ConsoleIO {

public:
    void            log(const std::string& message);
    std::string     read();
    std::string     readRestBuffer();
    void            requestInputLine();
public:
    bool            isEmpty();
    void            clear();

private:
    void            clearPrefixSpaces();

private:
    std::string buffer_;
};


#endif //TODOLIST_CONSOLEIO_H
