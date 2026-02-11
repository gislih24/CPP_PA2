#ifndef NODE
#define NODE

template <typename K, typename V> struct TreapNode {
    K key;
    V value;
    int priority;
    TreapNode* left;
    TreapNode* right;
    int size; // size of subtree rooted here

    // Constructor
    TreapNode() : key() value(), priority(), left(0), right(0), size(1) {};

    // Copy Constructor
    TreapNode(V const& _value)
        : key(), value(_value), priority(), left(0), right(0), size(1) {};
};

#endif

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

// Self-balancing BST using a treap.

template <typename K, typename V> struct Treap {
    // xorshift32 for simple random number generation.
    int rng_state_;

    int genRandomNumber() {
        rng_state_ ^= rng_state_ << 13;
        rng_state_ ^= rng_state_ >> 17;
        rng_state_ ^= rng_state_ << 5;
        return rng_state_;
    }

    TreapNode<K, V>* root_;

    // • Default construction - Initializes an empty instance with a reasonable
    // capacity. (This is not tested explicitly here!)

    // • Assignment and copy construction - Must properly copy the contents of
    // another instance of the data structure. (Ensure the two instances do not
    // share memory afterwards!)

    // • find() - Return the node with the given key. If such a node does not
    // exist, returns a sentinel value. (Simple BST find)
    TreapNode<K, V>* find(TreapNode<K, V>* cursor, K keyToFind) {
        TreapNode<K, V>* current = root_;
        if (keyToFind > current->key) {
            find(current->right, keyToFind);
        } else if (keyToFind < current->key) {
            find(current->left, keyToFind)
        } else if (keyToFind == current->key) {
            return current;
        } else {
            return cursor; // TODO
        }
    }

    // • lower_bound() - Return the node with the smallest key which is greater
    // than or equal to the given key, If such a node does not exist, returns a
    // sentinel value.
    TreapNode<K, V>* lower_bound() {}

    // • upper_bound() - Return the node with the smallest key which is
    // strictly greater than the given key. If such a node does not exist,
    // returns sentinel value.

    // • insert() - Must insert a node with the given key-value pair,
    // returning the newly inserted node. If the key exists already, nothing
    // is inserted and the existing node is returned.
    void insert(TreapNode<K, V>* cursor, K key, V const& value) {
        TreapNode<K, V>* newNode = new TreapNode<T>;
        newNode->value = value;
        newNode->priority = genRandomNumber();

        /*
        find(x)
        insert like in a BST
        if x.priority > parent.priority:
            if x == parent.left:
                right_rotation() // x.right = parent, etc.
            if x == parent.right:
                left_rotation(parent) // x.left = parent, etc.
        */
    }

    // • Erase - Must remove the given node. If given node is sentinel value,
    // does nothing.
    /*
    Basics for how erase might be done:
    find(x)
    while (x.child_count == 2):
        if (x.right.priority >= x.left.priority):
            rotate_left()
        if (x.left.priority > x.right.priority):
            rotate_right()
    if (x.is_leaf()):
        delete(x)
    if (x.child_count == 1):
        replace x with x's child
    */

    // • front() - Return the node with the minimum key in the tree. If no such
    // node exists, returns a sentinel value.

    // • back() - Return the node with the maximum key in the tree. If no such
    // node exists, returns a sentinel value.

    // • predecessor() - Return the node before the given node, that is, the
    // node with the largest key which is lower than the given node’s key. If
    // such a node does not exist, or if given node is sentinel value, returns
    // sentinel value.

    // • successor() - Return the node after the given node, that is, the node
    // with the smallest key which is higher than the given node’s key. If such
    // a node does not exist, or if given node is sentinel value, returns
    // sentinel value.

    // • rank() - Return the index of the node within the tree’s left-to-right
    // order, or in other words, how many nodes have smaller keys than the given
    // node.

    // • kth() - Return the node with the given index within the tree’s
    // left-to-right order.

    // • Element Access - Provide access to reading and writing the value
    // associated with a key, usually directly through the public interface of a
    // node instead of the tree.

    // • size() - Return the size of the instance.
};

#endif