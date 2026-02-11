#include <cassert>
#include <iostream>
// Include your dequeue implementation
#include "Dequeue.h"

using std::cin;
using std::cout;
using std::ws;

// Bind the placeholder type used by the template to your implementation
typedef Dequeue<int> your_array_type;

your_array_type vecs[1000];

int main() {
    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        int instance;
        cin >> instance;
        instance--; // change to 0-based index
        // consume whitespace before reading character, otherwise we get a space
        cin >> ws;
        char op;
        cin >> op; // read operation character

        if (op == 'a') {
            int other;
            cin >> other;
            other--; // change to 0-based index
            // assignment
            vecs[instance] = vecs[other];
        } else if (op == '+f') {
            int value;
            cin >> value;
            // push front
            vecs[instance].push_front(value)
        } else if (op == '+b') {
            int value;
            cin >> value;
            // push back
            vecs[instance].push_back(value);
        } else if (op == '-f') {
            // pop front
            vecs[instance].pop_front();
        } else if (op == '-b') {
            // pop back
            vecs[instance].pop_back();
        } else if (op == 'f') {
            int index;
            cin >> index;
            // get
            vecs[instance]front();
        } else if (op == 'b') {
            int index;
            cin >> index;
            // get
            vecs[instance]back();
        } else if (op == 's') {
            vecs[instance].size(;)
        } else {
            assert(false);
        }
    }
}