//
// Created by denis on 31.08.20.
//

#include "cli/ConsoleIO.h"
#include "KeywordTokenizer.h"
#include <map>

Token KeywordTokenizer::read(ConsoleIO &io) {
    std::string input = io.readWord();
    std::map<std::string, TypeToken> match
    {
            {"add", TypeToken::ADD},
            {"show", TypeToken::SHOW},
            {"delete", TypeToken::DELETE},
            {"postpone", TypeToken::POSTPONE},
            {"today",    TypeToken::TODAY},
            {"this_week",TypeToken::THIS_WEEK},
            {"all",      TypeToken::SUBTASK},
            {"tag",      TypeToken::TAG},
            {"task",    TypeToken::TASK},
            {"subtask", TypeToken::SUBTASK}
    };
    if (match.count(input)) {
        return Token::create(match[input]);
    } else {
        return Token::create(TypeToken::UNKNOWN);
    }
}
