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
    // sentinel.prev always points to the head,
    // sentinel.next always points to the tail.
    // The sentinel node is always located right before the tail.
    Node sentinel;
    // We gotta increment and decrement listSize jafnóðum.
    int listSize;

    // Constructor
    DoublyLinkedList() : listSize(0) {}; // sentinel() is done by default.

    // Copy Constructor
    DoublyLinkedList(DoublyLinkedList const& other) : listSize(0) {
        // Append elements by inserting before sentinel (at the end).
        const Node* currentNode = other.sentinel.next;
        while (currentNode != &other.sentinel) {
            insert(&sentinel,
                   currentNode->value);      // Insert before our sentinel.
            currentNode = currentNode->next; // Traverse forward.
        }
    }

    // Destructor
    ~DoublyLinkedList() {
        // Kill. Them. All. :( jk I'm not sad they deserve it :)
        Node* currentNode = sentinel.prev;
        while (currentNode != &sentinel) {
            Node* nextNode = currentNode->next;
            delete currentNode;
            currentNode = nextNode;
        }
        sentinel.next = &sentinel;
        sentinel.prev = &sentinel;
        listSize = 0;
    }

    int size() const { return listSize };

    Node* front() { return sentinel.next };
    Node* back() { return sentinel.prev };

    // The name SHOULD be 'insert_before' IMHFO, but whatever.
    Node* insert(Node*& cursor, T const& value) {
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

    Node* erase(Node*& cursor) {
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

    Node* predecessor(Node*& cursor) {
        return cursor->prev;
    }

    Node* successor(Node*& cursor) {
        return cursor->next;
    }
};