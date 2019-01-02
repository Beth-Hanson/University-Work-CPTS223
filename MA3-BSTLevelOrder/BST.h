/*
 * Binary Search Tree implementation 
 *  - heavily lifted from https://gist.github.com/mgechev/5911348
 *  - though, very very hacked up since then
 *
 * Simple keys and basic operations BST
 *
 * Aaron Crandall - 2016 - Added / updated:
 *  * Inorder, Preorder, Postorder printouts
 *  * Stubbed in level order printout
 * Aaron Crandall - 2017 - Heavy overhaul of tests & behaviors
 *  * Added BigFive (like we should!)
 *  * Added several public interfaces for tree features
 * Aaron Crandall - 2019 - Fixed -Wshadow errors
 *  * Identified a few badly done interface fixes
 *
 */

#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <cstring>		// strcmp
#include <vector>
#include <queue>
#include <initializer_list>

using namespace std;

/*
 *  Datastructure for a single tree node
 */ 
template <class T>
struct Node {
public:
    T value;
    Node *left;
    Node *right;

    Node(T val) {
        this->value = val;
        this->left = NULL;
        this->right = NULL;
    }

    Node(T val, Node<T> * setLeft, Node<T> * setRight) {
        this->value = val;
        this->left = setLeft;
        this->right = setRight;
    }
};

/*
 * Binary Search Tree (BST) class implementation
 */
template <class T>
class BST {

    private:
    Node<T> *_root;         // Root of the tree nodes
    bool _debug = false;    // Enable extra output

    /* clone a passed in tree, returns pointer to new tree */
    Node<T> * cloneTree(Node<T> *t) {
        if( t == NULL )
            return NULL;
        else
            return new Node<T>( t->value, 
                                cloneTree( t->left ),
                                cloneTree( t->right ) );
    }

    /* Recursively delete the tree nodes */
    void makeEmptyHelper(Node<T> *t) {
        if( t != NULL ) {
            makeEmptyHelper( t->left );
            makeEmptyHelper( t->right );
            delete t;
        }
    }

    /* Add new T val to the tree */
    void addHelper(Node<T> *root, T val) {
        if (root->value > val) {
            if (!root->left) {
                root->left = new Node<T>(val);
            } else {
                addHelper(root->left, val);
            }
        } else {
            if (!root->right) {
                root->right = new Node<T>(val);
            } else {
                addHelper(root->right, val);
            }
        }
    }

    /* Print tree out in inorder (A + B) */
    void printInOrderHelper(Node<T> *root) {
        if (!root) return;
        printInOrderHelper(root->left);
        cout << root->value << ' ';
        printInOrderHelper(root->right);
    }

    /* Print tree out in post order (A B +) */
    void printPostOrderHelper(Node<T> *root) {
        if (!root) return;
        printPostOrderHelper(root->left);
        printPostOrderHelper(root->right);
        cout << root->value << ' ';
    }

    /* Print tree out in pre order (+ A B) */
    void printPreOrderHelper(Node<T> *root) {
        if (!root) return;
        cout << root->value << ' ';
        printPreOrderHelper(root->left);
        printPreOrderHelper(root->right);
    }

    /* Print tree out in level order */
    /* MA TODO: Implement */
    void printLevelOrderHelper(Node<T> *root) {
        if (!root) return;
        cout << endl;
        cout << "printLevelOrderHelper UNIMPLEMENTED AT THIS TIME -- REPLACE!" << endl;
        cout << " ** Required to use the STL queue class (that's a huge hint)!" << endl;
        cout << " ** Doing this with a loop will be easier than recursion." << endl;
    }

    /* Generate vector of tree values to return */
    /* MA TODO: Implement */
    vector<T> & returnLevelOrderHelper(Node<T> *root) {
        vector<T> * ret = new vector<T>{};
        if (!root) return( *ret );
        /*
        MA TODO:
        */
        cout << endl;
        cout << " returnLevelOrderHelper UNIMPLEMENTED AT THIS TIME -- REPLACE!" << endl;
        cout << " ** Required to use the STL queue class (that's a huge hint)!" << endl;
        cout << " ** Doing this with a loop will be easier than recursion." << endl;
        return( *ret );
    }

    /* Return number of nodes in tree */
    int nodesCountHelper(Node<T> *root) {
        if (!root) {
            return 0;
        } else {
            return 1 + nodesCountHelper(root->left) + nodesCountHelper(root->right);
        }
    }

    /* Return height of tree (root == NULL -> 0) */
    int heightHelper(Node<T> *root) {
        if (!root) {
            return 0;
        } else {
            return 1 + max(heightHelper(root->left), heightHelper(root->right));
        }
    }

    /* Print out longest path from root to a leaf */
    void printMaxPathHelper(Node<T> *root) {
        if (!root) return;
        cout<<root->value<<' ';
        if (heightHelper(root->left) > heightHelper(root->right)) {
            printMaxPathHelper(root->left);
        } else {
            printMaxPathHelper(root->right);
        }
    }

    /* Delete a given <T> value from tree */
    bool deleteValueHelper(Node<T>* parent, Node<T>* current, T value) {
        if (!current) return false;
        if (current->value == value) {
            if (current->left == NULL || current->right == NULL) {
                Node<T>* temp = current->left;
                if (current->right) temp = current->right;
                if (parent) {
                    if (parent->left == current) {
                        parent->left = temp;
                    } else {
                        parent->right = temp;
                    }
                } else {
                    this->_root = temp;
                }
            } else {
                Node<T>* validSubs = current->right;
                while (validSubs->left) {
                    validSubs = validSubs->left;
                }
                T temp = current->value;
                current->value = validSubs->value;
                validSubs->value = temp;
                return deleteValueHelper(current, current->right, temp);
            }
            delete current;
            return true;
        }
        return deleteValueHelper(current, current->left, value) ||
               deleteValueHelper(current, current->right, value);
    }

    bool containsHelper(Node<T> * root, T val) {
        if( root == NULL )
            return( false );
        else if( root->value == val )
            return( true );
        else if( root->value > val ) // Search left
            return( containsHelper(root->left, val) );
        else
            return( containsHelper(root->right, val) );
    }


    /********************************* PUBLIC API *****************************/
    public:

    BST( ) : _root( NULL ) { }               // Basic initialization constructor

    BST( initializer_list<T> vals ) : _root( NULL ) {
        for( auto val : vals )
            { this->add(val); }
    }


    /* Destructor - Needs to free *all* nodes in the tree */
    /* MA TODO: Implement */
    ~BST( ) {
        if( this->_debug ) {
            cout << " [d] Destructor called." << endl;
            cout << " TODO: Implement destructor to free *whole* tree. " << endl;
        }
    }

    /* Copy constructor */
    /* MA TODO: Implement */
    BST( const BST &other ) : _root( NULL ) {
        cout << " [d] Copy constructor called. " << endl;
        cout << " TODO: Implement copy constructor. " << endl;
    }

    /* Move constructor */
    /* MA TODO: Implement */
    BST ( BST && other ) : _root( NULL ) {
        cout << " [d] Move constructor called " << endl;
        cout << " TODO: Implement move constructor. " << endl;
    }

    /* Copy assignment operator */
    /* MA TODO: Implement */
    BST& operator=(BST & other) {
        cout << " [d] Copy assignment operator called. " << endl;
        cout << " TODO: Implement copy assignment operator. " << endl;
        return * this;
    }

    /* Move assignment operator */
    /* MA TODO: Implement */
    BST& operator=(BST && other) {
        cout << " [d] Move assignment operator called. " << endl;
        cout << " TODO: Implement move assignment operator. " << endl;
        return * this;
    }

    /* Public API */
    void makeEmpty( ) {
        if (this->_root) 
            this->makeEmptyHelper(this->_root);
    }

    void add(T val) {
        if (this->_root) {
            this->addHelper(this->_root, val);
        } else {
            this->_root = new Node<T>(val);
        }
    }

    bool empty() {
        return( this->_root == NULL );
    }

    void print() {
        printInOrderHelper(this->_root); 
    }

    void printInOrder() {
        printInOrderHelper(this->_root);
    }

    void printPostOrder() {
        printPostOrderHelper(this->_root);
    }

    void printPreOrder() {
        printPreOrderHelper(this->_root);
    }

    void printLevelOrder() {
        printLevelOrderHelper(this->_root);
    }

    vector<T> & returnLevelOrder() {
        return returnLevelOrderHelper(this->_root);
    }

    int size() {
        return nodesCount();
    }
    int nodesCount() {
        return nodesCountHelper(this->_root);
    }

    int height() {
        return heightHelper(this->_root);
    }

    void printMaxPath() {
        printMaxPathHelper(this->_root);
    }

    bool deleteValue(T value) {
        return this->deleteValueHelper(NULL, this->_root, value);
    }

    bool contains( T value ) {
        return containsHelper(this->_root, value);
    }

    void debug_on() {
        this->_debug = true;
    }

    void debug_off() {
        this->_debug = false;
    }

    /** NOTE: This is dangerous - I should be using a child class that exposes
            the root and only exists in the testing harness */
    Node<T> * getRoot() { return(this->_root); } // Gives out our root pointer for testing
};


#endif
