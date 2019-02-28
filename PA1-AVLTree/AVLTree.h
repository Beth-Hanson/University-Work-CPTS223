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
// bool empty( )          --> Test for emptynode                Done
// int size( )            --> Quantity of elements innode       Failed Tests
// int height( )          --> Height of thenode (nullptr == -1) Done
// void add( x )          --> Insert new value x                Done
// void remove( x )       --> Remove node with value x          Done Unknown issue
// void clear ( )         --> Removes all elements fromnode     Done
// bool contains( x )     --> Return true if x is present       Done
// T findMin( )           --> Return smallest item value        Done
// T findMax( )           --> Return largest item value         Done
// void printPreOrder( )  --> Printnode in pre order to an ostream
// void ~AVLTree( )       --> Big Five Destructor               Done           
// AVLTree( )             --> Basic constructor                 
using std::max;

template <typename T>
class AVLTree
{
private:
    AVLNode<T> * _root;

public:
    AVLTree() : _root(nullptr) {}    // initializes root to nullptr

    ~AVLTree(){
        this->clear();
    }

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
      // AVLNode<T> *deadNode = deleteNode(_root, remVal);
      deleteNode(_root, remVal);
    }

    void clear() {
        // TODO: Delete all elements in thenode
       deleteTree(_root);
    }

    bool contains(const T & findVal) {
        // TODO: Return t/f if a given value is currently in thenode
        return search(_root, findVal);
    }

    int height() {
        return height(_root);
        // TODO: Return the current height of thenode
        // Remember! A null pointer is height -1
    }

    T findMin() {
        // Return the minimum *value* in thenode (not anode node)
        AVLNode<T> *temp = findSmall(_root);
        return temp->val;
    }

    T findMax() {
        // Return the maximum *value* in thenode (not anode node)
        AVLNode<T> *temp = findBig(_root);
        return temp->val;
    }

    // Prints thenode to ostream out in preorder traversal
    void printPreOrder(std::ostream& out) {
        printPreOrder(this->_root, out);
    }

    int size() {
        if (_root->nodeCount >= 0) { 
            return _root->nodeCount;
        }
        else{
            return 0;
        }
        // TODO: Return the size of thenode (number of nodes in thenode)
    }

// *************** Private /internal function implementation ******* //

private:
    // Should put your various internal balancing, rotating, and calculating functions here
    void insert(AVLNode<T> *&node, const T & newVal){
        //In progress
        if (node != nullptr){
            if(node->val > newVal){
                if(!node->left){
                    node->left = new AVLNode<T>(newVal);
                }
                else {
                    insert(node->left, newVal);
                }
            }
            else {
                if (!node->right){
                    node->right = new AVLNode<T>(newVal);
                }
                else {
                    insert(node->right, newVal);
                }
            }
        }
        else {
            node = new AVLNode<T>(newVal);
        }
        //Update height
        node->height = max(height(node->left), height(node->right)) + 1;
        // if (height(node->left) > height(node->right)) {
        //     node->height = height(node->left) + 1;
        // }
        // if (height(node->right) > height(node->left)) {
        //     node->height = height(node->right) + 1;
        // }
        //get balance
        int balance = this->checkBalance(node->left, node->right);
        //rotate as needed
        if (balance > 1){
            //Left-Left
            if (node->left != nullptr){
                if (newVal < node->left->val){
                node = rightRotate(node);
                }
                //Left-Right
                else if (newVal > node->left->val){
                    node->left = leftRotate(node->left);
                    node = rightRotate(node);
                }
            }
            //Right-Right
            else if (node->right != nullptr){
                if (newVal > node->right->val){
                    node = leftRotate(node);
                }
                //Right-Left
                else if (newVal < node->right->val){
                    node->right = rightRotate(node->right);
                    node = leftRotate(node);
                }
            }
            
        }
        
    }

    AVLNode<T> *&rightRotate(AVLNode<T> *&flip) {
        //in progress
        AVLNode<T> *flop = flip->left;
        if (flop->right){
            flip->left = flop->right;
        }
        else {
            flip->left = nullptr;
        }
        flop->right = flip;
        //Height update based off of MA3 and book
        flip->height = max(height(flip->left), height(flip->right)) + 1;
        flop->height = max(height(flop->left), height(flop->right)) + 1;

        flip = flop;
        // AVLNode<T> *temp = flop->right;

        // flop->right = flip;
        // flip->left = temp;

         //Height Update
        //Flip Height add 1
        // if (height(flip->left) > height(flip->right)) {
        //     flip->height = height(flip->left) + 1;
        // }
        // if (height(flip->right) > height(flip->left)) {
        //     flip->height = height(flip->right) + 1;
        // }
        
        return flip;
    }

    AVLNode<T> *&leftRotate(AVLNode<T> *&flip){
        //in progress
        AVLNode<T> *flop = flip->right;
        if (flop->left){
            flip->right = flop->left;
        }
        else {
            flip->right = nullptr;
        }
        flop->left = flip;
        //Height update based off of MA3 and book
        flip->height = max(height(flip->left), height(flip->right)) + 1;
        flop->height = max(height(flop->left), height(flop->right)) + 1;

        flip = flop;
        // AVLNode<T> *temp = flop->left;

        // flop->left = flip;
        // flip->right = temp;

        // //Height fix
        // if (height(flip->left) > height(flip->right)) {
        //     flip->height = height(flip->left) + 1;
        // }
        // if (height(flip->right) > height(flip->left)) {
        //     flip->height = height(flip->right) + 1;
        // }
        return flip;
    }

    void deleteTree(AVLNode<T> *&node){
        if(node != nullptr){
            deleteTree(node->left);
            deleteTree(node->right);
            node->~AVLNode();
            node = nullptr;
            delete node;
        }
    }

    void deleteNode(AVLNode<T> *& node, const T & remVal){
       if (!node) return; //node;
       if (remVal < node->val){
           //node->left = deleteNode(node->left, remVal);
           deleteNode(node->left, remVal);
       }
       else if (remVal > node->val){
           //node->right = deleteNode(node->right, remVal);
           deleteNode(node->right, remVal);
       }
       else{
           if(node->left == nullptr || node->right == nullptr){
               //fix if fails
               AVLNode<T> *temp = node;
               node = node->left ? node->left : node->right;
               temp->~AVLNode();
               delete temp;
               //return node;
           }
           else{
                AVLNode<T> *temp = findSmall(node->right);
                node->val = temp->val;
                //node->right = deleteNode(node->right, temp->val);
                deleteNode(node->right, temp->val);
            }
       }
       //Height Update
       if (node){
           node->height = max(height(node->left), height(node->right)) + 1;
           //get balance
            int balance = this->checkBalance(node->left, node->right);
            //rotate as needed
            if (balance > 1){
            //Left-Left
                if (node->left != nullptr){
                    if (remVal > node->left->val){
                    node = rightRotate(node);
                    }
                //Left-Right
                    else if (remVal < node->left->val){
                        node->left = leftRotate(node->left);
                        node = rightRotate(node);
                    }
                }
            //Right-Right
                else if (node->right != nullptr){
                    if (remVal < node->right->val){
                        node = leftRotate(node);
                    }
                //Right-Left
                    else if (remVal > node->right->val){
                        node->right = rightRotate(node->right);
                        node = leftRotate(node);
                    }
                }
            
            }
       } 
        
        //return node;
    }

    bool search(AVLNode<T> *& node, const T & findVal){
        if (node != nullptr){
            if(findVal == node->val){
                return true;
            }
            if(findVal > node->val){
                return search(node->right, findVal);
            }
            if(findVal < node->val){
                return search(node->left, findVal);
            }
        }
        return false;
    }
    
    AVLNode<T> *findSmall(AVLNode<T> *&node) {
	    AVLNode<T> *temp = node;
	    if (temp->left != nullptr) {
		    return findSmall(temp->left);
	    }
	    return temp;
    }

    AVLNode<T> *findBig(AVLNode<T> *&node) {
	    AVLNode<T> *temp = node;
	    if (temp->right != nullptr) {
		    return findBig(temp->right);
	    }
	    return temp;
    }

    int checkBalance(AVLNode<T> *&left, AVLNode<T> *&right){
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
