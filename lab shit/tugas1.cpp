#include <iostream>
using namespace std;

struct Node {
    float data;
    Node* next;
};

void nlink(Node*& head){
    head = nullptr;
}


void insertAscending(Node*& head, float x){
    Node* elm = new Node;
    elm->data=x;
    Node* prev =nullptr;
    Node* now =head;
    while(now != nullptr && now->data < x){
        prev = now;
        now = now->next;
    }
    if (prev == nullptr) {
        elm->next = head;
        head = elm;
    } else {
        elm->next = now;
        prev->next = elm;
    }
}

void print(Node* head){
    Node* temp =head;
    while (temp!=nullptr){
        cout << temp->data;
        if (temp->next != nullptr){
            cout << " - ";
        }
        temp = temp->next;
    }
    cout <<endl;
}


int main() {
    Node* head=nullptr;
    nlink(head);
    insertAscending(head, 10.5);
    insertAscending(head, 12.0);
    insertAscending(head, 20.9);
    insertAscending(head, 25.1);
    cout << "original list"<< endl;
    print(head);
    insertAscending(head, 15.0);
    cout << "setelah insert 15.0"<<endl;
    print(head);
    return 0;
}