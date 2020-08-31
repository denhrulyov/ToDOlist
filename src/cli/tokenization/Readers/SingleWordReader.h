//
// Created by denis on 31.08.20.
//

#ifndef TODOLIST_SINGLEWORDREADER_H
#define TODOLIST_SINGLEWORDREADER_H

#include "cli/ConsoleIO.h"

class SingleWordReader {

public:
    static std::string read(ConsoleIO& io) {
        return io.read();
    }
};


#endif //TODOLIST_SINGLEWORDREADER_H
