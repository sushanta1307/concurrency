// Thread Safe LRU cache

#include<iostream>
#include<unordered_map>
#include<list>
#include <thread>

using namespace std;

class LRUCache {
    int capacity;
    list<int> usages;
    unordered_map<int, pair<int, list<int>::iterator>> cache;

public:
    LRUCache(int cap) : capacity(cap) {}

    int get(int key) {
        auto it = cache.find(key);
        if(it == cache.end()) return -1;

        int val = it->second.first;

        // move the element to the first
        usages.erase(it->second.second);
        usages.push_front(key);

        cache[key] = {val, usages.begin()};

        return val;
    }

    void put(int key, int val) {
        auto it = cache.find(key);
        if(it != cache.end()) {
            usages.erase(it->second.second);
        } else if(cache.size() == capacity) {
            int k = usages.back();
            cache.erase(k);
            usages.pop_back();
        }

        usages.push_front(key);
        cache[key] = {val, usages.begin()};
    }

};

void reader(LRUCache &lru, int id) {
    for(int i=0;i<10;i++) {
        int key = id*10 + i;
        int val = lru.get(key);
        cout<< key <<" " << val << endl;
        this_thread::sleep_for(1000ms);
    }
}

void writer(LRUCache &lru, int id) {
    for(int i=0;i<10;i++) {
        lru.put(id*10+i, i);
        this_thread::sleep_for(2000ms);
    }
}

int main() {
    LRUCache cache(4);
    thread t1(writer, ref(cache), 2);
    thread t2(reader, ref(cache), 2);

    t1.join();
    t2.join();
    return 0;
}