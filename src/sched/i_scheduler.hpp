#pragma once
#include "../task/task.hpp"

namespace Scheduler {
    class IScheduler {
        public:
            IScheduler() = default;
            virtual ~IScheduler() = default;

            virtual void addTask(Task::Task& task) = 0;
            virtual int removeTask(int id) = 0;
            virtual Task::Task& getNext() = 0;
    };
}
