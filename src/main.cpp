#include <iostream>


#include "cli/CLI.h"
#include <boost/date_time.hpp>

using namespace boost::gregorian;

int main() {
    todo_list_cli::createCLI().run();
    return 0;
}
