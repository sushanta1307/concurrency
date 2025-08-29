// Build a simple thread pool with a fixed number of worker threads.

#include<iostream>
#include<thread>
#include<mutex>
#include<atomic>
#include<queue>
#include<condition_variable>

using namespace std;

class ThreadPool {
    mutex mu;
    condition_variable cv;
    atomic<bool> stop;
    vector<thread> workers;
    queue<function<void()>> tasks;

public:
    ThreadPool(int n) : stop(false) {
        for(int i=0;i<n;i++) {
            workers.emplace_back([this] {
                function<void()> task;
                while(1) {
                    {
                        unique_lock<mutex> lock(mu);
                        cv.wait(lock, [this] {
                            return stop || !tasks.empty();
                        });

                        if(stop and tasks.empty()) return;
                        task = tasks.front();
                    }

                    task();
                }
            });
        }
    }

    void enqueue(function<void()> fn) {
        {
            unique_lock<mutex> lock(mu);
            tasks.push(move(fn));
        }
        cv.notify_one();
    }

    ~ThreadPool() {
        stop = true;
        cv.notify_all();
        for(auto &w: workers) {
            if(w.joinable()) {
                w.join();
            }
        }
    }
};

int main() {

}