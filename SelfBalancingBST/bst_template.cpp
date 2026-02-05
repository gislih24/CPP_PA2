#include <cassert>
#include <iostream>
// #include "your_tree.h"

using std::cin;
using std::cout;
using std::ws;

your_tree_type<int, int> trees[1000];
your_node_type<int, int>* cursors[1000];

int main() {
    int q;
    cin >> q;

    for (int i = 0; i < 1000; i++) {
        cursors[i] = NULL; // or other sentinel value
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
            trees[instance] = trees[other];
            cursors[instance] = NULL; // or other sentinel value
        } else if (op == '?') {
            int key;
            cin >> key;
            cursors[instance] = trees[instance].find(key);
        } else if (op == 'l') {
            int key;
            cin >> key;
            cursors[instance] = trees[instance].lower_bound(key);
        } else if (op == 'u') {
            int key;
            cin >> key;
            cursors[instance] = trees[instance].upper_bound(key);
        } else if (op == 'i') {
            int key, value;
            cin >> key >> value;
            cursors[instance] = trees[instance].insert(key, value);
        } else if (op == 'e') {
            trees[instance].erase(cursors[instance]);
            cursors[instance] = NULL; // or other sentinel value
        } else if (op == 'f') {
            cursors[instance] = trees[instance].front();
        } else if (op == 'b') {
            cursors[instance] = trees[instance].back();
        } else if (op == '>') {
            cursors[instance] = trees[instance].successor(cursors[instance]);
        } else if (op == '<') {
            cursors[instance] = trees[instance].predecessor(cursors[instance]);
        } else if (op == 'r') {
            // or other sentinel value
            if (cursors[instance] == NULL) {
                cout << "-\n";
            } else {
                cout << trees[instance].rank(cursors[instance]) << '\n';
            }
        } else if (op == 'k') {
            int k;
            cin >> k;
            cursors[instance] = trees[instance].kth(k);
        } else if (op == 'g') {
            // or other sentinel value
            if (cursors[instance] == NULL) {
                cout << "-\n";
            } else {
                cout << cursors[instance]->value << '\n';
            }
        } else if (op == 's') {
            int value;
            cin >> value;
            // or other sentinel value
            if (cursors[instance] != NULL) {
                cursors[instance]->value = value;
            }
        } else if (op == 'z') {
            cout << trees[instance].size() << '\n';
        } else {
            assert(false);
        }
    }
}