//
// Created by denis on 31.08.20.
//

#include "cli/ConsoleIO.h"
#include "KeywordTokenizer.h"
#include <map>

Token KeywordTokenizer::read(ConsoleIO &io) {
    std::string input = io.readWord();
    std::map<std::string, Keyword> match
    {
            {"add",       Keyword::ADD},
            {"show",      Keyword::SHOW},
            {"delete",    Keyword::DELETE},
            {"postpone",  Keyword::POSTPONE},
            {"today",     Keyword::TODAY},
            {"this_week", Keyword::THIS_WEEK},
            {"all",       Keyword::SUBTASK},
            {"tag",       Keyword::TAG},
            {"task",      Keyword::TASK},
            {"subtask",   Keyword::SUBTASK}
    };
    if (match.count(input)) {
        return Token::create(match[input]);
    } else {
        return Token::create(Keyword::UNKNOWN);
    }
}
