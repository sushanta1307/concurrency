// Write a program that launches 5 threads, each printing "Hello from thread X".

#include<iostream>
#include<thread>
#include<vector>

using namespace std;

void hello(int x) {
    // threads don't flush the output at a time when cout run concurrently
    // This is also not reliable
    // Use mutex for best results
    string msg = "Hello from thread " + to_string(x);
    cout<<msg<<endl;
}

int main() {

    vector<thread> threads;

    for(int i=0;i<5;i++) {
        // threads.push_back(thread(hello, ref(i)));
        threads.emplace_back(hello, i);
    }

    for(auto &t: threads) {
        if(t.joinable()) {
            t.join();
        }
    }

    return 0;
}