//
// Created by denis on 04.09.20.
//

#ifndef TODOLIST_CONSOLEIOINTERFACE_H
#define TODOLIST_CONSOLEIOINTERFACE_H


/*
 * Class for manual line-by-line console input-output
 *
 * @author Denis Hrulov
 */

#include <string>
class ConsoleIOInterface {

public:
    /*
     * Writes line to console
     *
     * @param message to write
     */
    virtual void            putLine(const std::string& message) = 0;
    /*
     * ignores whitespaces until first other symbol
     * and reads word to the first whitespace
     *
     */
    virtual std::string     readWord() = 0;
    /*
     * reads rest of buffer, ignoring whitespaces until first other symbol
     *
     * @return word read from console
     */
    virtual std::string     readRestBuffer() = 0;
    /*
     * console waiting for input, reads all until newline and sets buffer content to read data
     *
     * @return rest of buffer from first non-whitespace
     */
    virtual void            requestInputLine() = 0;

public:
    /*
     * indicates whether buffer is of length of zero
     *
     * @return is buffer empty
     */
    virtual bool            isEmpty() = 0;
    /*
     * clears input buffer
     */
    virtual void            clear() = 0;

public:
    void operator = (const ConsoleIOInterface& rhs) = delete;

public:
    virtual std::string_view seeBuffer() = 0;
public:
    virtual ~ConsoleIOInterface() = default;
};


#endif //TODOLIST_CONSOLEIOINTERFACE_H
