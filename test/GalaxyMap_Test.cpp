#include "gtest/gtest.h"
#include "GalaxyMap.h"

class GalaxyMap_Test : public testing::Test
{  protected:
   GalaxyMap map;
   GalaxyMap emptyMap;

   virtual void SetUp()
   {
      map.readMapFromFile("testMap.txt");
   }
   
   virtual void TearDown()
   {
      //delete map;
      //delete emptyMap;
   }
   
};

//Tests that missing file is handled properly
TEST_F(GalaxyMap_Test, ReadMapFromFile_NoFile)
{
   map.readMapFromFile("notAFile");
   try{
      EXPECT_TRUE(map.containsNode("test") == NULL);
   }catch(...){
      GTEST_FAIL();
   }
}

//Tests that all nodes are being created and can be found
TEST_F(GalaxyMap_Test, ContainsNode)
{
   EXPECT_TRUE(map.containsNode("Test Begin") != NULL);
   EXPECT_TRUE(map.containsNode("Test End") != NULL);
   EXPECT_TRUE(map.containsNode("Test Mid") != NULL);
}