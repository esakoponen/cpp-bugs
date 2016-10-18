#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>

typedef std::chrono::high_resolution_clock rt_clock;
typedef std::chrono::time_point<rt_clock> rt_time_point;

std::timed_mutex mutex;

void f()
{
    mutex.try_lock_for(std::chrono::seconds(3));
}

int main()
{
    mutex.lock();
    std::cout << "mutex locked" << std::endl;

    rt_time_point t1 = rt_clock::now();
    std::thread(f).join();
    rt_time_point t2 = rt_clock::now();
    std::cout << "delay: "
              << std::chrono::duration_cast<std::chrono::seconds>(t2-t1).count()
              << std::endl;
    return 0;
}
