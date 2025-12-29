#include <iostream>
using namespace std;


struct Node {
    float data;
    Node* next;
};

void  addnew(Node*& head, float x){
    Node* nnode = new Node;
    nnode->data = x;
    nnode->next =nullptr;
    if (head==nullptr){
        head = nnode;
    } else {
        Node* temp = head;
        while (temp->next !=nullptr){
            temp=temp->next;
        }
        temp->next = nnode;
    }
}


void print(Node* head){
    Node* temp =head;
    while (true){
        cout << temp->data;
        if (temp->next != nullptr){
            cout << " - ";
        }
        temp = temp->next;
    }
}



int main() {
    Node* head = nullptr;
    float y;
    cout << "masukan data (masukan -1 jika selesai)\nstart: ";
    while (true){
        cin >> y;
        if (y==-1){
            break;
        }
        addnew (head,y);
        cout << "next: ";
    }
    print(head);
    cout << endl;

    return 0;
}