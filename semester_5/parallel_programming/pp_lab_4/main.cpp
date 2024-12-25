#include <iostream>
#include <thread>
#include <random>

#include "ThreadPool.h"
#include "ThreadPoolUtil.h"

static constexpr int RANDOM_MIN = 1;
static constexpr int RANDOM_MAX = 20;

static int getRandomNumber() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution dist(RANDOM_MIN, RANDOM_MAX);
    return dist(gen);
}

void sampleTask(const int id) {
    const auto threadId = std::to_string(ThreadPoolUtil::getCurrentThreadId());
    const auto msgRunning = "Task " + std::to_string(id) + " is running on thread #" + threadId + "...\n";
    std::cout << msgRunning;
    std::this_thread::sleep_for(std::chrono::seconds(getRandomNumber()));
    const auto msgCompleted = "Task " + std::to_string(id) + " completed." + '\n';
    std::cout << msgCompleted;
}
int main() {
    ThreadPool pool;

    for (int i = 0; i < 10; ++i) {
        pool.addTask([i] { sampleTask(i); } );
    }

    std::this_thread::sleep_for(std::chrono::seconds(RANDOM_MAX));
    return 0;
}
