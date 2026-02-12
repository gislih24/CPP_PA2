#ifndef SELF_BALANCING_BST_H
#define SELF_BALANCING_BST_H

// Treap-based self-balancing BST.

template <typename K, typename V> struct TreapNode {
    K key;
    V value;

    unsigned int priority; // heap key (smaller = higher priority)
    int subtree_size;      // size of subtree rooted here

    TreapNode* left;
    TreapNode* right;
    TreapNode* parent;

    TreapNode(const K& k, const V& v, unsigned int parent_node)
        : key(k), value(v), priority(parent_node), subtree_size(1), left(0),
          right(0), parent(0) {}
};

template <typename K, typename V> class Treap {
  private:
    TNode* _root;

    /**
     * @brief Helper function to get the size of the subtree rooted at the
     * given node.
     *
     * @param tree_node Pointer to the node whose subtree size we want to get.
     *
     * @return Size of the subtree rooted at the given node. If the node is
     * NULL, returns 0.
     */
    static int get_subtree_size(TNode* tree_node) {
        if (tree_node == 0) {
            return 0;
        } else {
            return tree_node->subtree_size;
        };
    }

    /**
     * @brief Helper function to update the subtree size of the given node.
     *
     * Updates the size based on the sizes of its left and right children.
     * Called after any modification to the subtree so that sizer remain
     * accurate.
     *
     * @param node Pointer to the node whose subtree size we want to update.
     */
    static void pull(TNode* node) {
        if (node != 0) {
            node->subtree_size = 1 + get_subtree_size(node->left) +
                                 get_subtree_size(node->right);
        }
    }

    /**
     * @brief Generates the next priority value for a new node.
     *
     * This is used in the insert() operation to assign a priority to the newly
     * inserted node.
     *
     * @return The next priority value to be assigned to a new node.
     */
    static unsigned int next_priority() {
        // Basic way to generate a random number that I toootally came up with
        // myself.
        static unsigned int state = 2463534242u;
        state = state * 1103515245u + 12345u;
        return state;
    }

    /**
     * @brief Helper function to update the subtree sizes of all ancestors of
     * the given node.
     *
     * This should be called after any modification to the subtree (like
     * rotations or insertions) to ensure that the subtree sizes remain accurate
     * on the path from the modified node up to the root.
     *
     * @param node Pointer to the node from which we want to start updating
     * subtree sizes.
     */
    void pull_up(TNode* node) {
        while (node != 0) {
            pull(node);
            node = node->parent;
        }
    }

    /**
     * @brief Performs a left rotation on the given node to maintain the heap
     * property in the treap.
     *
     * @param x Pointer to the node on which to perform the left rotation.
     */
    void rotate_left(TNode* x) {
        // x must have a right child.
        TNode* y = x->right;
        if (y == 0) {
            return;
        }

        TNode* b = y->left;

        // Link y with x's parent.
        y->parent = x->parent;
        if (x->parent == 0) {
            _root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }

        // Put x on y's left.
        y->left = x;
        x->parent = y;

        // Move b to x's right.
        x->right = b;
        if (b != 0) {
            b->parent = x;
        }

        // Update sizes for the rotated pair.
        pull(x);
        pull(y);
    }

    /**
     * @brief Performs a right rotation on the given node to maintain the heap
     * property in the treap.
     *
     * @param x Pointer to the node on which to perform the right rotation (must
     * have a left child for the rotation to be valid).
     */
    void rotate_right(TNode* x) {
        // x must have a left child.
        TNode* y = x->left;
        if (y == 0) {
            return;
        }

        TNode* b = y->right;

        // Link y with x's parent.
        y->parent = x->parent;
        if (x->parent == 0) {
            _root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }

        // Put x on y's right.
        y->right = x;
        x->parent = y;

        // Move b to x's left.
        x->left = b;
        if (b != 0) {
            b->parent = x;
        }

        // Update sizes for the rotated pair.
        pull(x);
        pull(y);
    }

    /**
     * @brief Recursively destroys the subtree rooted at the given node, freeing
     * all associated memory.
     *
     * @param tree_node Pointer to the root of the subtree to be destroyed. If
     * the pointer is NULL, the function does nothing.
     */
    static void destroy_subtree(TNode* tree_node) {
        if (tree_node == 0) {
            return;
        }
        destroy_subtree(tree_node->left);
        destroy_subtree(tree_node->right);
        delete tree_node;
    }

    /**
     * @brief Recursively clones the subtree rooted at the given source node,
     * creating a new subtree with the same structure and values.
     *
     * @param source_node Pointer to the root of the subtree to be cloned.
     * @param parent_node Pointer to the parent node for the new subtree (used
     * to set parent pointers correctly in the cloned subtree).
     *
     * @return Pointer to the root of the newly cloned subtree. If the source
     * node is NULL, returns NULL. The caller is responsible for managing the
     * memory of the cloned subtree.
     */
    static TNode* clone_subtree(TNode* source_node, TNode* parent_node) {
        if (source_node == 0) {
            return 0;
        }

        TNode* new_tree_node = new TNode(source_node->key, source_node->value,
                                         source_node->priority);
        new_tree_node->parent = parent_node;
        new_tree_node->left = clone_subtree(source_node->left, new_tree_node);
        new_tree_node->right = clone_subtree(source_node->right, new_tree_node);
        pull(new_tree_node);
        return new_tree_node;
    }

  public:
    typedef TreapNode<K, V> TNode;

    // Constructor
    Treap() : _root(0) {}

    // Copy constructor
    Treap(const Treap& other) : _root(0) {
        _root = clone_subtree(other._root, 0);
    }

    // Destructor
    ~Treap() {
        clear();
    }

    // Assignment operator
    Treap& operator=(const Treap& other) {
        if (this != &other) {
            clear();
            _root = clone_subtree(other._root, 0);
        }
        return *this;
    }

    // Returns number of nodes.
    int size() const {
        return get_subtree_size(_root);
    }

    // Removes all nodes.
    void clear() {
        destroy_subtree(_root);
        _root = 0;
    }

    /**
     * @brief Finds the node with the given key in the treap.
     *
     * @param key The key to search for in the treap.
     *
     * @return Pointer to the node with the given key if it exists in the treap;
     * otherwise, returns NULL.
     */
    TNode* find(const K& key) const {
        TNode* curr_node = _root;
        while (curr_node != 0) {
            if (key < curr_node->key) {
                curr_node = curr_node->left;
            } else if (curr_node->key < key) {
                curr_node = curr_node->right;
            } else {
                return curr_node; // key found
            }
        }
        return 0;
    }

    /**
     * @brief Finds the node with the smallest key that is greater than or equal
     * to the given key in the treap.
     *
     * @param key The key to compare against when searching for the lower bound
     * in the treap.
     *
     * @return Pointer to the node with the smallest key that is greater than or
     * equal to the given key if such a node exists in the treap; otherwise,
     * returns NULL.
     */
    TNode* lower_bound(const K& key) const {
        TNode* curr_node = _root;
        TNode* best_node = 0;
        while (curr_node != 0) {
            if (!(curr_node->key < key)) { // curr_node->key >= key
                best_node = curr_node;
                curr_node = curr_node->left;
            } else {
                curr_node = curr_node->right;
            }
        }
        return best_node;
    }

    /**
     * @brief Finds the node with the smallest key that is strictly greater than
     * the given key in the treap.
     *
     * @param key The key to compare against when searching for the upper bound
     * in the treap.
     *
     * @return Pointer to the node with the smallest key that is strictly
     * greater than the given key if such a node exists in the treap;
     * otherwise, returns NULL.
     */
    TNode* upper_bound(const K& key) const {
        TNode* curr_node = _root;
        TNode* best_node = 0;
        while (curr_node != 0) {
            if (key < curr_node->key) { // curr_node->key > key
                best_node = curr_node;
                curr_node = curr_node->left;
            } else {
                curr_node = curr_node->right;
            }
        }
        return best_node;
    }

    /**
     * @brief Inserts a new node with the given key and value into the treap.
     *
     * @param key The key for the new node to be inserted into the treap.
     * @param value The value for the new node to be inserted into the treap.
     *
     * @return Pointer to the newly inserted node if the key was not already
     * present in the treap; otherwise, returns a pointer to the existing node
     * with the same key without modifying the treap.
     */
    TNode* insert(const K& key, const V& value) {
        TNode* parent = 0;
        TNode* curr_node = _root;
        while (curr_node != 0) {
            parent = curr_node;
            if (key < curr_node->key) {
                curr_node = curr_node->left;
            } else if (curr_node->key < key) {
                curr_node = curr_node->right;
            } else {
                return curr_node; // key already exists
            }
        }

        // Create the new node with a random priority and link it to the parent.
        TNode* new_node = new TNode(key, value, next_priority());
        new_node->parent = parent;

        // Link new node to parent.
        if (parent == 0) {
            _root = new_node;
        } else if (key < parent->key) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }

        // Fix subtree sizes up from the parent.
        pull_up(parent);

        // Restore heap property by rotating the new node up until it's in the
        // correct position.
        while (new_node->parent != 0 &&
               new_node->priority < new_node->parent->priority) {
            if (new_node == new_node->parent->left) {
                rotate_right(new_node->parent);
            } else {
                rotate_left(new_node->parent);
            }
        }

        // Ensure sizes are consistent on the path to root.
        pull_up(new_node);
        return new_node;
    }

    /**
     * @brief Removes the given node from the treap while maintaining the
     * treap's properties.
     *
     * @param node Pointer to the node that should be removed from the treap. If
     * the pointer is NULL, the function does nothing.
     */
    void erase(TNode* node) {
        if (node == 0) {
            return;
        }

        // Rotate the node down until it becomes a leaf.
        while (node->left != 0 || node->right != 0) {
            if (node->left == 0) {
                rotate_left(node);
            } else if (node->right == 0) {
                rotate_right(node);
            } else if (node->left->priority < node->right->priority) {
                rotate_right(node);
            } else {
                rotate_left(node);
            }
        }

        // Detach the leaf node from its parent and delete it.
        TNode* parent = node->parent;
        if (parent == 0) {
            _root = 0;
        } else if (parent->left == node) {
            parent->left = 0;
        } else {
            parent->right = 0;
        }

        delete node;
        pull_up(parent);
    }

    /**
     * @brief Finds the node with the smallest key in the treap.
     *
     * This is the front element in an in-order traversal of the treap.
     *
     * @return Pointer to the node with the smallest key in the treap if the
     * treap is not empty; otherwise, returns NULL.
     */
    TNode* front() const {
        TNode* curr_node = _root;
        if (curr_node == 0) {
            return 0;
        }

        while (curr_node->left != 0) {
            curr_node = curr_node->left;
        }
        return curr_node;
    }

    /**
     * @brief Finds the node with the largest key in the treap.
     *
     * This is the back element in an in-order traversal of the treap.
     *
     * @return Pointer to the node with the largest key in the treap if the
     * treap is not empty; otherwise, returns NULL.
     */
    TNode* back() const {
        TNode* curr_node = _root;
        if (curr_node == 0) {
            return 0;
        }

        while (curr_node->right != 0) {
            curr_node = curr_node->right;
        }
        return curr_node;
    }

    /**
     * @brief Finds the in-order successor of the given node in the treap.
     *
     * This is the node with the smallest key that is greater than the given
     * node's key.
     *
     * @param node Pointer to the node whose in-order successor we want to find.
     *
     * @return Pointer to the in-order successor of the given node if it exists
     * in the treap; otherwise, returns NULL.
     */
    TNode* successor(TNode* node) const {
        if (node == 0) {
            return 0;
        }

        // If there's a right child, the successor is the leftmost node in the
        // right subtree.
        if (node->right != 0) {
            TNode* curr_node = node->right;
            while (curr_node->left != 0) {
                curr_node = curr_node->left;
            }
            return curr_node;
        }
        // Otherwise, the successor is the lowest ancestor of the node whose
        // left child is also an ancestor of the node.
        TNode* curr_node = node;
        TNode* parent_node = curr_node->parent;
        while (parent_node != 0 && curr_node == parent_node->right) {
            curr_node = parent_node;
            parent_node = parent_node->parent;
        }
        return parent_node;
    }

    /**
     * @brief Finds the in-order predecessor of the given node in the treap.
     *
     * @param node Pointer to the node whose in-order predecessor we want to
     * find.
     *
     * @return Pointer to the in-order predecessor of the given node if it
     * exists in the treap; otherwise, returns NULL.
     */
    TNode* predecessor(TNode* node) const {
        if (node == 0) {
            return 0;
        }
        if (node->left != 0) {
            TNode* curr_node = node->left;
            while (curr_node->right != 0) {
                curr_node = curr_node->right;
            }
            return curr_node;
        }
        TNode* curr_node = node;
        TNode* parent_node = curr_node->parent;
        while (parent_node != 0 && curr_node == parent_node->left) {
            curr_node = parent_node;
            parent_node = parent_node->parent;
        }
        return parent_node;
    }

    /**
     * @brief Calculates the in-order rank of the given node in the treap
     *
     * This is the number of nodes in the treap that have keys less than the
     * given node's key.
     *
     * @param node Pointer to the node whose in-order rank we want to calculate.
     *
     * @return The in-order rank of the given node in the treap if the node
     * exists in the treap; otherwise, returns -1.
     */
    int rank(TNode* node) const {
        if (node == 0) {
            return -1;
        }

        int r = get_subtree_size(node->left);
        TNode* curr_node = node;
        while (curr_node->parent != 0) {
            if (curr_node == curr_node->parent->right) {
                r += 1 + get_subtree_size(curr_node->parent->left);
            }
            curr_node = curr_node->parent;
        }
        return r;
    }

    /**
     * @brief Finds the node with the k-th smallest key in the treap.
     *
     * @param k The 0-based index of the node to find based on in-order
     * traversal of the treap.
     *
     * @return Pointer to the node with the k-th smallest key in the treap if
     * such a node exists; otherwise, returns NULL.
     */
    TNode* kth(int k) const {
        if (k < 0 || k >= get_subtree_size(_root)) {
            return 0;
        }

        TNode* curr_node = _root;
        // At each step, we check the size of the left subtree to determine
        // whether to go left, right, or return the current node.
        while (curr_node != 0) {
            int left_sz = get_subtree_size(curr_node->left);
            if (k < left_sz) {
                curr_node = curr_node->left;
            } else if (k == left_sz) {
                return curr_node;
            } else {
                k -= left_sz + 1;
                curr_node = curr_node->right;
            }
        }
        return 0;
    }

    // Alias, just in case.
    TNode* kth_element(int k) const {
        return kth(k);
    }
};

#endif // SELF_BALANCING_BST_H
