#include "task/hello_task.hpp"
#include "task/hello_task_res.hpp"
#include "resource/guarded_resource.hpp"
#include "sched/round_robin.hpp"

int main(int argc, char **argv) {
    srand(time(0));
    Scheduler::RoundRobin scheduler;

    Resource::GuardedResource<int> res{2137};

    Task::HelloTaskWithResource task0{0, res};
    Task::HelloTaskWithResource task1{1, res};
    Task::HelloTask task2{2};

    scheduler.addTask(task0);
    scheduler.addTask(task1);
    scheduler.addTask(task2);

    for (int i = 0; i < 20; i++) {
        scheduler.getNext().run();
    }

    scheduler.printStates();

    return 0;
}
