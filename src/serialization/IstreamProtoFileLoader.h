//
// Created by denis on 21.09.20.
//

#ifndef TODOLIST_ISTREAMPROTOFILELOADER_H
#define TODOLIST_ISTREAMPROTOFILELOADER_H

#include <iostream>
#include <optional>

/*
 * class wrapping parsing Protobuf objects from istream
 *
 * @author Denis Hrulov
 */

template<class T_proto>
class IstreamProtoFileLoader {

public:
    /*
     * @param input stream
     *
     * @return Protobuf object if succeed to parse else std::nullopt
     */
    virtual std::optional<T_proto> load(std::istream&);
};

template<class T_proto>
std::optional<T_proto> IstreamProtoFileLoader<T_proto>::load(std::istream &in) {
    T_proto proto;
    if (!proto.ParseFromIstream(&in)) {
        return std::nullopt;
    }
    return proto;
}


#endif //TODOLIST_ISTREAMPROTOFILELOADER_H
