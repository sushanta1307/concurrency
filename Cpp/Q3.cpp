// Multiple threads increment a shared counter → ensure result is correct with std::mutex.

#include<iostream>
#include<thread>
#include<mutex>

using namespace std;
int counter = 0;

mutex mu;

void increment() {
    for(int i=0;i<100;i++) {
        // mu.lock();
        // counter++;
        // mu.unlock();

        lock_guard<mutex> lk(mu);
        counter++;
    }
}

int main() {
    thread t1(increment);
    thread t2(increment);

    if(t1.joinable()) t1.join();
    if(t2.joinable()) t2.join();

    cout<<counter<<endl;
    return 0;
}