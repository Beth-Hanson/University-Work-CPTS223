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

TEST(LinkedListContent, BasicInOrderStorage)
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
