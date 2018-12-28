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

//**************** Start of ListNode Tests ********************//
TEST(ListNode, GetValue)
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
    //nodeB.setValue(20);
    //nodeB = nodeA;
    // Assert
    ASSERT_EQ(nodeA.getValue(), nodeB.getValue());
}
//****************** End of ListNode Tests ********************//

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
    int setLocation = vals.size() - 1;  // Inserts at tail of LL
    for (auto val : vals)
        { numbers.addElement(val); }
    // Act
    numbers.setElementAt(setVal,setLocation);
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
    for (auto val : vals)
        { numbers.addElement(val); }
    // Act
    numbers.setElementAt(setVal,setLocation);
    // Assert
    ASSERT_EQ(setVal, numbers.getElementAt(setLocation));
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
