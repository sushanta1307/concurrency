// Launch N threads, each computing sum of a portion of an array, then combine results in main.

#include<iostream>
#include<thread>

using namespace std;

void partialSum(const vector<int> &arr, int start, int end, int &res) {
    for(int i=start;i<end;i++) {
        res += arr[i];
    }
}

int main() {

    vector<int> arr = {1,2,3,4,5,6,7,8,9};
    vector<thread> threads(3);
    vector<int> results(3, 0);

    for(int i=0;i<3;i++) {
        threads[i] = thread(partialSum, cref(arr), 3*i, 3*(i+1), ref(results[i]));
    }

    for(auto &t: threads) {
        if(t.joinable()) {
            t.join();
        }
    }
    
    int ans = 0;
    for(auto res: results) {
        ans += res;
    }

    cout<<ans<<endl;

    return 0;
}