#include <iostream>
using namespace std;

const int MAX = 5;

struct Queue {
    char data[MAX];
    int head;
    int tail;
};

void createQueue(Queue &Q) {
    Q.head = 0;
    Q.tail = 0;
}

bool isEmpty(Queue Q) {
    return (Q.tail == 0);
}

bool isFull(Queue Q) {
    return (Q.tail == MAX);
}

void enqueue(Queue &Q, char x) {
    if (isFull(Q)) {
        cout << "Queue penuh" << endl;
    } else {
        Q.tail++;
        Q.data[Q.tail - 1] = x;
    }
}

void dequeue(Queue &Q, char &Y) {
    if (isEmpty(Q)) {
        cout << "Queue kosong" << endl;
    } else {
        Y = Q.data[0];
        for (int i = 0; i < Q.tail - 1; i++) {
            Q.data[i] = Q.data[i + 1];
        }
        Q.tail--;
    }
}

void printQueue(Queue Q) {
    if (isEmpty(Q)) {
        cout << "Queue kosong" << endl;
    } else {
        for (int i = 0; i < Q.tail; i++) {
            cout << Q.data[i] << " ";
        }
        cout << endl;
    }
}

int main() {
    Queue Q;
    createQueue(Q);

    enqueue(Q, 'A');
    enqueue(Q, 'B');
    enqueue(Q, 'C');
    printQueue(Q);

    char out;
    dequeue(Q, out);
    cout << "Dequeued: " << out << endl;
    printQueue(Q);

    return 0;
}
