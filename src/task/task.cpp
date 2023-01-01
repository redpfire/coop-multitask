#include "task.hpp"

namespace Task {
    Task::Task(int id)
        : state_{TaskState::CREATED},
          id_{id}
    {
    }

    void Task::changeState(const TaskState state) {
        this->state_ = state;
    }

    const TaskState Task::getState() const {
        return this->state_;
    }

    const int Task::getID() const {
        return this->id_;
    }

    void Task::setID(int id) {
        this->id_ = id;
    }
}
