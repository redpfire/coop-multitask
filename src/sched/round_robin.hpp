#pragma once
#include "i_scheduler.hpp"
#include "../task/task_queue.hpp"

namespace Scheduler {
    class RoundRobin : public IScheduler {
        public:
            explicit RoundRobin();

            void addTask(Task::Task& task) override;
            int removeTask(int id) override;
            Task::Task& getNext() override;

            void printStates();

        private:
            Task::TaskQueue taskQueue_;

            // this is arbitrary and is used to prevent
            // infinite blocking while finding a task to run
            static constexpr int maxTaskFindTries_{99};
    };
}
