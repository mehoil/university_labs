#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <queue>
#include <vector>
#include <functional>
#include <windows.h>
#include <atomic>

static constexpr int MAX_THREADS_COUNT = 12;

class ThreadPool {
    std::vector<HANDLE> threads;
    std::queue<std::function<void()>> taskQueue;

    HANDLE mutexHandle;
    HANDLE semaphoreHandle;
    std::atomic<bool> stop;

public:
    ThreadPool() : stop(false) {
        auto threadCount = std::thread::hardware_concurrency();
        if (threadCount == 0) {
            threadCount = MAX_THREADS_COUNT;
        }

        mutexHandle = CreateMutex(nullptr, FALSE, nullptr);
        semaphoreHandle = CreateSemaphore(nullptr, 0, MAX_THREADS_COUNT, nullptr);

        for (int i = 0; i < threadCount; ++i) {
            auto threadHandle = createWinThread();
            if (threadHandle == nullptr) {
                throw std::runtime_error("Could not create a win thread");
            }
            threads.push_back(threadHandle);
        }
    }

    ~ThreadPool() {
        {
            stop.store(true);
            ReleaseSemaphore(semaphoreHandle, static_cast<LONG>(threads.size()), nullptr);
        }

        for (const HANDLE& thread : threads) {
            WaitForSingleObject(thread, INFINITE);
            CloseHandle(thread);
        }

        CloseHandle(mutexHandle);
        CloseHandle(semaphoreHandle);
    }

    template<typename Func>
    void addTask(Func task) {
        WaitForSingleObject(mutexHandle, INFINITE);

        if (stop) {
            ReleaseMutex(mutexHandle);
            throw std::runtime_error("Cannot add task => thread pool is stopping.");
        }

        taskQueue.push(std::function<void()>(task));

        ReleaseMutex(mutexHandle);
        ReleaseSemaphore(semaphoreHandle, 1, nullptr);
    }

private:
    static DWORD WINAPI worker(const LPVOID param) {
        auto* pool = static_cast<ThreadPool*>(param);

        while (true) {
            WaitForSingleObject(pool->semaphoreHandle, INFINITE);
            WaitForSingleObject(pool->mutexHandle, INFINITE);

            if (pool->stop && pool->taskQueue.empty()) {
                ReleaseMutex(pool->mutexHandle);
                return 0;
            }

            if (!pool->taskQueue.empty()) {
                std::function<void()> task = std::move(pool->taskQueue.front());
                pool->taskQueue.pop();

                ReleaseMutex(pool->mutexHandle);
                task();
            } else {
                ReleaseMutex(pool->mutexHandle);
            }
        }
    }

    HANDLE createWinThread() {
        return CreateThread(
                nullptr,                // default security attributes
                0,                      // default stack size
                &ThreadPool::worker,    // thread method
                this,                   //  ^ param passed to thread method
                0,                      // default creation flags
                nullptr                 // default thread ID
            );
    }
};

#endif // THREADPOOL_H