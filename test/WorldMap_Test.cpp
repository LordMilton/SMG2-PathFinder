#include "gtest/gtest.h"
#include "WorldMap.h"
#include "World.h"

#define MOVE_TIME 750

class WorldMap_Test : public testing::Test
{  protected:
   WorldMap map = WorldMap(MOVE_TIME);
   WorldMap emptyMap = WorldMap(MOVE_TIME);

   virtual void SetUp()
   {
      map.readMapFromFile("../data/Test Worlds");
   }
   
   virtual void TearDown()
   {
      //delete map;
      //delete emptyMap;
   }
   
};

//Tests that missing file is handled properly
TEST_F(WorldMap_Test, ReadMapFromFile_NoFile)
{
   map.readMapFromFile("notAFile");
   try{
      EXPECT_TRUE(map.containsValue("test") == NULL);
   }catch(...){
      GTEST_FAIL();
   }
}

//Tests that all nodes are being created and can be found
TEST_F(WorldMap_Test, ContainsValue_Valid)
{
   EXPECT_TRUE(map.containsValue("Test World 1") != NULL);
   EXPECT_TRUE(map.containsValue("Test World 2") != NULL);
   EXPECT_TRUE(map.containsValue("Test World 3") != NULL);
}

//Tests that nonexistent nodes aren't falsely found
TEST_F(WorldMap_Test, ContainsValue_Inaccessible)
{
   EXPECT_TRUE(map.containsValue("Test") == NULL);
}

//Tests pathTime on empty Map
TEST_F(WorldMap_Test, PathTime_Empty)
{
   EXPECT_EQ(emptyMap.pathTime("test1", "test2"), -1);
}

//Tests pathTime with one or both nodes inaccessible
TEST_F(WorldMap_Test, PathTime_Inaccessible)
{
   EXPECT_EQ(map.pathTime("none", "Test World 1"), -1);
   EXPECT_EQ(map.pathTime("Test World 1", "none"), -1);
   EXPECT_EQ(map.pathTime("none1", "none2"), -1);
}

//Tests pathTime with valid input
TEST_F(WorldMap_Test, PathTime_Valid)
{
   EXPECT_EQ(map.pathTime("Test World 1", "Test World 3"), MOVE_TIME*2);
   EXPECT_EQ(map.pathTime("Test World 3", "Test World 1"), MOVE_TIME*2);
}

//Helper function for toArray test(s)
bool arrayContains(World** arr, int arrLen, std::string worldName)
{
   for(int i = 0; i < arrLen; i++)
   {
      if(arr[i]->getName() == worldName)
         return true;
   }
   return false;
}

//Test toArray with a non-empty Map
TEST_F(WorldMap_Test, ToArray_NonEmpty)
{
   int size = -1;
   World** arr = (World**)(map.toArray(&size));
   
   EXPECT_EQ(size, 3);
   EXPECT_TRUE(arrayContains(arr, size, "Test World 1"));
   EXPECT_TRUE(arrayContains(arr, size, "Test World 2"));
   EXPECT_TRUE(arrayContains(arr, size, "Test World 3"));
}

//Test toArray with an empty Map
TEST_F(WorldMap_Test, ToArray_Empty)
{
   int size = -1;
   World** arr = (World**)(emptyMap.toArray(&size));
   
   EXPECT_EQ(size, 0);
}
