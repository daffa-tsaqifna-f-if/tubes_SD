#include <iostream>
using namespace std;

struct Node {
    float data;
    Node* next;
};

// a. Deklarasi list
struct List {
    Node* head;
};

// b. Membuat list kosong
void createList(List &L) {
    L.head = nullptr;
}

// c. Membuat elemen baru
Node* createElement(float X) {
    Node* newNode = new Node;
    newNode->data = X;
    newNode->next = nullptr;
    return newNode;
}

// d. Insert Ascending
void insertAscending(List &L, float X) {
    Node* newNode = createElement(X);

    // Jika list kosong atau X lebih kecil dari head
    if (L.head == nullptr || X < L.head->data) {
        newNode->next = L.head;
        L.head = newNode;
        return;
    }

    Node* prev = nullptr;
    Node* curr = L.head;
    while (curr != nullptr && curr->data < X) {
        prev = curr;
        curr = curr->next;
    }

    newNode->next = curr;
    prev->next = newNode;
}

// Utility: print list
void printList(List L) {
    Node* p = L.head;
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}



int main() {
    List L;
    createList(L);

    insertAscending(L, 10.5);
    insertAscending(L, 12.0);
    insertAscending(L, 20.9);
    insertAscending(L, 25.1);
    insertAscending(L, 15.0); // test insert middle
    printList(L);

    return 0;
}
