//
// Created by denis on 31.08.20.
//

#ifndef TODOLIST_ALLBUFFERREADER_H
#define TODOLIST_ALLBUFFERREADER_H

#include "cli/ConsoleIO.h"

class AllBufferReader {

public:
    static std::string read(ConsoleIO& io) {
        return io.readLine();
    }
};


#endif //TODOLIST_ALLBUFFERREADER_H
