#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <utility>

class ThreadPool
{
public:
    ThreadPool(size_t count)
    {
        for (size_t i = 0; i < count; ++i)
        {
            m_threads.emplace_back([this]
            {
                while(true)
                {
                    std::function<void()> task;
                    {
                        std::unique_lock lk(m_mutex);
                        m_cv.wait(lk, [this]{ return m_ready || !m_tasks.empty(); });
                        if (m_ready && m_tasks.empty()) return;
                        task = std::move(m_tasks.front());
                        m_tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    ~ThreadPool()
    {
        {
            std::unique_lock lk(m_mutex);
            m_ready = true;
        }   
        m_cv.notify_all();
        for (auto& t : m_threads)
        {
            t.join();
        }
    }

    template <typename T>
    void add_task(const std::function<T>& task)
    {
        {
            std::unique_lock lk(m_mutex);
            m_tasks.emplace(task);
        }
        m_cv.notify_one();
    }

    void change_ready()
    {
        m_ready = !m_ready;
    }

    bool get_ready() const 
    {
        return m_ready;
    }

private:
    std::vector<std::thread> m_threads;
    std::queue<std::function<void()>> m_tasks;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    bool m_ready = false;
};

int main()
{
    

    return 0;
}