#ifndef NODE
#define NODE

template <typename T> struct Node {
    Node* prev; // The next node in the list (predecessor).
    T data;     // The data stored in the node.
    Node* next; // The next node in the list (successor)

    // Constructor
    Node() : prev(this), data(), next(this) {};

    // Copy Constructor
    Node(T const& _data) : prev(0), data(_data), next(0) {};
};

#endif

#ifndef DOUBLYLINKEDLIST
#define DOUBLYLINKEDLIST

template <typename T> struct DoublyLinkedList {
  private:
    /* The sentinel node.
     * sentinel.next always points to the head(front),
     * sentinel.prev always points to the tail(back).
     */
    Node sentinel;
    // Size of the list.
    int listSize;

    /**
     * @brief Clears the list, freeing all allocated memory.
     */
    void clearList() {
        Node* current = sentinel.next;
        while (current != &sentinel) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        sentinel.next = &sentinel;
        sentinel.prev = &sentinel;
        listSize = 0;
    }

    /**
     * @brief Copies the contents of another list into this list.
     *
     * @param other The list to be copied.
     */
    void copyOtherList(DoublyLinkedList const& other) {
        Node* cur = other.sentinel.next;
        while (cur != &other.sentinel) {
            insert(&sentinel, cur->data); // append at end
            cur = cur->next;
        }
    }

  public:
    /**
     * @brief Constructor that initializes an empty list.
     */
    DoublyLinkedList() : listSize(0) {};

    // Copy Constructor
    DoublyLinkedList(DoublyLinkedList const& other) : listSize(0) {
        copyOtherList(other);
    }

    /**
     * @brief Assignment operator using copy-and-swap idiom.
     *
     * @param other The list to be assigned.
     *
     * @return A reference to this list.
     */
    DoublyLinkedList& operator=(DoublyLinkedList const& other) {
        if (this == &other) {
            return *this;
        }

        clearList();
        copyOtherList(other);
        return *this;
    }

    // Destructor
    ~DoublyLinkedList() {
        clearList();
    }

    // Return the first node(head) of the list, not a sentinel node.
    Node* front() {
        return sentinel.next;
    }

    // Return the last node(tail) of the list, a sentinel node.
    Node* back() {
        return &sentinel;
    }

    // Kattis wants these for some reason...
    // Return the first node(head) of the list, not a sentinel node.
    Node* begin_node() {
        return front();
    }
    // Return the last node(tail) of the list, a sentinel node.
    Node* sentinel_end_node() {
        return back();
    }

    /**
     * @brief Inserts a new node with the given data before the cursor node.
     *
     * @param cursor The node before which the new node will be inserted.
     * @param data The data to be stored in the new node.
     *
     * @return A pointer to the newly inserted node.
     */
    Node* insert(Node* cursor, T const& data) {
        // "Node*&" means "a reference to a pointer to a Node". So we're
        // changing that pointer directly.
        Node* newNode = new Node(data);

        newNode->prev = cursor->prev;
        newNode->next = cursor;
        cursor->prev->next = newNode;
        cursor->prev = newNode;

        listSize++;
        return newNode;
    }

    /**
     * @brief Erases the cursor node from the list, returning the node after the
     *        erased node.
     *
     * @param cursor The node to be erased.
     *
     * @return A pointer to the node that was after the erased node.
     */
    Node* erase(Node* cursor) {
        Node* after = cursor->next;

        // Swap them
        cursor->prev->next = cursor->next;
        cursor->next->prev = cursor->prev;

        delete cursor;
        --listSize;
        return after;
    }

    // Return the node before the cursor node
    Node* predecessor(Node* cursor) {
        return cursor->prev;
    }

    // Return the node after the cursor node
    Node* successor(Node* cursor) {
        return cursor->next;
    }

    // Return the size of the instance
    int size() const {
        return listSize;
    }
};

#endif