#include <iostream>
#include "queue.h"
using namespace std;

int main() {
    Queue Q;

    createQueue(Q);
    printInfo(Q);
    cout << "\n Enqueue 3 Elemen"<<endl;
    enqueue(Q,5);
    printInfo(Q);
    enqueue(Q,2);
    

    return 0;
}