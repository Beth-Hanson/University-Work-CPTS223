/*
 *  Test suite for BST Level Order project
 *
 *  All tests in this file should start with Base*
 * 
 */

#ifndef BASE_TESTS_H
#define BASE_TESTS_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

using namespace testing;

//********* Start of Microassignment LinkedList tests *****************//

//*** Start of Copy Constructor test ***
TEST(BaseBSTBigFive, CopyConstructor)
{
    // Assemble
    std::stringstream ssA;       // Buffer to store stream
    std::stringstream ssB;       // Buffer to store stream
    TestableBST<int> tree{};
    vector<int> srcVals = {20, 10, 30, 40, 35, -7, 5, 0};
    for (auto val : srcVals) 
        { tree.add(val); }
    // Act
    TestableBST<int> bstCopy{ tree };       // Executes Copy Constructor

    ASSERT_NE(tree.getRoot(), bstCopy.getRoot());   // Shallow copy test
    tree.printPostOrder(ssA);               // Grab contents
    bstCopy.printPostOrder(ssB);
    EXPECT_EQ(ssA.str(), ssB.str());        // Compare contents
    ASSERT_EQ(tree.size(), bstCopy.size());
    ASSERT_EQ(tree.height(), bstCopy.height());
}
//*** End of Copy Constructor tests ***

//*** Start of Move Constructor tests ***
TEST(BaseBSTBigFive, MoveConstructor)
{
    std::stringstream ssA;       // Buffer to store stream
    std::stringstream ssB;       // Buffer to store stream
    TestableBST<int> treeA{};
    vector<int> srcVals = {20, 10, 30, 40, 35, -7, 5, 0};
    string postOrderResult = "0 5 -7 10 35 40 30 20 ";
    for (auto val : srcVals) 
        { treeA.add(val); }
    Node<int>* srcRootA = treeA.getRoot();          // Save root for testing
    treeA.printPostOrder(ssA);                      // Grab contents of A

    // Act
    TestableBST<int> movedBST = std::move(treeA);   // Move constructor

    // Assert
    movedBST.printPostOrder(ssB);                   // Grab moved nodes in B
    ASSERT_EQ(srcRootA, movedBST.getRoot());        // Should be same Node
    EXPECT_EQ(ssA.str(), ssB.str());                // Compare contents
    EXPECT_EQ(postOrderResult, ssB.str());          // Compare to golden string
    ASSERT_EQ(srcVals.size(), movedBST.size());     // No elements lost
    ASSERT_EQ(nullptr, treeA.getRoot());            // Old BST destroyed
    ASSERT_EQ(0, treeA.size());                     // Old BST empty
}
//*** End of Move Constructor tests ***

//*** Start of Initializer List Constructor tests ***
TEST(BaseBSTBigFive, InitializerListConstructor)
{
    initializer_list<int> srcInitList = {20, 10, 30, 40, 35, -7, 5, 0};
    string postOrderResult = "0 5 -7 10 35 40 30 20 ";

    // Execute initializer_list constructor
    BST<int> newBST = BST<int>{ srcInitList };

    // Assert
    std::stringstream ssA;                          // Buffer to store stream
    newBST.printPostOrder(ssA);                     // Grab moved nodes in B
    EXPECT_EQ(postOrderResult, ssA.str());          // Compare to golden string
    ASSERT_EQ(srcInitList.size(), newBST.size());   // Size correct?
}
//*** End of Initializer List Constructor tests ***

//*** Start of Copy *assignment* operator tests ***
TEST(BaseLinkedListBigFive, CopyAssignmentOperator)
{
    std::stringstream ssA;
    std::stringstream ssB;
    string postOrderResult = "0 5 -7 10 35 40 30 20 ";
    vector<int> srcVals = {20, 10, 30, 40, 35, -7, 5, 0};

    TestableBST<int> firstBST{}; 
    for (auto val : srcVals)
        { firstBST.add(val); }              // Fill the first tree
    TestableBST<int> copiedBST;             // List to copy into via assignment

    // Act - Run copy assignment operator
    copiedBST = firstBST;                   // Copy assignment operator executed

    firstBST.printPostOrder(ssA);           // Grab contents from both trees
    copiedBST.printPostOrder(ssB);

    // Assert
    ASSERT_NE(firstBST.getRoot(), copiedBST.getRoot()); // Shallow copy (bad)?
    ASSERT_EQ(srcVals.size(), copiedBST.size());        // Test size correct
    EXPECT_EQ(ssA.str(), ssB.str());                    // Test contents
    EXPECT_EQ(postOrderResult, ssB.str());
}
//*** End of Copy *assignment* operator tests ***

//*** Start of Move *assignment* operator tests ***
TEST(BaseLinkedListBigFive, MoveAssignmentOperator)
{
    std::stringstream ssA;
    std::stringstream ssB;
    string postOrderResult = "0 5 -7 10 35 40 30 20 ";
    initializer_list<int> finalInitList = {20, 10, 30, 40, 35, -7, 5, 0};
    vector<int> finalVals = {20, 10, 30, 40, 35, -7, 5, 0};

    BST<int> movedBST{};                        // Assemble - create our list
    vector<int> srcVals = {1, 2, 3, 4, 5};
    for (auto val : srcVals)
        { movedBST.add(val); }                  // Fill list with init data

    // Act - execute move assignment operator
    // NOTE: This requires a working initializer_list constructor
    //  The rvalue on the right of the = operator is built 
    //  with an anonymous initializer_list object
    movedBST = BST<int>{finalInitList};         // Move assignment op

    movedBST.printPostOrder(ssA);               // Grab contents

    // Assert
    ASSERT_EQ(finalVals.size(), movedBST.size());           // Test size correct
    EXPECT_EQ(postOrderResult, ssA.str());
}
//*** End of Move *assignment* operator tests ***

//*** Start of Destructor (~) tests ***
int nonNullPtrCount( Node<int> * root ) {
    int count = 0;
    if( root == nullptr ) return count;
    if( root->left != nullptr )
    {
        count = count + 1 + nonNullPtrCount(root->left);
    }
    if( root->right != nullptr )
    {
        count = count + 1 + nonNullPtrCount(root->right);
    }   
    return(count);
}

TEST(BaseBSTBigFive, DestructorTests)
{
    TestableBST<int> * myBST = new TestableBST<int>();
    myBST->debug_on();                      // Turn on extra LinkedList output
    vector<int> srcVals = {20, 10, 30, 40, 35, -7, 5, 0};
    for (auto val : srcVals)
        { myBST->add(val); }

    // Gather white box data
    Node<int> * myRoot = myBST->getRoot();

    delete myBST;   // Act - explicitly call destructor on tree

    ASSERT_EQ(nullptr, myBST->getRoot());     // Is root now nullptr?
    ASSERT_EQ(0, nonNullPtrCount( myRoot ));  // Is old root really cleaned up?

}
//*** End of Destructor (~) tests ***

//*** Start of Level Order Tests ***
TEST(BaseLevelOrder, PrintLevelOrder)
{
    std::stringstream ss;       // Buffer to store stream
    BST<int> * bst = new BST<int>({4,2,1,3,6,5,7,9,8});
    cout << "\tShould produce:\t4 2 6 1 3 5 7 9 8 " << endl;
    cout << "\tLevelorder: \t";
    bst->printLevelOrder(ss);    // Results are stored in ss
    cout << ss.str();
    cout << endl;
    ASSERT_THAT(ss.str(), HasSubstr("4 2 6 1 3 5 7 9 8"));
}


//*** End of BST Level Order Tests ***

//********* End of Base Microassignment BST tests **************//


#endif
