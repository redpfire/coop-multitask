#pragma once
#include "task.hpp"
#include "../resource/guarded_resource.hpp"
#include <atomic>

namespace Task {
    class HelloTask : public Task {
        public:
            HelloTask(int id)
                : Task{id}
            {
            }

            void run() override;
    };
}
