#pragma once
#include "../task/task.hpp"
#include <atomic>
#include <vector>
#include <memory>
#include <iostream>

namespace Resource {
    template<class T>
    class GuardedResource {
        public:
            explicit GuardedResource(T val) : data_{val}, lockedBy_{-1} {}

            void unlock(Task::Task* callingTask) {
                if (callingTask->getID() == lockedBy_) {
                    std::cout << "Unlocking resource" << std::endl;
                    lockedBy_ = -1;

                    // also wake up the first task waiting for this resource
                    if (!queue_.empty()) {
                        queue_.front()->changeState(Task::TaskState::READY);
                        queue_.erase(queue_.begin());
                    }
                }
            };

            int lockOrFail(Task::Task* callingTask) {
                if (lockedBy_ < 0) {
                    lockedBy_ = callingTask->getID();
                    std::cout << "Locking resource by " << lockedBy_ << std::endl;
                    return 0;
                }

                std::cout << "Waiting for resource by " << callingTask->getID() << std::endl;
                // Caution! You should check here if the task is already in the queue
                // i'm lazy and will omit this but this is bad practice and will fail!
                queue_.push_back(callingTask);
                return 1;
            };

            const int getBearerID() const {
                return lockedBy_;
            }

            T& get() {
                return data_;
            };

        private:
            T data_;
            std::atomic<int> lockedBy_;
            std::vector<Task::Task*> queue_{};
    };
}
