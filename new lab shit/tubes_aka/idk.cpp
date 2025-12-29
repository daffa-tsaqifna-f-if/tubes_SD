#include <iostream>
#include <chrono>
#include <iomanip>
#include <vector>

using namespace std;

// Iterative factorial
long long factIter(int n) {
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Recursive factorial
long long factRec(int n) {
    if (n == 0 || n == 1)
        return 1;
    return n * factRec(n - 1);
}

int main() {
    vector<int> inputs = {10, 100, 500, 1000, 2000, 3500, 4500};

    cout << "BENCHMARK ALGORITMA FAKTORIAL: ITERATIF VS REKURSIF\n";
    cout << "---------------------------------------------------\n\n";

    cout << left
         << setw(10) << "N"
         << setw(18) << "Iteratif (detik)"
         << setw(20) << "Rekursif (detik)"
         << setw(12) << "Ratio (R/I)"
         << endl;

    cout << string(60, '-') << endl;

    for (int n : inputs) {
        // Iterative timing
        auto start = chrono::high_resolution_clock::now();
        factIter(n);
        auto end = chrono::high_resolution_clock::now();
        double iterTime = chrono::duration<double>(end - start).count();

        // Recursive timing
        start = chrono::high_resolution_clock::now();
        factRec(n);
        end = chrono::high_resolution_clock::now();
        double recTime = chrono::duration<double>(end - start).count();

        double ratio = recTime / iterTime;

        cout << setw(10) << n
             << setw(18) << fixed << setprecision(6) << iterTime
             << setw(20) << fixed << setprecision(6) << recTime
             << setw(12) << fixed << setprecision(2) << ratio << "x"
             << endl;
    }

    return 0;
}
