/**
 * File: chrome.h
 * Author: xiaoran
 * Email: xiaoranone@126.com
 * Time: 2019-08-09 PM.
 */

#ifndef DATAWHALE_CHROME_H
#define DATAWHALE_CHROME_H

#include <memory.h>
#include "stack.h"
#include "queue.h"

namespace datawhale {

class Chrome {
public:

    Chrome(int _depth = 3) : depth(_depth) { }
    ~Chrome() {}

    void go(std::string url) {
        op.push(url);
    }

    std::string back() {
        std::string t = op.top();
        backup.push(t);
        op.pop();
        return t;
    }

    std::string front() {
        std::string s = backup.top();
        backup.pop();
        op.push(s);
        return s;
    }

private:
    Stack<std::string> op;
    Stack<std::string> backup;
    int depth;
};

} // namespace datawhale

#endif // DATAWHALE_CHROME_H