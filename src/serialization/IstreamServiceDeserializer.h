//
// Created by denis on 18.09.20.
//

#ifndef TODOLIST_ISTREAMSERVICEDESERIALIZER_H
#define TODOLIST_ISTREAMSERVICEDESERIALIZER_H

#include "ServiceDeserializer.h"

/*
 * class deserializing TaskService from istream
 *
 * @author Denis Hrulov
 */

class IstreamServiceDeserializer {

public:
    /*
     * @param input stream
     *
     * @return serialized service if OK else nullptr
     */
    virtual std::unique_ptr<TaskServiceInterface> deserialize(std::istream&) = 0;
    virtual ~IstreamServiceDeserializer() = default;
};


#endif //TODOLIST_ISTREAMSERVICEDESERIALIZER_H
