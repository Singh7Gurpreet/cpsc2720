// #include "ItemClass.h"
// #include "ClawItem.h"
// #include "PipeItem.h"
// #include "OxygenItem.h"
// #include "FlamePartItem.h"
// #include "FlameFinishedItem.h"

// #include <iostream>
// #include <gtest/gtest.h> //Not too sure if this is needed to run the test

// class ItemTest : public ::testing::Test {

// //To link the items to this unit test
// protected:

//     ClawItem clawItem;
//     PipeItem pipeItem;
//     OxygenItem oxygenItem;
//     flamePartItem flamePart;
//     flameFinishedItem flameFinished;

// };

// TEST(ItemTest,CanSetName) {
//     Item item;
//     std::string expectedName = "Gurpeet Singh";
//     item.setName(expectedName);

//     //Verify that the name was correctly set
//     ASSERT_EQ(expectedName, person.getName());
// }

// TEST(ItemTest, CanGetName) {
//     Item item;
//     std::string expectedName = "Matthew MacMaster";
//     item.setName(expectedName); //First, set the name

//     //Verify that getName returns the correct name
//     ASSERT_EQ(expectedName, person.getName());
// }

// TEST(ItemTest, CanGetUses) {
//     Item item;
//     item.setUses(10);
//     EXPECT_EQ(10, item.getUses()); //Verify the getter retrieves the set
//     value
// }

// TEST(ItemTest, CanSetUses) {
//     Item item;
//     item.setUses (8);
//     EXPECT_EQ(8, item.getUses()) //Verify the setter updates the name
// }

// TEST(ItemTest, CanSetDescription) {
//     MyClass obj;
//     std::string expected = "Test Description";
//     obj.setDescription(expected);

//     //Use ASSERT_EQ to compare expected and actual values
//     ASSERT_EQ(expected, obj.getDescription());
// }

// TEST(ItemTest, CanGetDescription) {
//     MyClass obj;
//     std::string expected = "Initiial Description";
//     obj.setDescription(expected); //Set an intial description

//     //Use ASSERT_EQ to ensure getDescription returns the correct value
//     ASSERT_EQ(expected, obj.getDescription());
// }
