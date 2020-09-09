//
// Created by denis on 20.08.20.
//

#ifndef TODOLIST_CONSOLEIO_H
#define TODOLIST_CONSOLEIO_H

#include <iostream>
#include "ConsoleIOInterface.h"

class ConsoleIO : public ConsoleIOInterface {

public:
    ConsoleIO(std::istream&, std::ostream&);

public:
    void            putLine(const std::string& message) override ;
    std::string     readWord() override ;
    std::string     readRestBuffer() override ;
    void            requestInputLine() override ;

public:
    bool            isEmpty() override ;
    void            clear() override ;

public:
    std::string_view seeBuffer() override;

private:
    void            clearPrefixSpaces();

private:
    std::istream& in_;
    std::ostream& out_;
    std::string buffer_;
};


#endif //TODOLIST_CONSOLEIO_H
