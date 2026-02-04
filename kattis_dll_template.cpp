#include "DoublyLinkedList.h"
#include <cassert>
#include <iostream>

using std::cin;
using std::cout;
using std::ws;

your_list_type lists[1000];
your_node_type* cursors[1000];

int main() {
    int q;
    cin >> q;

    for (int i = 0; i < 1000; i++) {
        cursors[i] = lists[i].sentinel_end_node();
    }

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
            lists[instance] = lists[other];
            cursors[instance] = lists[instance].sentinel_end_node();
        } else if (op == 'f') {
            cursors[instance] = lists[instance].begin_node();
        } else if (op == 'b') {
            cursors[instance] = lists[instance].sentinel_end_node();
        } else if (op == 'i') {
            int value;
            cin >> value;
            cursors[instance] =
                lists[instance].insert(cursors[instance], value);
        } else if (op == 'e') {
            cursors[instance] = lists[instance].erase(cursors[instance]);
        } else if (op == '>') {
            cursors[instance] = lists[instance].successor(cursors[instance]);
        } else if (op == '<') {
            cursors[instance] = lists[instance].predecessor(cursors[instance]);
        } else if (op == 'g') {
            cout << cursors[instance]->data << '\n';
        } else if (op == 's') {
            int value;
            cin >> value;
            cursors[instance]->data = value;
        } else if (op == 'z') {
            cout << lists[instance].size() << '\n';
        } else {
            assert(false);
        }
    }
}