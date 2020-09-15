//
// Created by denis on 20.08.20.
//

#ifndef TODOLIST_TASKTABLEIO_H
#define TODOLIST_TASKTABLEIO_H

class ConsoleContextInterface;

namespace task_table_io {
    /*
     * function for printing task table to console
     *
     * @param context containing data
     *
     */
    void print(ConsoleContextInterface& context);
}


#endif //TODOLIST_TASKTABLEIO_H
