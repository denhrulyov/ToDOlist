//
// Created by denis on 18.08.20.
//

#include "ParseTask.h"
#include "cli/ConsoleContext.h"
#include "cli/tokenization/MultiwordDataTokenizer.h"

ParseTask::ParseTask()
:
ParseState(),
tokenizer_(std::move(std::make_unique<MultiwordDataTokenizer>()))
{}

