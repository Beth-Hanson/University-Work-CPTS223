/*
 *  Test suite for Big Five Linked List project
 *
 *   All tests should begin with Starter* for their group name
 *
 */

#ifndef STARTER_TESTS_H
#define STARTER_TESTS_H

#include <gtest/gtest.h>    // Google's C++ testing harness
#include <gmock/gmock.h>    // Google's object mocking library
#include <vector>

using namespace testing;

//**************** Start of Node Tests ********************//
TEST(StarterNode, BasicInitializer)
{
    // Assemble
    int testValue = 13;
    Node<int> node = Node<int>(testValue);
    // Assert
    ASSERT_EQ(testValue, node.value);
    ASSERT_EQ(NULL, node.left);
    ASSERT_EQ(NULL, node.right);
}

TEST(StarterNode, InitializeChildren)
{
    // Assemble
    int testValue = 13;
    Node<int> * leftChild = new Node<int>(8);
    Node<int> * rightChild = new Node<int>(15);
    Node<int> node = Node<int>(testValue, leftChild, rightChild);
    // Assert
    ASSERT_EQ(testValue, node.value);
    ASSERT_EQ(leftChild, node.left);
    ASSERT_EQ(rightChild, node.right);
}

//****************** End of Node Tests ********************//


//****************** Start of BST Tests ********************//
TEST(StarterBST, IsEmpty)
{
    BST<int> tree{};                // Assemble
    ASSERT_EQ(true, tree.empty());  // Assert
}

TEST(StarterBST, AddContains)
{
    BST<int> tree{};                // Assemble
    tree.add(7);
    ASSERT_EQ(true, tree.contains(7));
}

TEST(StarterBST, MultipleAddContains)
{
    BST<int> tree{};                // Assemble
    vector<int> vals = {20, 10, 30, 5, 15, 25, 35, 2, 7, 12, 17, 23, 28, 32, 38, -1, -4, 0};
    for (auto val : vals)
        { tree.add(val); }
    for (auto val : vals)
    {
        ASSERT_EQ(true, tree.contains(val));
    }
}

TEST(StarterBST, NotContains)
{
    BST<int> tree{};        // Assemble
    vector<int> vals = {20, 10, 30, 5, 15, 25, 35, 2, 7, 12, 17, 23, 28, 32, 38, -1, -4, 0};
    for (auto val : vals)
        { tree.add(val); }  // Act
    for (auto val : vals)
    {
        ASSERT_EQ(false, tree.contains(val+100));   // Assert
    }
}

TEST(StarterBST, DupAddContains)
{
    BST<int> tree{};                // Assemble
    vector<int> vals = {20, 10, 30, 5, 15, 25, 35, 2, 7, 12, 17, 23, 28, 32, 38, -1, -4, 0, 20, 10, 30, 5, 15, 25, 35, 2, 7, 12, 17, 23, 28, 32, 38, -1, -4, 0};
    for (auto val : vals)
        { tree.add(val); }
    for (auto val : vals)
    {
        ASSERT_EQ(true, tree.contains(val));
    }
}

TEST(StarterBST, Size)
{
    BST<int> tree{};
    vector<int> vals = {20, 10, 30, 5, 15, 25, 35, 2, 7, 12, 17, 23, 28, 32, 38, -1, -4, 0};
    for (auto val : vals)
        { tree.add(val); }
    ASSERT_EQ(vals.size(), tree.size());
}

TEST(StarterBST, Height)
{
    BST<int> tree{};
    vector<int> vals = {20, 10, 5, 3, -1, 30, 35, 33};
    ASSERT_EQ(0, tree.height());    // Test empty tree
    tree.add( vals[0] );
    ASSERT_EQ(1, tree.height());    // Single node tree
    tree.add( vals[1] );
    ASSERT_EQ(2, tree.height());    // Two node tree
    tree.add( vals[2] );
    ASSERT_EQ(3, tree.height());    // Three node degraded (unbalanced) tree
    tree.add( vals[3] );
    ASSERT_EQ(4, tree.height());    // Four node degraded (unbalanced) tree
    tree.add( vals[4] );
    ASSERT_EQ(5, tree.height());    // Five node degraded (unbalanced) tree
    tree.add( vals[5] );
    tree.add( vals[6] );
    tree.add( vals[7] );
    ASSERT_EQ(5, tree.height());    // More balanced tree
}

TEST(StarterBST, MakeEmpty)
{
    BST<int> tree{};
    vector<int> vals = {20, 10, 30, 5, 15, 25, 35, 2, 7, 12, 17, 23, 28, 32, 38, -1, -4, 0};
    for (auto val : vals)
        { tree.add(val); }
    ASSERT_EQ(vals.size(), tree.size());    // Validating tree status
    ASSERT_EQ(false, tree.empty());         // Tree not empty
    ASSERT_EQ(6, tree.height());            // This tree from vals is height = 6
    ASSERT_NE(NULL, tree.getRoot());        // Should not be an empty root

    tree.makeEmpty();                       // Act - should empty the tree

    ASSERT_EQ(true, tree.empty());          // Should be true
    ASSERT_EQ(0, tree.size());              // Should be zero
    ASSERT_EQ(0, tree.height());            // Height is zero now
    ASSERT_EQ(NULL, tree.getRoot());        // Root should be NULL
        // Should also check to ensure all nodes were freed, not just forgotten
}

TEST(StarterBST, fuzzing)
{
    BST<int> tree{};        // Assemble
    vector<int> vals = {20, 10, 30, 5, 15, 25, 35, 2, 7, 12, 17, 23, 28, 32, 38, -1, -4, 0};
    for (auto val : vals)
        { tree.add(val); }  // Act
    for (auto val : vals)
    {
        ASSERT_EQ(false, tree.contains(val+100));   // Assert
    }
}


/*
TEST(StarterLinkedList, IsNotEmpty)
{
    // Assemble
    LinkedList<int> numbers{};
    numbers.addElement(50);
    // Assert
    ASSERT_EQ(false, numbers.isEmpty());
}

TEST(StarterLinkedList, Size)
{
    LinkedList<int> numbers{};          // Assemble
    ASSERT_EQ(0, numbers.getSize());    // Empty list size assert
    for( int i = 1; i < 1001; ++i ) {   // 1000 elements long
        numbers.addElement(i);          // Act
        ASSERT_EQ(i, numbers.getSize());// Assert
    }
}

TEST(StarterLinkedList, GetElementAt)
{
    // Assemble
    LinkedList<int> numbers{};
    vector<int> vals = {2, 5, 7, 3, 6};
    // Act
    for (auto val : vals)
        { numbers.addElement(val); }
    // Assert
    ASSERT_EQ(7, numbers.getElementAt(2));
}

TEST(StarterLinkedList, SetElementAt)
{
    // Assemble
    LinkedList<int> numbers{};
    int setVal = 10;
    int setLocation = 4;
    vector<int> vals = {2, 5, 7, 3, 6};
    for (auto val : vals)
        { numbers.addElement(val); }
    // Act
    numbers.setElementAt(setVal, setLocation);
    // Assert
    ASSERT_EQ(setVal, numbers.getElementAt(setLocation));
}

TEST(StarterLinkedList, AddElementAtFront)
{
    // Assemble
    LinkedList<int> numbers{};
    int setVal = 10;
    int setLocation = 0;
    vector<int> vals = {2, 5, 7, 3, 6};
    for (auto val : vals)
        { numbers.addElement(val); }
    // Act
    numbers.setElementAt(setVal,setLocation);
    // Assert
    ASSERT_EQ(setVal, numbers.getElementAt(setLocation));
}

TEST(StarterLinkedList, AddElementAtEnd)
{
    // Assemble
    LinkedList<int> numbers{};
    int setVal = 10;
    vector<int> vals = {2, 5, 7, 3, 6};
    int setLocation = (int)vals.size();      // Inserts at tail of LL
    for (auto val : vals)
        { numbers.addElement(val); }
    // Act
    numbers.addElementAt(setVal, setLocation);
    // Assert
    ASSERT_EQ(setVal, numbers.getElementAt(setLocation));
}

TEST(StarterLinkedList, AddElementAtMiddle)
{
    // Assemble
    LinkedList<int> numbers{};
    int setVal = 10;
    vector<int> vals = {2, 5, 7, 3, 6};
    int setLocation = (int)vals.size() / 2; // Inserts in middle of LL
    for (auto val : vals)                   // Add all vals to list as nodes
        { numbers.addElement(val); }
    // Act
    numbers.addElementAt(setVal, setLocation);
    // Assert
    ASSERT_EQ(setVal, numbers.getElementAt(setLocation));
}

TEST(StarterLinkedList, GetElementAtExceptionOut_Of_RangeUnderZero)
{
    LinkedList<int> numbers{};
    ASSERT_THROW(numbers.getElementAt(-1), out_of_range);
}
TEST(StarterLinkedList, GetElementAtExceptionOut_Of_RangeTooHigh)
{
    LinkedList<int> numbers{};
    ASSERT_THROW(numbers.getElementAt(2), out_of_range);
}

TEST(StarterLinkedList, RemoveElementAtExceptionOut_Of_RangeUnderZero)
{
    LinkedList<int> numbers{};
    ASSERT_THROW(numbers.removeElementAt(-1), out_of_range);
}

TEST(StarterLinkedList, RemoveElementAtExceptionOut_Of_RangeTooHigh)
{
    LinkedList<int> numbers{};
    vector<int> vals = {2, 5, 7, 3, 6};
    //int remLocation = (int)vals.size() / 2; // Inserts in middle of LL
    for (auto val : vals)                   // Add all vals to list as nodes
        { numbers.addElement(val); }
    ASSERT_THROW(numbers.removeElementAt(10), out_of_range);
}

TEST(StarterLinkedList, RemoveElementAtMiddle)
{
    LinkedList<int> numbers{};
    vector<int> vals = {2, 5, 7, 3, 6};
    int remLocation = (int)vals.size() / 2; // Inserts in middle of LL
    for (auto val : vals)                   // Add all vals to list as nodes
        { numbers.addElement(val); }
    numbers.removeElementAt(remLocation);   // Removing from middle of list
    ASSERT_EQ(4, numbers.getSize());
    ASSERT_EQ(3, numbers.getElementAt(remLocation));
    numbers.removeElementAt(0);         // Removing from head of list
    ASSERT_EQ(3, numbers.getSize());
    ASSERT_EQ(5, numbers.getElementAt(0));
    numbers.removeElementAt(2);         // Removing from current tail of list
    ASSERT_EQ(2, numbers.getSize());
    numbers.removeElementAt(0);         // Removing to make size 1
    ASSERT_EQ(1, numbers.getSize());
    numbers.removeElementAt(0);         // Removing to make size 0
    ASSERT_EQ(0, numbers.getSize());
}

TEST(StarterLinkedList, getElementAt)
{
    // Assemble
    LinkedList<int> numbers{};
    int getVal = 7; 
    vector<int> vals = {2, 5, 7, 3, 6};
    int getLocation = 2;                // Gets value of node at index 2 (val=7)
    for (auto val : vals)               // Add all vals to list as nodes
        { numbers.addElement(val); }
    // Act
    int gotVal = numbers.getElementAt(getLocation);
    // Assert
    ASSERT_EQ(getVal, gotVal);
}

TEST(StarterLinkedList, BasicInOrderStorage)
{
    // Assemble
    LinkedList<int> numbers{};
    vector<int> vals = {2, 5, 7, 3, 6};
    // Act
    for (auto val : vals)
        { numbers.addElement(val); }
    vector<int> result;
    for (int i = 0; i < numbers.getSize(); i++)
        { result.push_back(numbers.getElementAt(i)); }
    // Assert
    ASSERT_THAT(result, ElementsAreArray(vals));
}
*/
//****************** End of LinkedList tests **************************//

#endif
