/*
 *  Yet another AVL tree edition
 * 
 *  Contributors:
 *      Aaron S. Crandall <acrandal@wsu.edu> - 2018
 * 
 */

#ifndef __AVLTree_H
#define __AVLTree_H

#include <ostream>
#include <algorithm>     // Includes a max(a,b) function
#include <exception>

#include "AVLNode.h"

// AVLTree class
// ******************PUBLIC OPERATIONS*********************
// bool empty( )          --> Test for empty tree
// int size( )            --> Quantity of elements in tree
// int height( )          --> Height of the tree (nullptr == -1)
// void add( x )          --> Insert new value x
// void remove( x )       --> Remove node with value x
// void clear ( )         --> Removes all elements from tree
// bool contains( x )     --> Return true if x is present
// T findMin( )           --> Return smallest item value
// T findMax( )           --> Return largest item value
// void printPreOrder( )  --> Print tree in pre order to an ostream
// void ~AVLTree( )       --> Big Five Destructor
// AVLTree( )             --> Basic constructor


template <typename T>
class AVLTree
{
private:
    AVLNode<T> * _root;

public:
    AVLTree() : _root(nullptr) {}    // initializes root to nullptr

    /* Returns true if the tree is empty */
    bool empty() {
        return false;
        // TODO: Properly return t/f if the tree is empty or not
    }

    void add(const T & newVal) {
        // TODO: implement adding a value to the tree
    }

    void remove(const T & remVal) {
        // TODO: Implemente properly removing a node and rebalancing the tree
    }

    void clear() {
        // TODO: Delete all elements in the tree
    }

    bool contains(const T & findVal) {
        // TODO: Return t/f if a given value is currently in the tree
        return false;
    }

    int height() {
        return -2;
        // TODO: Return the current height of the tree
        // Remember! A null pointer is height -1
    }

    T findMin() {
        // Return the minimum *value* in the tree (not a tree node)
        return (T)NULL; // this is to allow the tests to fail - should definitely be changed!
    }

    T findMax() {
        // Return the maximum *value* in the tree (not a tree node)
        return (T)NULL; // this is to allow the tests to fail - should definitely be changed!
    }

    // Prints the tree to ostream out in preorder traversal
    void printPreOrder(std::ostream& out) {
        printPreOrder(this->_root, out);
    }

    int size() {
        return -1;
        // TODO: Return the size of the tree (number of nodes in the tree)
    }

// *************** Private /internal function implementation ******* //

private:
    // Should put your various internal balancing, rotating, and calculating functions here

    // Freebie: neat little function to safely get a node's height
    int height( AVLNode<T> * t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    // Traverses the tree and prints in pre order
    // This is used a lot in the testing system, changing it would be troublesome
    void printPreOrder(AVLNode<T> * & t, std::ostream& out)
    {
        if( t != nullptr )
        {
            out << t->val << " ";
            printPreOrder(t->left, out);
            printPreOrder(t->right, out);
        }
    }



};




#endif
