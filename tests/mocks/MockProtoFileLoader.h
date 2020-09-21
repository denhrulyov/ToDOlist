//
// Created by denis on 21.09.20.
//

#ifndef TODOLIST_MOCKPROTOFILELOADER_H
#define TODOLIST_MOCKPROTOFILELOADER_H

#include "serialization/IstreamProtoFileLoader.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

template<class T_proto>
class MockProtoFileLoader : public IstreamProtoFileLoader<T_proto> {

public:
    MOCK_METHOD(std::optional<T_proto>, load, (std::istream&), (override));
};


#endif //TODOLIST_MOCKPROTOFILELOADER_H
