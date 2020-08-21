//
// Created by denis on 20.08.20.
//

#ifndef TODOLIST_CONSOLEIO_H
#define TODOLIST_CONSOLEIO_H

#include <iostream>

class ConsoleIO {

public:
    void log(const std::string& message);
    std::string read();
};


#endif //TODOLIST_CONSOLEIO_H
