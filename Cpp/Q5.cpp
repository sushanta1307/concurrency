// Simulate a bank account with deposit/withdraw methods safely accessed by multiple threads.
#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

class Account {
    int balance;
    mutex mu;
public:
    Account(int b) : balance(b) {}

    void deposit(int b) {
        lock_guard<mutex> lock(mu);
        balance += b;
    }

    void withdraw(int b) {
        lock_guard<mutex> lock(mu);
        if(balance >= b) balance -= b;
    }

    int getBalance() {
        lock_guard<mutex> lock(mu);
        return balance;
    }

};

void worker(Account &acc) {
    for(int i=0;i<100;i++) {
        acc.deposit(10);
        acc.withdraw(10);
    }
}

int main() {

    Account acc(1000);

    thread t1(worker, ref(acc));
    thread t2(worker, ref(acc));


    t1.join();
    t2.join();

    cout << acc.getBalance() << endl;
    return 0;
}