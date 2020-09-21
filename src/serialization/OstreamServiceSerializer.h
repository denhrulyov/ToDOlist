//
// Created by denis on 18.09.20.
//

#ifndef TODOLIST_OSTREAMSERVICESERIALIZER_H
#define TODOLIST_OSTREAMSERVICESERIALIZER_H

#include "ServiceSerializer.h"
#include <iostream>
#include "task.pb.h"

/*
 * class serializing TaskService to ostream
 *
 * @author Denis Hrulov
 */


class OstreamServiceSerializer {

public:
    /*
     * @param output stream
     * @param reference to TaskService object
     *
     * @return serialized service if OK else nullptr
     */
    virtual void serialize(std::ostream&, TaskServiceInterface& service) = 0;
    virtual ~OstreamServiceSerializer() = default;

};

#endif