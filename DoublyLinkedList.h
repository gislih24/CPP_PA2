#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
// Just an example:
template <typename T> struct DoublyLinkedList {
    struct Node {
        Node* prev;
        T value;
        Node* next;

        Node();
        Node(T const& _value);
    };

    Node sentinel;
    int listSize;

    DoublyLinkedList();
    DoublyLinkedList(DoublyLinkedList const& other);
    ~DoublyLinkedList();

    int size() const;

    Node* front();
    Node* back();

    Node* insert(Node* cursor, T const& value);
    Node* erase(Node* cursor);

    Node* predecessor(Node* cursor);
    Node* successor(Node* cursor);
};

#endif