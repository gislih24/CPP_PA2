template <typename T> struct DoublyLinkedList {
    struct Node {
        Node* prev; // predecessor
        T value;
        Node* next; // successor

        // Constructor
        Node() : prev(this), value(), next(this) {};

        // Copy Constructor
        Node(T const& _value) : prev(0), value(_value), next(0) {};
    };

    // We gotta make sure that:
    // sentinel.next always points to the head,
    // sentinel.prev always points to the tail.
    Node sentinel;
    // We gotta increment and decrement listSize jafnóðum.
    int listSize;
    void clearList() {
        Node* current = sentinel.next;
        while (current != &sentinel) {
            Node* next = current->next;
            current = next;
            delete current;
        }
        sentinel.next = &sentinel;
        sentinel.prev = &sentinel;
        listSize = 0;
    }

    // Constructor
    DoublyLinkedList() : listSize(0) {}; // sentinel() is done by default.

    // Must properly copy the contents of another instance of the data
    // structure. Ensure the two instances do not share memory afterwards!
    // Copy Constructor
    DoublyLinkedList(DoublyLinkedList const& other) : listSize(0) {
        // Append elements by inserting before sentinel (at the end).
        copyOtherList(other);
    }

    void copyOtherList(const DoublyLinkedList<T>& other) {
        copyOtherList(other);
    }

    // Assignment Operator
    DoublyLinkedList& operator=(DoublyLinkedList const& other) {
        if (this == &other)
            return *this; // guard in case of self assignment

        // clear current contents
        clearList();

        copyOtherList(other);
        return *this;
    }

    // Destructor
    ~DoublyLinkedList() {
        // Kill. Them. All. :( jk I'm not sad they deserve it :)
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

    // Must insert a node with the given element before the cursor, returning
    // the newly inserted node.
    // The name SHOULD be 'insert_before' IMHFO, but whatever.
    Node* insert(Node* cursor, T const& value) {
        // "Node*&" means "a reference to a pointer to a Node". So we're
        // changing that pointer directly.
        Node* newNode = new Node(value);

        newNode->prev = cursor->prev;
        newNode->next = cursor;
        cursor->prev->next = newNode;
        cursor->prev = newNode;

        listSize++;
        return newNode;
    }

    // Must erase the cursor node, returning the node after the erased node.
    Node* erase(Node* cursor) {
        Node* after = cursor->next;

        // Swap that shiiit.
        cursor->prev->next = cursor->next;
        cursor->next->prev = cursor->prev;
        cursor->prev = 0;
        cursor->next = 0;

        delete cursor; // Goodbye!

        listSize--;
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