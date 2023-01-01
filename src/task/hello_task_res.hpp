#pragma once
#include "task.hpp"
#include "../resource/guarded_resource.hpp"
#include <atomic>

namespace Task {
    class HelloTaskWithResource : public Task {
        public:
            HelloTaskWithResource(int id, Resource::GuardedResource<int>& resource)
                : Task{id}
                , resource_{resource}
            {
            }

            void run() override;

        private:
            Resource::GuardedResource<int>& resource_;
    };
}
