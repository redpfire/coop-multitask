#include "hello_task.hpp"
#include <iostream>

namespace Task {
    void HelloTask::run() {
        std::cout << "----> Hello World from " << getID() << "!" << std::endl;
    }
}
