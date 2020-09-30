//
// Created by denis on 30.09.20.
//

#ifndef TODOLIST_FILESTREAMSOURCE_H
#define TODOLIST_FILESTREAMSOURCE_H

#include <iostream>

class StreamOwner {

public:
    virtual void setStream(const std::shared_ptr<std::iostream>&) = 0;
    virtual ~StreamOwner() = default;
};


#endif //TODOLIST_FILESTREAMSOURCE_H
