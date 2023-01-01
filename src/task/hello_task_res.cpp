#include "hello_task_res.hpp"
#include <iostream>

// this is some simple mockery with dice rolling to simulate
// what a real task could do with shared resources
namespace Task {
    void HelloTaskWithResource::run() {
        std::cout << "----> Hello World from " << getID() << "!" << std::endl;

        const bool hasLock = resource_.getBearerID() == getID();
        if (hasLock) {
            // if we've locked the resource, roll if we should unlock it or
            // maybe say fuck you to other tasks
            if (rand() % 5 == 0) {
                resource_.unlock(this);

                if ((double)rand() / RAND_MAX < 0.35) { // our job could be done so roll if we should terminate
                    changeState(TaskState::TERMINATED);
                }
            }

            return;
        }

        if (!resource_.lockOrFail(this)) {
            // yay locked, now we noop!
        }
        else {
            // nay, some other task has claimed the lock... it's critical to
            // claim it so we'll wait
            changeState(TaskState::WAITING);
        }
    }
}
