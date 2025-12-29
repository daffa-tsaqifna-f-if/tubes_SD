#include "queue.h"
#include <iostream>
using namespace std;

int main() {
    queue Q;
    address nodeA, nodeB, nodeC, nodeD, nodeE = Nil;
    createQueue(Q);
    nodeA = alokasi(1);
    nodeB = alokasi (2);
    nodeC =  alokasi (3);
    nodeD = alokasi (4);
    nodeE =  alokasi(5);
    enqueue(Q,nodeA);


    return 0;
}