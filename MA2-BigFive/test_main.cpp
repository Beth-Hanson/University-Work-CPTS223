/*
 *
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

#include "LinkedList.h"
#include "ListNode.h"

#include <sstream>      // stringstream stream buffer

using namespace testing;



    // Returns pointer to front of list - THIS IS DANGEROUS
    // Should be protected:, but I need it here for testing the destructor
    // To fix this, I should inherit from LinkedList and create this interface for testing
    /*
    ListNode<T> *getFront()
    {
        return _front;
    }
    */

//**************** Start of ListNode Tests ********************//
TEST(ListNode, SetAndGetValue)
{
    // Assemble
    ListNode<int> node;
    int testValue = 13;
    node.setValue(testValue);
    // Assert
    ASSERT_EQ(testValue, node.getValue());
}

TEST(ListNode, CopyConstructor)
{
    // Assemble
    ListNode<int> nodeA;
    int testValue = 13;
    nodeA.setValue(testValue);
    // Act
    ListNode<int> nodeB(nodeA);    // Invokes copy constructor
    // Assert
    ASSERT_EQ(nodeA.getValue(), nodeB.getValue());
}

TEST(ListNode, CopyOperator)
{
    // Assemble
    ListNode<int> nodeA;
    int testValue = 13;
    nodeA.setValue(testValue);
    ListNode<int> nodeB;
    // Act
    nodeB = nodeA;    // Invokes copy operator
    // Assert
    ASSERT_EQ(nodeA.getValue(), nodeB.getValue());
}
//****************** End of ListNode Tests ********************//


//****************** Start of LinkedList Tests ********************//
TEST(LinkedListBasics, IsEmpty)
{
    // Assemble
    LinkedList<int> numbers{};
    // Assert
    ASSERT_EQ(true, numbers.isEmpty());
}

TEST(LinkedListBasics, IsNotEmpty)
{
    // Assemble
    LinkedList<int> numbers{};
    numbers.addElement(50);
    // Assert
    ASSERT_EQ(false, numbers.isEmpty());
}

TEST(LinkedListBasics, GetElementAt)
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

TEST(LinkedListBasics, SetElementAt)
{
    // Assemble
    LinkedList<int> numbers{};
    int setVal = 10;
    int setLocation = 4;
    vector<int> vals = {2, 5, 7, 3, 6};
    for (auto val : vals)
        { numbers.addElement(val); }
    // Act
    numbers.setElementAt(setVal,setLocation);
    // Assert
    ASSERT_EQ(setVal, numbers.getElementAt(setLocation));
}

TEST(LinkedListBasics, AddElementAtFront)
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

TEST(LinkedListBasics, AddElementAtEnd)
{
    // Assemble
    LinkedList<int> numbers{};
    int setVal = 10;
    vector<int> vals = {2, 5, 7, 3, 6};
    int setLocation = vals.size();      // Inserts at tail of LL
    for (auto val : vals)
        { numbers.addElement(val); }
    // Act
    numbers.addElementAt(setVal, setLocation);
    // Assert
    ASSERT_EQ(setVal, numbers.getElementAt(setLocation));
}

TEST(LinkedListBasics, AddElementAtMiddle)
{
    // Assemble
    LinkedList<int> numbers{};
    int setVal = 10;
    vector<int> vals = {2, 5, 7, 3, 6};
    int setLocation = vals.size() / 2;  // Inserts in middle of LL
    for (auto val : vals)               // Add all vals to list as nodes
        { numbers.addElement(val); }
    // Act
    numbers.addElementAt(setVal, setLocation);
    // Assert
    ASSERT_EQ(setVal, numbers.getElementAt(setLocation));
}

TEST(LinkedListBasics, GetElementAtExceptionOut_Of_RangeUnderZero)
{
    LinkedList<int> numbers{};
    ASSERT_THROW(numbers.getElementAt(-1), out_of_range);
}
TEST(LinkedListBasics, GetElementAtExceptionOut_Of_RangeTooHigh)
{
    LinkedList<int> numbers{};
    ASSERT_THROW(numbers.getElementAt(2), out_of_range);
}

TEST(LinkedListBasics, RemoveElementAtExceptionOut_Of_RangeUnderZero)
{
    LinkedList<int> numbers{};
    ASSERT_THROW(numbers.removeElementAt(-1), out_of_range);
}

TEST(LinkedListBasics, RemoveElementAtExceptionOut_Of_RangeTooHigh)
{
    LinkedList<int> numbers{};
    vector<int> vals = {2, 5, 7, 3, 6};
    int remLocation = vals.size() / 2;  // Inserts in middle of LL
    for (auto val : vals)               // Add all vals to list as nodes
        { numbers.addElement(val); }
    ASSERT_THROW(numbers.removeElementAt(10), out_of_range);
}

TEST(LinkedListBasics, RemoveElementAtMiddle)
{
    LinkedList<int> numbers{};
    vector<int> vals = {2, 5, 7, 3, 6};
    int remLocation = vals.size() / 2;  // Inserts in middle of LL
    for (auto val : vals)               // Add all vals to list as nodes
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

TEST(LinkedListBasics, getElementAt)
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

TEST(LinkedListBasics, BasicInOrderStorage)
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
//****************** End of LinkedList tests **************************//


//********* Start of Microassignment LinkedList tests *****************//
TEST(LinkedListBigFive, CopyConstructor)
{
    // Assemble
    LinkedList<int> firstList{};
    vector<int> srcVals = {1, 2, 3, 4, 5};
    for (auto val : srcVals) {
        firstList.addElement(val);
    }
    // Act
    LinkedList<int> listCopy{ firstList };      // Executes Copy Constructor
    vector<int> copyVals = {};
    for (int i = 0; i < listCopy.getSize(); i++)
    {
        copyVals.push_back(listCopy.getElementAt(i));
    }
    // Assert
    ASSERT_THAT(copyVals, ElementsAreArray(srcVals));
}




//********* End of Microassignment LinkedList tests *******************//



// Main only sets up the Google gtest system and runs the tests
// Any Functions in this file called "TEST" will be run
int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

    // Notes
    //ASSERT_EQ(true, true);
    //ASSERT_THAT(result, ElementsAre(2,5,7,3,6));
    //ASSERT_THAT(result, ElementsAreArray(vals));
    // ASSERT_THROW(statement, exception_type);
    // ASSERT_ANY_THROW(statement);
    // ASSERT_NO_THROW(statement);
