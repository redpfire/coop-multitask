#pragma once
#include <iostream>

namespace Task {

enum class TaskState {
    CREATED = 0,
    TERMINATED,
    READY,
    WAITING,
    RUNNING
};

inline const char* ToString(TaskState v)
{
    switch (v)
    {
        case TaskState::CREATED:        return "CREATED";
        case TaskState::TERMINATED:     return "TERMINATED";
        case TaskState::READY:          return "READY";
        case TaskState::WAITING:        return "WAITING";
        case TaskState::RUNNING:        return "RUNNING";
        default:                        return "[Unknown TaskState]";
    }
}

struct TaskStateFunctor {
    void operator()(std::pair<int, TaskState> item) {
        std::cout << item.first << "\t\t" << ToString(item.second) << std::endl;
    }
};

class Task {
    public:
        explicit Task(int id);
        const int getID() const;
        void setID(int id);
        const TaskState getState() const;
        void changeState(const TaskState state);

        virtual void run() = 0;

    private:
        int id_;
        TaskState state_;
};

}
