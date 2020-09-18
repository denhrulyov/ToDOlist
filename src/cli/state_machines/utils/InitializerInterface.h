//
// Created by denis on 07.09.20.
//

#ifndef TODOLIST_INITIALIZERINTERFACE_H
#define TODOLIST_INITIALIZERINTERFACE_H

#include <memory>
#include <functional>

template <class Base>
class InitializerInterface {

public:
    using Creator = std::function<std::shared_ptr<Base>(void)>;

public:
    explicit InitializerInterface(const Creator& creator) : init_object_(creator) {}

public:
    Creator getCreator() {
        return init_object_;
    }
    virtual std::shared_ptr<Base> getValue() = 0;
    virtual ~InitializerInterface() = default;

private:
    Creator init_object_;
};


#endif //TODOLIST_INITIALIZERINTERFACE_H
