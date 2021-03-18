#include "gtest/gtest.h"
#include "GalaxyMap.h"

#define MOVE_TIME 500

class GalaxyMap_Test : public testing::Test
{  protected:
   GalaxyMap map = GalaxyMap(MOVE_TIME);
   GalaxyMap emptyMap = GalaxyMap(MOVE_TIME);

   virtual void SetUp()
   {
      map.readMapFromFile("../data/test/Test World");
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

//Tests that stars are being read from file
TEST_F(GalaxyMap_Test, ReadMapFromFile_Stars)
{
   Galaxy* begin = ((Galaxy*)map.containsValue("Test Begin"));
   Galaxy* end = ((Galaxy*)map.containsValue("Test End"));
   
   EXPECT_TRUE(begin->getStar("Star 1") != NULL);
   EXPECT_TRUE(begin->getStar("Secret Star") != NULL);
   EXPECT_TRUE(begin->getStar("Comet Star") != NULL);
   EXPECT_TRUE(end->getStar("Star 1") != NULL);
   EXPECT_TRUE(end->getStar("Comet Star") != NULL);
   EXPECT_FALSE(end->getStar(3) != NULL);
}

//Tests that all nodes are being created and can be found
TEST_F(GalaxyMap_Test, ContainsValue)
{
   EXPECT_EQ(((Galaxy*)(map.containsValue("Test Begin")))->getName(), "Test Begin");
   EXPECT_EQ(((Galaxy*)(map.containsValue("Test End")))->getName(), "Test End");
   EXPECT_EQ(((Galaxy*)(map.containsValue("Test Middle")))->getName(), "Test Middle");
}

//Tests pathTime on empty Map
TEST_F(GalaxyMap_Test, PathTime_Empty)
{
   EXPECT_EQ(emptyMap.pathTime("test1", "test2"), -1);
}

//Tests pathTime with one or both nodes inaccessible
TEST_F(GalaxyMap_Test, PathTime_Inaccessible)
{
   EXPECT_EQ(map.pathTime("none", "Test Begin"), -1);
   EXPECT_EQ(map.pathTime("Test Begin", "none"), -1);
   EXPECT_EQ(map.pathTime("none1", "none2"), -1);
}

//Tests pathTime with valid input
TEST_F(GalaxyMap_Test, PathTime_Valid)
{
   EXPECT_EQ(map.pathTime("Test Begin", "Test End"), MOVE_TIME*3);
   EXPECT_EQ(map.pathTime("Test End", "Test Begin"), MOVE_TIME*3);
}

//Helper function for toArray test(s)
bool arrayContains(Galaxy** arr, int arrLen, std::string galName)
{
   for(int i = 0; i < arrLen; i++)
   {
      if(arr[i]->getName() == galName)
         return true;
   }
   return false;
}

//Test toArray with a non-empty Map
TEST_F(GalaxyMap_Test, ToArray_NonEmpty)
{
   int size = -1;
   Galaxy** arr = (Galaxy**)(map.toArray(&size));
   
   EXPECT_EQ(size, 5);
   EXPECT_TRUE(arrayContains(arr, size, "Test Begin"));
   EXPECT_TRUE(arrayContains(arr, size, "Test Middle 2"));
   EXPECT_TRUE(arrayContains(arr, size, "Test End"));
}

//Test toArray with an empty Map
TEST_F(GalaxyMap_Test, ToArray_Empty)
{
   int size = -1;
   Galaxy** arr = (Galaxy**)(emptyMap.toArray(&size));
   
   EXPECT_EQ(size, 0);
}