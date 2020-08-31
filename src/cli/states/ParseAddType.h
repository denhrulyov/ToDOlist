//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_PARSEADDTYPE_H
#define TODOLIST_PARSEADDTYPE_H

class ConsoleContext;
class KeywordTokenizerInterface;
#include "ParseState.h"

class ParseAddType : public ParseState {

public:
    explicit ParseAddType();

public:
    void                            print(ConsoleContext& context) override;
    std::shared_ptr<State>          execute(ConsoleContext& context) override;
    void                            help(ConsoleContext&) override;

private:
    std::unique_ptr<KeywordTokenizerInterface> tokenizer_;
};


#endif //TODOLIST_PARSEADDTYPE_H
