#pragma once

#include <queue>
#include <condition_variable>
#include <mutex>

template<typename T>
class BlockingQueue {
private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable cv;

public:
    void push(const T &item) { {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(item);
    }
        cv.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [this](){ return !queue.empty(); });
        T item = std::move(queue.front());
        queue.pop();
        return item;
    }

};
