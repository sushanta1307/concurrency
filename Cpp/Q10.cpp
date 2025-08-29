// Implement a parallel sum of a large array using futures/promises.

#include<iostream>
#include<vector>
#include <numeric>
#include <future>

using namespace std;

int partialSum(vector<int> &arr, int start, int end) {
    return accumulate(arr.begin()+start, arr.begin() + end, 0);
}

int main() {
    vector<int> arr = {1,2,3,4,5,6,7,8,9};

    const int NUM_THREADS = 3;
    vector<future<int>> futures;

    for(int i=0;i<3;i++) {
        futures.push_back(async(launch::async, partialSum, ref(arr), 3*i, 3*(i+1)));
    }

    int total = 0;

    for(auto &f: futures) {
        total += f.get();
    }

    cout<<total<<endl;

    return 0;
}