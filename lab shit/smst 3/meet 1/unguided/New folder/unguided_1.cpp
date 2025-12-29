#include <iostream>
using namespace std;

int input(int &angka, int &angka2) {
    cout<<"Masukkan angka pertama: ";
    cin>>angka;
    cout<<"Masukkan angka kedua: ";
    cin>>angka2;
    return 0;
}

void output(int angka, int angka2) {
    cout<<"hasil penjumlahan: "<<angka+angka2<<endl;
    cout<<"hasil pengurangan: "<<angka-angka2<<endl;
    cout<<"hasil perkalian: "<<angka*angka2<<endl;
    cout<<"hasil pembagian: "<<angka/angka2<<endl;
}

int main() {
    int x,y;
    input(x,y);
    output(x,y);
    return 0;
}