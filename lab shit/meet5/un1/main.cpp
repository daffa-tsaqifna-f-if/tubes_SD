#include "listBuah.h"
#include <iostream>
using namespace std;

int main() {
    linkedlist List;
    address nodeA,nodeB,nodeC,nodeD,nodeE = Nil;
    createList(List);
    dataBuah dtbuah;
    nodeA = alokasi ("jeruk",100,3000);
    nodeB = alokasi ("apel",75,4000);
    nodeC = alokasi ("pir",87,5000);
    nodeD = alokasi ("semangka",43,11500);
    nodeE = alokasi("durian",15,31450);
    
    insertFirst (List,nodeA);
    insertLast (List,nodeB);
    insertAfter(List,nodeC,nodeA);
    insertAfter(List,nodeD,nodeC);

    cout<< "-- ISI LIST SETELAH DILAKUKAN UPDATE ---"<<endl;
    printList (List);
    cout << "jumbalh node: "<<nbList(List)<< endl;
    cout<<endl;
    
    return 0;
}