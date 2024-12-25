#ifndef THREADPOOLUTIL_H
#define THREADPOOLUTIL_H

#include <sstream>
#include <string>
#include <thread>

class ThreadPoolUtil {
public:
    static int getCurrentThreadId() {
        std::ostringstream oss;
        oss << std::this_thread::get_id() << std::endl;
        return std::stoi(oss.str());
    }
};

#endif //THREADPOOLUTIL_H
