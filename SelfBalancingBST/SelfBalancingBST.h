#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

template <typename T> struct SelfBalancingBST {
    /*
    • Default construction - Initializes an empty instance with a reasonable
    capacity. (This is not tested explicitly here!)

    • Assignment and copy construction - Must properly copy the contents of
    another instance of the data structure. (Ensure the two instances do not
    share memory afterwards!)

    • Find - Return the node with the given key. If such a node does not exist,
    returns a sentinel value.

    • Lower Bound - Return the node with the smallest key which is greater than
    or equal to the given key, If such a node does not exist, returns a
    sentinel value.

    • Upper Bound - Return the node with the smallest key which is strictly
    greater than the given key. If such a node does not exist, returns sentinel
    value.

    • Insert - Must insert a node with the given key-value pair, returning the
    newly inserted node. If the key exists already, nothing is inserted and the
    existing node is returned.

    • Erase - Must remove the given node. If given node is sentinel value, does
    nothing.

    • Front - Return the node with the minimum key in the tree. If no such node
    exists, returns a sentinel value.

    • Back - Return the node with the maximum key in the tree. If no such node
    exists, returns a sentinel value.

    • Predecessor - Return the node before the given node, that is, the node
    with the largest key which is lower than the given node’s key. If such a
    node does not exist, or if given node is sentinel value, returns sentinel
    value.

    • Successor - Return the node after the given node, that is, the node with
    the smallest key which is higher than the given node’s key. If such a node
    does not exist, or if given node is sentinel value, returns sentinel value.

    • Rank - Return the index of the node within the tree’s left-to-right
    order, or in other words, how many nodes have smaller keys than the given
    node.

    • k-th Element - Return the node with the given index within the tree’s
    left-to-right order.

    • Element Access - Provide access to reading and writing the value
    associated with a key, usually directly through the public interface of a
    node instead of the tree.

    • Size - Return the size of the instance.
    */
};

#endif