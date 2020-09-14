//
// Created by denis on 31.08.20.
//

#include "KeywordTokenizer.h"
#include "Keyword.h"
#include <map>

Keyword  KeywordTokenizer::read(ConsoleIOInterface &io) {
    std::string input = io.readWord();
    std::map<std::string, Keyword > match
    {
            {"add",       Keyword::ADD},
            {"show",      Keyword::SHOW},
            {"delete",    Keyword::DELETE},
            {"postpone",  Keyword::POSTPONE},
            {"today",     Keyword::TODAY},
            {"this_week", Keyword::THIS_WEEK},
            {"all",       Keyword::ALL},
            {"current_list", Keyword::CURRENT_LIST},
            {"tag",       Keyword::TAG},
            {"task",      Keyword::TASK},
            {"subtask",   Keyword::SUBTASK},
            {"Y",         Keyword::YES},
            {"n",         Keyword::NO}
    };
    if (match.count(input)) {
        return match[input];
    } else {
        return Keyword::UNKNOWN;
    }
}
