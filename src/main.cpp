#include <iostream>


#include "cli/CLI.h"
#include <boost/date_time.hpp>

using namespace boost::gregorian;

int main() {
    operator<<(std::cout, std::string("sss"));
    todo_list_cli::createCLI().run();
    return 0;
}
