#include "round_robin.hpp"
#include <iostream>
#include <algorithm>

namespace Scheduler {
    RoundRobin::RoundRobin()
        : taskQueue_{}
    {
    }

    void RoundRobin::addTask(Task::Task& task) {
        taskQueue_.addTask(task);
    }

    int RoundRobin::removeTask(int id) {
        return taskQueue_.removeTask(id);
    }

    Task::Task& RoundRobin::getNext() {
        Task::Task& prevTask = taskQueue_.peekPrev();

        // when the task itself didn't change it's state
        if (prevTask.getState() == Task::TaskState::RUNNING) {
            prevTask.changeState(Task::TaskState::READY);
        }

        for (int i = 0; i < maxTaskFindTries_; i++) {
            Task::Task& nextTask = taskQueue_.popNext();

            switch (nextTask.getState()) {
                case Task::TaskState::TERMINATED:
                    std::cout << "Removing task " << nextTask.getID() << std::endl;
                    taskQueue_.removeTask(nextTask.getID());
                    continue;
                case Task::TaskState::WAITING:
                    std::cout << "Skipping task " << nextTask.getID() << std::endl;
                    continue;

                default: // CREATED, READY, RUNNING
                    break;
            }

            nextTask.changeState(Task::TaskState::RUNNING);
            return nextTask;
        }
        
        // if none applicable tasks found force head to run
        // to prevent blocking
        taskQueue_.peekHead().changeState(Task::TaskState::RUNNING);
        return taskQueue_.popHead();
    }

    void RoundRobin::printStates() {
        std::cout << "TID\t\tSTATE" << std::endl;

        const auto states = taskQueue_.getStates();
        std::for_each(states.begin(), states.end(), Task::TaskStateFunctor());
    }
}
