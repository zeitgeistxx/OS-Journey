#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <random>
#include <chrono>

struct NetworkRequest
{
    int id;
    int retry_count;

    NetworkRequest(int id, int retry_count = 0) : id(id), retry_count(retry_count) {}
};

template <typename T>
class ThreadSafeWorkQueue
{
    std::queue<T> queue;
    std::mutex mtx;
    std::condition_variable cv;
    bool done;

public:
    explicit ThreadSafeWorkQueue() : done(false) {}

    void push(const T &item)
    {
        std::lock_guard<std::mutex> lock(mtx);
        queue.push(item);
        cv.notify_one();
    }

    bool try_pop(T &item)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]()
                { return !queue.empty() || done; });

        if (queue.empty() && done)
            return false;

        if (!queue.empty())
        {
            item = queue.front();
            queue.pop();
            return true;
        }
        return false;
    }

    void set_done()
    {
        std::lock_guard<std::mutex> lock(mtx);
        done = true;
        cv.notify_all();
    }

    bool is_done() const
    {
        return done && queue.empty();
    }
};

bool process_network_request(const NetworkRequest &request)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1); // 50% chance of success

    bool success = dist(gen);
    // bool success = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    if (success)
    {
        std::cout << "Request " << request.id << " processed successfully!\n";
        return true;
    }
    else
    {
        std::cout << "Request " << request.id << " failed. Retrying...\n";
        return false;
    }
}

void worker(ThreadSafeWorkQueue<NetworkRequest> &tsQueue, int id)
{
    NetworkRequest request(0);
    while (!tsQueue.is_done())
    {
        if (tsQueue.try_pop(request))
        {
            if (!process_network_request(request))
            {
                request.retry_count++;
                tsQueue.push(request);
            }
        }
        else if (tsQueue.is_done())
        {
            break;
        }
    }
}

int main()
{
    ThreadSafeWorkQueue<NetworkRequest> tsQueue;

    const int num_requests = 10;
    for (int i = 1; i <= num_requests; ++i)
    {
        tsQueue.push(NetworkRequest(i));
    }

    std::vector<std::thread> workers;
    const int num_workers = std::thread::hardware_concurrency() / 2;
    for (int i = 0; i < num_workers; ++i)
    {
        workers.emplace_back(worker, std::ref(tsQueue), i);
    }
    tsQueue.set_done();

    for (auto &worker : workers)
    {
        worker.join();
    }
}