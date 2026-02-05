#include "DoublyLinkedList.h"
#include <iostream>

int main() {
    int q;
    std::cin >> q;

    DoublyLinkedList<int> lists[1000];
    Node<int>* cursors[1000];

    for (int i = 0; i <= 1000; ++i) {
        cursors[i] = lists[i].back();
    }

    for (int i = 0; i < q; ++i) {
        int id;
        int operation;
        std::cin >> id >> operation;

        if (operation == 'a') {
            /* construct a copy of the array, takes integer argument for the
             * instance ID of the doubly linked list to copy. */
            int sourceListId;
            std::cin >> sourceListId;
            lists[id] = lists[sourceListId]; // Deep copy via operator=
            cursors[id] = lists[id].back();  // Reset cursor to sentinel
        } else if (operation == 'f') {
            // front, no additional arguments.
            cursors[id] = lists[id].front();
        } else if (operation == 'b') {
            // back, no additional arguments.
            cursors[id] = lists[id].back(); // sentinel
        } else if (operation == 'i') {
            // insert, takes one integer argument, the element to insert.
            int elementToInsert;
            std::cin >> elementToInsert;
            cursors[id] = lists[id].insert(cursors[id], elementToInsert);
        } else if (operation == 'e') {
            // erase, no additional arguments.
            cursors[id] = lists[id].erase(cursors[id]);
        } else if (operation == '>') {
            // successor, no additional arguments.
            cursors[id] = lists[id].successor(cursors[id]);
        } else if (operation == '<') {
            // predecessor, no additional arguments.
            cursors[id] = lists[id].predecessor(cursors[id]);
        } else if (operation == 'g') {
            // element access, read.
            std::cout << cursors[id]->data << "\n";
        } else if (operation == 's') {
            /* element access, takes integer argument, the element to write into
             * the cursor node. */
            int elementToWrite;
            std::cin >> elementToWrite;
            cursors[id]->data = elementToWrite;
        } else if (operation == 'z') {
            std::cout << lists[id].size() << "\n";
        }
    }

    return 0;
}