#include<iostream>
#include<thread>
#include<atomic>
#include<vector>

using namespace std;

atomic<int> counter(0);

void increment() {
    for(int i=0;i<100000;i++) {
        counter++;
    }
}

int main() {

    vector<thread> threads;

    for(int i=0;i<3;i++) {
        threads.emplace_back(increment);
    }

    for(auto &t: threads) {
        t.join();
    }

    cout<<counter<<endl;

    return 0;
}