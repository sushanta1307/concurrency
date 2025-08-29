// Implement a bounded buffer (producer-consumer problem).

#include<iostream>
#include<thread>
#include<vector>
#include<queue>
#include<mutex>
#include<condition_variable>

using namespace std;

mutex mu;
condition_variable cv_producer, cv_consumer;

queue<int> buffer;
const int MAX_BUFFER_SIZE = 5;

void producer() {
    for(int i=1;i<10;i++) {
        unique_lock<mutex> lk(mu);
        cv_producer.wait(lk, [] {
            return buffer.size() < MAX_BUFFER_SIZE;
        });

        buffer.push(i);
        cout<<"Produced "<<i<<endl;
        lk.unlock();
        cv_producer.notify_all(); // use notify_one for multiple consumers
        this_thread::sleep_for(500ms);
    }
}

void consumer() {
    for(int i=1;i<10;i++) {
        unique_lock<mutex> lk(mu);
        cv_consumer.wait(lk, [] {
            return !buffer.empty();
        });

        int val = buffer.front();
        buffer.pop();

        cout<<"Consumer "<<i<<endl;
        lk.unlock();
        cv_consumer.notify_all(); // use notify_one for multiple Producers
        this_thread::sleep_for(1000ms);
    }
}

int main() {

    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();

    cout << "All items produced and consumed!\n";
    return 0;
}