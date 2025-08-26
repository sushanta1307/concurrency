// Implement a thread-safe logging class where multiple threads log messages to a single file.

#include<iostream>
#include<thread>
#include<fstream>
#include<mutex>

using namespace std;

class Logger {
public:
    ofstream file;
    mutex mu;

    Logger(string fileName) {
        file.open(fileName, ios::out);
    }

    void log(string msg) {
        lock_guard<mutex> lock(mu);
        file<<msg<<endl;
    }

};

void worker(Logger &logger, int id) {
    for(int i=0;i<5;i++) {
        logger.log("Thread " + to_string(id) + " msg " + to_string(i));
    }
}

int main() {
    Logger logger("log.txt");
    vector<thread> threads;

    for(int i=0;i<3;i++) {
        threads.emplace_back(worker, ref(logger), i);
    }

    for(auto &t: threads) {
        if(t.joinable()) {
            t.join();
        }
    }

    return 0;
}