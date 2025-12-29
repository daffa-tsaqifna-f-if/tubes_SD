#include "Input.h"

#include <iostream>
#include <limits>

using namespace std;

namespace input {

string line(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

int integer(const string& prompt) {
    while (true) {
        cout << prompt;
        int v;
        if (cin >> v) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return v;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid. Coba lagi.\n";
    }
}

double number(const string& prompt) {
    while (true) {
        cout << prompt;
        double v;
        if (cin >> v) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return v;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid. Coba lagi.\n";
    }
}

} // namespace input
