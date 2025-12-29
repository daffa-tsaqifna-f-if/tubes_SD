#include <iostream>
using namespace std;

const int maxB = 12;

struct buku {
    string nama;
    string penulis;
};

struct Node {
    buku data;
    Node* next;
};

struct stack {
    Node* top;
    int count;
};

void create(stack &r) {
    r.top = nullptr;
    r.count = 0;
}

bool full(stack r) {
    return r.count == maxB;
}

bool empty(stack r) {
    return r.top == nullptr;
}

void stackin(stack &rak, string n, string p) {
    if (!full(rak)) {
        Node* baru = new Node;
        baru->data.nama = n;
        baru->data.penulis = p;
        baru->next = rak.top;
        rak.top = baru;
        rak.count++;
    } else {
        cout << "sorry full\n";
    }
}

void check(stack &r, string &n, string &p) {
    if (!empty(r)) {
        Node* hapus = r.top;
        n = hapus->data.nama;
        p = hapus->data.penulis;
        r.top = hapus->next;
        delete hapus;
        r.count--;
    } else {
        cout << "not found\n";
    }
}

void find(stack &rak, string n, string &p) {
    if (empty(rak)) {
        cout << "Rak kosong\n";
        return;
    }

    stack temp;
    create(temp);
    string t1, t2;
    bool found = false;

    while (!found && !empty(rak)) {
        check(rak, t1, t2);
        if (t1 == n) {
            found = true;
        } else {
            stackin(temp, t1, t2);
        }
    }

    if (found) {
        cout << "Buku ditemukan: " << t1 << " oleh " << t2 << endl;
    } else {
        cout << "Buku tidak ditemukan.\n";
    }

    while (!empty(temp)) {
        check(temp, t1, t2);
        stackin(rak, t1, t2);
    }
}

int main() {
    stack rak;
    string N, P;
    int x;
    create(rak);

    while (true) {
        cout << "1. masukan buku?\n";
        cout << "2. mencari buku\n";
        cout << "3. exit\n";
        cin >> x;
        switch (x) {
        case 1:
            cout << "masukan nama buku: ";
            cin >> N;
            cout << "masukan penulis: ";
            cin >> P;
            stackin(rak, N, P);
            break;
        case 2:
            cout << "masukan nama buku: ";
            cin >> N;
            find(rak, N, P);
            break;
        case 3:
            cout << "ok";
            return 0;
        default:
            return 0;
        }
    }
}
