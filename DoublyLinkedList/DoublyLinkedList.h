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
    Node<T> sentinel;
    // Size of the list.
    int list_size;

    /**
     * @brief Clears the list, freeing all allocated memory.
     */
    void clear_list() {
        Node<T>* current = sentinel.next;
        while (current != &sentinel) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        sentinel.next = &sentinel;
        sentinel.prev = &sentinel;
        list_size = 0;
    }

    /**
     * @brief Copies the contents of another list into this list.
     *
     * @param other The list to be copied.
     */
    void copy_other_list(DoublyLinkedList const& other) {
        Node<T>* cur = other.sentinel.next;
        while (cur != &other.sentinel) {
            insert(&sentinel, cur->data); // append at end
            cur = cur->next;
        }
    }

  public:
    /**
     * @brief Constructor that initializes an empty list.
     */
    DoublyLinkedList() : list_size(0) {};

    // Copy Constructor
    DoublyLinkedList(DoublyLinkedList const& other) : list_size(0) {
        copy_other_list(other);
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

        clear_list();
        copy_other_list(other);
        return *this;
    }

    // Destructor
    ~DoublyLinkedList() {
        clear_list();
    }

    // Return the first node(head) of the list, not a sentinel node.
    Node<T>* front() {
        return sentinel.next;
    }

    // Return the last node(tail) of the list, a sentinel node.
    Node<T>* back() {
        return &sentinel;
    }

    // Kattis wants these for some reason...
    // Return the first node(head) of the list, not a sentinel node.
    Node<T>* begin_node() {
        return front();
    }
    // Return the last node(tail) of the list, a sentinel node.
    Node<T>* sentinel_end_node() {
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
    Node<T>* insert(Node<T>* cursor, T const& data) {
        // "Node<T>*&" means "a reference to a pointer to a Node<T>". So we're
        // changing that pointer directly.
        Node<T>* new_node = new Node<T>(data);

        new_node->prev = cursor->prev;
        new_node->next = cursor;
        cursor->prev->next = new_node;
        cursor->prev = new_node;

        list_size++;
        return new_node;
    }

    /**
     * @brief Erases the cursor node from the list, returning the node after the
     *        erased node.
     *
     * @param cursor The node to be erased.
     *
     * @return A pointer to the node that was after the erased node.
     */
    Node<T>* erase(Node<T>* cursor) {
        Node<T>* after = cursor->next;

        // Swap them
        cursor->prev->next = cursor->next;
        cursor->next->prev = cursor->prev;

        delete cursor;
        --list_size;
        return after;
    }

    // Return the node before the cursor node
    Node<T>* predecessor(Node<T>* cursor) {
        return cursor->prev;
    }

    // Return the node after the cursor node
    Node<T>* successor(Node<T>* cursor) {
        return cursor->next;
    }

    // Return the size of the instance
    int size() const {
        return list_size;
    }
};

#endif