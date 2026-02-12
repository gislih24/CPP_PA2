// kattis_heap2_template.cpp
// Kattis main template for: heap2

#include "Heap2.h"
#include <cassert>
#include <iostream>

using std::cin;
using std::cout;
using std::ws;

static const int MAX_INSTANCES = 1000;

Heap2<int> heaps[MAX_INSTANCES];

int main() {
    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        int instance;
        cin >> instance;
        instance--;

        cin >> ws;
        char op;
        cin >> op;

        if (op == 'a') {
            int other;
            cin >> other;
            other--;
            heaps[instance] = heaps[other];
        } else if (op == '+') {
            int value;
            cin >> value;
            heaps[instance].push(value);
        } else if (op == '-') {
            heaps[instance].pop();
        } else if (op == 'p') {
            cout << heaps[instance].peek() << '\n';
        } else if (op == 's') {
            cout << heaps[instance].size() << '\n';
        } else {
            assert(false);
        }
    }

    return 0;
}
