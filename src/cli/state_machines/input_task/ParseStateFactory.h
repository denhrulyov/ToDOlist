//
// Created by denis on 07.09.20.
//

#ifndef TODOLIST_PARSESTATEFACTORY_H
#define TODOLIST_PARSESTATEFACTORY_H

#include "ParseStateFactoryInterface.h"

class ParseStateFactory : public ParseStateFactoryInterface {



public:
    explicit ParseStateFactory();

public:
    std::shared_ptr<ParseState> getNextState() override ;

private:
    struct InitializerInterface {
        virtual std::shared_ptr<ParseState> get() = 0;
        virtual ~InitializerInterface() = default;
    };

    template<class T>
    struct Initializer : public InitializerInterface {
        std::shared_ptr<ParseState> get() override {
            return std::make_shared<T>();
        }
    };

private:
    using initializer_array_type =      std::array<std::unique_ptr<InitializerInterface>, 4>;
    initializer_array_type              states_;
    initializer_array_type::iterator    current_state_;
};


#endif //TODOLIST_PARSESTATEFACTORY_H
