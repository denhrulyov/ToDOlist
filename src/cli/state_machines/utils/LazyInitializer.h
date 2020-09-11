//
// Created by denis on 07.09.20.
//

#ifndef TODOLIST_LAZYINITIALIZER_H
#define TODOLIST_LAZYINITIALIZER_H

#include "InitializerInterface.h"

template <class Base, class T>
class LazyInitializer : public InitializerInterface<Base> {

public:
    using Creator = typename InitializerInterface<Base>::Creator;

public:
    explicit LazyInitializer(const Creator& creator)
    :
    InitializerInterface<Base>(creator),
    initialized_(false) {}

public:
    std::shared_ptr<Base> getValue() override {
        if (!initialized_) {
            initialized_ = true;
            object_ = this->getCreator()();
        }
        return object_;
    }

    static LazyInitializer createDefault() {
        return LazyInitializer(
                Creator([] () {
                    return std::make_shared<T>();
                })
        );
    }

private:
    std::shared_ptr<Base>   object_;
    bool                    initialized_;
};


#endif //TODOLIST_LAZYINITIALIZER_H
