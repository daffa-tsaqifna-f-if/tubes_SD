#include <iostream>
using namespace std;

struct Node {
    float data;
    Node* next;
};

void  addnew(Node*& head, int x){
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
    while (temp!=nullptr){
        cout << temp->data;
        if (temp->next != nullptr){
            cout << " - ";
        }
        temp = temp->next;
    }
    cout <<endl;
}

bool check(Node* head,int x){
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == x){
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void deletel(Node*& head,int x){
    if (head == nullptr) {
        cout << "List kosong"<<endl;
        return;
    }

    if (!check(head, x)) {
        cout << "Tidak ada elemen bernilai " << x << " dalam list"<<endl;
        return;
    }

    if (head->data == x) {
        Node* del = head;
        head = head->next;
        delete del;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr && temp->next->data != x) {
        temp = temp->next;
    }
    Node* target = temp->next;
    if (target->next == nullptr) {
            temp->next = nullptr;
            delete target;
            return;
        }
    Node* del = target->next;
    target->next = del->next;
    delete del;
}

int main() {
    Node* head=nullptr;
    int x;
    addnew(head,15);
    addnew(head,30);
    addnew(head,40);
    addnew(head,50);
    cout << "linked list awal"<<endl;
    print(head);
    cout << "nilai yang di cari: ";
    cin >> x;
    deletel(head,x);
    cout << "linked list akhir"<<endl;
    print(head);
    return 0;
}