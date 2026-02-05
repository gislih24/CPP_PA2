#include <cassert>
#include <iostream>

using std::cout;
using std::cin;
using std::ws;

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
        }
        else if (op == '+') {
            int value;
            cin >> value;
            // push back
        }
        else if (op == '-') {
            // pop back
        }
        else if (op == 'i') {
            int index, value;
            cin >> index >> value;
            // insert
        }
        else if (op == 'e') {
            int index;
            cin >> index;
            // erase
        }
        else if (op == 'g') {
            int index;
            cin >> index;
            // get
        }
        else if (op == 's') {
            int index, value;
            cin >> index >> value;
            // set
        }
        else if (op == 'r') {
            int sz;
            cin >> sz;
            // resize
        }
        else if (op == 'p') {
            // print
        }
        else {
            assert(false);
        }
    }
}