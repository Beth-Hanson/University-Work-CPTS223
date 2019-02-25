/*
 *  Yet another AVLnode edition
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
// bool empty( )          --> Test for emptynode
// int size( )            --> Quantity of elements innode
// int height( )          --> Height of thenode (nullptr == -1)
// void add( x )          --> Insert new value x
// void remove( x )       --> Remove node with value x
// void clear ( )         --> Removes all elements fromnode
// bool contains( x )     --> Return true if x is present
// T findMin( )           --> Return smallest item value
// T findMax( )           --> Return largest item value
// void printPreOrder( )  --> Printnode in pre order to an ostream
// void ~AVLTree( )       --> Big Five Destructor
// AVLTree( )             --> Basic constructor


template <typename T>
class AVLTree
{
private:
    AVLNode<T> * _root;

public:
    AVLTree() : _root(nullptr) {}    // initializes root to nullptr

    /* Returns true if thenode is empty */
    bool empty() {
        if (_root == nullptr){
            return true;
        } 
        else {
            return false;
        }
        // TODO: Properly return t/f if thenode is empty or not
    }

    void add(const T & newVal) {
        // TODO: implement adding a value to thenode
        insert(_root, newVal);
    }

    void remove(const T & remVal) {
        // TODO: Implemente properly removing a node and rebalancing thenode
    }

    void clear() {
        // TODO: Delete all elements in thenode
       deleteTree(_root);
    }

    bool contains(const T & findVal) {
        // TODO: Return t/f if a given value is currently in thenode
        return false;
    }

    int height() {
        return height(_root);
        // TODO: Return the current height of thenode
        // Remember! A null pointer is height -1
    }

    T findMin() {
        // Return the minimum *value* in thenode (not anode node)
        return (T)NULL; // this is to allow the tests to fail - should definitely be changed!
    }

    T findMax() {
        // Return the maximum *value* in thenode (not anode node)
        return (T)NULL; // this is to allow the tests to fail - should definitely be changed!
    }

    // Prints thenode to ostream out in preorder traversal
    void printPreOrder(std::ostream& out) {
        printPreOrder(this->_root, out);
    }

    int size() {
        return -1;
        // TODO: Return the size of thenode (number of nodes in thenode)
    }

// *************** Private /internal function implementation ******* //

private:
    // Should put your various internal balancing, rotating, and calculating functions here
    void insert(AVLNode<T> *node, const T & newVal){
        //In progress
        if (node != nullptr){
            if (newVal > node->val){
                if (node->right != nullptr){
                    insert(node->right, newVal);
                }
                else {
                    node->right = new AVLNode<T>(newVal);
                }
            }
            else if (newVal < node->val){
                if (node->left != nullptr){
                    insert(node->left, newVal);
                }
                else {
                    node->left = new AVLNode<T>(newVal);
                }
            }
        }
        else {
            node = new AVLNode<T>(newVal);
        }
        //Update height
        if (height(node->left) > height(node->right)) {
            node->height = height(node->left) + 1;
        }
        if (height(node->right) > height(node->left)) {
            node->height = height(node->right) + 1;
        }
        //get balance
        int balance = this->checkBalance(node->left, node->right);
        //rotate as needed
        if (balance > 1){
            //Left-Left
            if (newVal < node->left->val){
                node = leftRotate(node);
            }
            //Right-Right
            if (newVal > node->right->val){
                node = rightRotate(node);
            }
            //Left-Right
            if (newVal > node->left->val){
                node->left = leftRotate(node->left);
                node = rightRotate(node);
            }
            //Right-Left
            if (newVal < node->right->val){
                node->right = rightRotate(node->right);
                node = leftRotate(node);
            }
        }
        _root = node;
    }

    AVLNode<T> *rightRotate(AVLNode<T> *flip) {
        //in progress
        AVLNode<T> *flop = flip->left;
        AVLNode<T> *temp = flop->right;

        flop->right = flip;
        flip->left = temp;

         //Height Update
        //Flip Height add 1
        if (height(flip->left) > height(flip->right)) {
            flip->height = height(flip->left) + 1;
        }
        if (height(flip->right) > height(flip->left)) {
            flip->height = height(flip->right) + 1;
        }
        return flip;
    }

    AVLNode<T> *leftRotate(AVLNode<T> *flip){
        //in progress
        AVLNode<T> *flop = flip->right;
        AVLNode<T> *temp = flop->left;

        flop->left = flip;
        flip->right = temp;

        //Height fix
        if (height(flip->left) > height(flip->right)) {
            flip->height = height(flip->left) + 1;
        }
        if (height(flip->right) > height(flip->left)) {
            flip->height = height(flip->right) + 1;
        }
        return flip;
    }
    void deleteTree(AVLNode<T> *node){
        if(node->left != nullptr){
            deleteTree(node->left);
        }
        if(node->right != nullptr){
            deleteTree(node->right);
        }
        if(node->left == nullptr && node->right == nullptr){
            delete node;
        }
    }

    int checkBalance(AVLNode<T> *left, AVLNode<T> *right){
        //in progress
        int balance = abs(height(left) - height(right));
        return balance;
    }

    // Freebie: neat little function to safely get a node's height
    int height( AVLNode<T> * t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    // Traverses thenode and prints in pre order
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
