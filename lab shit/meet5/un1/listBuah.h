#ifndef LISTBUAH_H
#define LISTBUAH_H
#define Nil nullptr
#include <iostream>
using namespace std;

struct buah{
    string nama;
    int jumlah;
    float harga;
};

typedef buah dataBuah;
typedef struct node *address;

struct node{
    dataBuah isidata;
    address next;
};

struct linkedlist{
    address first;
};

bool isEmpty(linkedlist List);
void createList(linkedlist &List);                      
address alokasi(string nama, int jumlah, float harga);
void dealokasi(address &node);                          
void printList(linkedlist List);                        
void insertFirst(linkedlist &List, address nodeBaru);
void insertAfter(linkedlist &List, address nodeBaru, address prev);
void insertLast(linkedlist &List, address nodeBaru);
void delFirst(linkedlist &List);
void delLast(linkedlist &List);
void delAfter(linkedlist &List, address nodeHapus, address nodePrev);
int nbList(linkedlist List);                            
void deleteList(linkedlist &List);

void updateFirst(linkedlist List);
void updateLast(linkedlist List);
void updateAfter(linkedlist List, address prev);

#endif