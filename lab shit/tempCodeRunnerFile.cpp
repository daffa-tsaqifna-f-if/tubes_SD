#include <iostream>
using namespace std;

const int maxB = 12;


struct buku {
    string nama;
    string penulis;
};

struct stack{
    buku data[maxB];
    int top;
};

void create(stack &r){
    r.top = -1;
}

bool full(stack r){
    return  r.top == maxB - 1;
}

bool empty(stack r){
    return r.top == -1;
}

void stackin(stack &rak, string n, string p){
    if (!full(rak)){
        rak.top++;
        rak.data[rak.top].nama = n;
        rak.data[rak.top].penulis =p;
    }else{
        cout << "sorry full\n";
    }
}

void check(stack &r,string &n, string &p){
    if (!empty(r)){
        n=r.data[r.top].nama;
        p=r.data[r.top].penulis;
        r.top--;
    } else{
        cout << "not found";
    }
}


void find(stack &rak, string n, string p){
    stack temp;
    create (temp);
    string t1,t2;
    bool found = false;

    while (!found && !empty(rak)){
        check (rak, t1,t2);
        if (t1==n){
            p = t2;
            found =true;
        }else{
            stackin(temp,t1,t2);
        }
    }

    if (found) {
        cout << "Buku ditemukan: " << t1 << " oleh " << t2 << endl;
    } else {
        cout << "Buku tidak ditemukan.\n";
    }

    while(!empty(temp)){
        check (temp,t1,t2);
        stackin (rak,t1,t2);
    }
}




int main() {
    stack rak;
    string N,P;
    int x;
    create(rak);
    while(true){
        cout << "1. masukan buku?\n2. mencari buku\n3. exit";
        cin >> x;
        switch (x){
        case 1:
            cout << "masukan nama buku: ";
            cin >>N;
            cout << "masukan penulis";
            cin >>P;
            stackin (rak,N,P);
        case 2:
            cout << "masukan nama buku: ";
            cin >>N;
            cout << "masukan penulis";
            cin >>P;
            find(rak,N,P);
        case 3:
            cout << "ok";
            break;
        default:
            break;
        }
    }
    return 0;
}