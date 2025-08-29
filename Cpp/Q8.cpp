// Read-Heavy Cache with std::shared_mutex

#include<iostream>
#include<thread>
#include<unordered_map>
#include<shared_mutex>

using namespace std;

class ThreadSafeCache {
    shared_mutex mu;
    unordered_map<int, int> cache;

public:
    void put(int key, int val) {
        unique_lock<shared_mutex> lock(mu);
        cache[key] = val;
    }

    int get(int key) {
        shared_lock<shared_mutex> lock(mu);
        auto it = cache.find(key);

        return (it != cache.end()) ? it->second : -1;
    }

};

int main() {

}