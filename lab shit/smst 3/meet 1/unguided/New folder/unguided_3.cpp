#include <iostream>
using namespace std;

int input(int &angka){
    cout << "Masukkan angka: ";
    cin >> angka;
    return 0;
}

int output(int &angka){
    for (int i = angka; i >= 1; i--) {
        for (int s = 0; s < (angka - i) * 2; s++) {
            cout << " ";
        }

        for (int j = i; j >= 1; j--) {
            cout << j << " ";
        }

        cout << "* ";

        for (int j = 1; j <= i; j++) {
            cout << j;
            if (j != i) cout << " ";
        }

        cout << endl;
    }

    for (int s = 0; s < angka * 2; s++) {
        cout << " ";
    }
    cout << "*" << endl;

    return 0;
}

int main() {
    int x;
    input(x);
    output(x);      
    return 0;
}
