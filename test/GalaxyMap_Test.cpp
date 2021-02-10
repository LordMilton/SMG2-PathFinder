#include "gtest/gtest.h"
#include "GalaxyMap.h"

#define MOVE_TIME 500

class GalaxyMap_Test : public testing::Test
{  protected:
   GalaxyMap map = GalaxyMap(MOVE_TIME);
   GalaxyMap emptyMap = GalaxyMap(MOVE_TIME);

   virtual void SetUp()
   {
      map.readMapFromFile("../data/Test World");
   }
   
   virtual void TearDown()
   {
      //delete map;
      //delete emptyMap;
   }
   
};

//Tests getName after setting
TEST_F(GalaxyMap_Test, GetName_Set)
{
   EXPECT_EQ(map.getName(), "Test World");
}

//Test getName before setting
TEST_F(GalaxyMap_Test, GetName_Unset)
{
   EXPECT_EQ(emptyMap.getName(), "");
}

//Tests that missing file is handled properly
TEST_F(GalaxyMap_Test, ReadMapFromFile_NoFile)
{
   map.readMapFromFile("notAFile");
   try{
      EXPECT_TRUE(map.containsValue("test") == NULL);
   }catch(...){
      GTEST_FAIL();
   }
}

//Tests that all nodes are being created and can be found
TEST_F(GalaxyMap_Test, ContainsValue)
{
   EXPECT_TRUE(map.containsValue("Test Begin") != NULL);
   EXPECT_TRUE(map.containsValue("Test End") != NULL);
   EXPECT_TRUE(map.containsValue("Test Middle") != NULL);
}

//Tests pathTime on empty Map
TEST_F(GalaxyMap_Test, PathTime_Empty)
{
   EXPECT_EQ(emptyMap.pathTime("test1", "test2"), -1);
}

//TODO Tests pathTime with one or both nodes inaccessible
TEST_F(GalaxyMap_Test, PathTime_Inaccessible)
{
   EXPECT_EQ(map.pathTime("none", "Test Begin"), -1);
   EXPECT_EQ(map.pathTime("Test Begin", "none"), -1);
   EXPECT_EQ(map.pathTime("none1", "none2"), -1);
}

//TODO Tests pathTime with valid input
TEST_F(GalaxyMap_Test, PathTime_Valid)
{
   EXPECT_EQ(map.pathTime("Test Begin", "Test End"), MOVE_TIME*3);
   EXPECT_EQ(map.pathTime("Test End", "Test Begin"), MOVE_TIME*3);
}