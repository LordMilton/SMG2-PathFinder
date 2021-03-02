#include "gtest/gtest.h"
#include "World.h"
#include "GalaxyMap.h"

class World_Test : public testing::Test
{  protected:
   GalaxyMap* map = NULL;
   World* world1 = NULL;
   World* world2 = NULL;

   virtual void SetUp()
   {
      map = new GalaxyMap(500);
      world1 = new World("Test World", map, true);
      world1->getMap()->readMapFromFile("../data/Test World");
      world2 = new World("Test World", map);
   }
   
   virtual void TearDown()
   {
      delete world1;
   }
   
};

//Tests getName after setting
TEST_F(World_Test, GetName)
{
   EXPECT_EQ(world1->getName(), "Test World");
}

//Tests that we get the right GalaxyMap
TEST_F(World_Test, GetMap)
{
   if(world1->getMap() == NULL)
   {
      GTEST_FAIL();
   }
   else
   {
      EXPECT_TRUE(world1->getMap()->containsValue("Test Begin") != NULL);
      EXPECT_TRUE(world1->getMap()->containsValue("Test Middle 2") != NULL);
      EXPECT_TRUE(world1->getMap()->containsValue("Test End") != NULL);
      EXPECT_TRUE(world1->getMap()->containsValue("Test") == NULL);
   }
}

//Tests that we can find the Galaxies in our GalaxyMap
TEST_F(World_Test, ContainsGalaxy_Exists)
{
   EXPECT_TRUE(world1->containsGalaxy("Test Begin") != NULL);
   EXPECT_TRUE(world1->containsGalaxy("Test Middle 2") != NULL);
   EXPECT_TRUE(world1->containsGalaxy("Test End") != NULL);   
}

//Tests that we don't find Galaxies not in our GalaxyMap
TEST_F(World_Test, ContainsGalaxy_NotExists)
{
   EXPECT_TRUE(world1->containsGalaxy("Test") == NULL);
}

//Tests that availability is being set by constructor
TEST_F(World_Test, IsAvailable_Constructor)
{
   EXPECT_TRUE(world1->isAvailable());
   EXPECT_FALSE(world2->isAvailable());
}

//Tests that MakeAvailable is changing availability appropriately
TEST_F(World_Test, MakeAvailable)
{
   world1->makeAvailable();
   world2->makeAvailable();
   EXPECT_TRUE(world1->isAvailable());
   EXPECT_TRUE(world2->isAvailable());
}