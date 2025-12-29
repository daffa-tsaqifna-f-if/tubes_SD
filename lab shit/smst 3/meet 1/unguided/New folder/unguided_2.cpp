#include <iostream>
using namespace std;

int input(int &angka){
    while(true){
        cout << "Masukkan angka: ";
        cin >> angka;
        if (angka >100){
            cout <<"input lebih dari 100 coba lagi"<<endl;
            continue;
        }else{
            break;
        }
    }
    return 0;
}

void text(int angka){
    int satuan, puluhan;
    string less[] = {"nol", "satu", "dua", "tiga", "empat", "lima", "enam", "tujuh", "delapan", "sembilan", "sepuluh"};
    string specific[] = {"belas","puluh"};
    string text;
    //check
    if (angka <=10){
        cout << angka<<" : "<<less [angka];
        }else if(angka == 100){
            cout<<"seratus";
            }else{
                satuan = angka % 10;
                puluhan = (angka / 10) % 10;
                if (puluhan == 1){
                    switch (satuan){
                    case 1:
                        cout<<angka<<" : "<<"sebelas";
                    default:
                        text = less[satuan]+" "+specific[0];
                        cout<<angka<<" : "<<text;
                    }
                }else {
                    text = less[puluhan]+" "+specific[1]+" "+less[satuan];
                    cout<<angka<<" : "<<text;
                    }
     };
}

int main() {
    int x;
    input(x);
    text(x);
    return 0;
}