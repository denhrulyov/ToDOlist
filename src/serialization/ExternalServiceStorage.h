//
// Created by denis on 18.09.20.
//

#ifndef TODOLIST_EXTERNALSERVICESTORAGE_H
#define TODOLIST_EXTERNALSERVICESTORAGE_H

#include "ServiceSerializer.h"
#include "ServiceDeserializer.h"

class ExternalServiceStorage {
    virtual ServiceSerializer getSerializer() = 0;
    virtual ServiceDeserializer getDeserializer() = 0;
};


#endif //TODOLIST_EXTERNALSERVICESTORAGE_H
