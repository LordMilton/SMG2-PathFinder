#include "gtest/gtest.h"
#include "Galaxy.h"
#include <iostream>

class Galaxy_Test : public testing::Test
{  protected:
   Galaxy gal1 = Galaxy("gal1", true);
   Galaxy gal2 = Galaxy("gal2", false);
   Galaxy gal3 = Galaxy("gal3", false);
   Galaxy gal4 = Galaxy("gal4", false);

   virtual void SetUp()
   {
      Star* test1 = new Star("test1");
      gal1.addStar(test1);
      Star* test2 = new Star("test2");
      gal1.addStar(test2);
      Star* test3 = new Star("test3");
      gal1.addStar(test3);
      gal1.addSuccessor(&gal2);
      gal1.addSuccessor(&gal3);
      gal3.addSuccessor(&gal4);
   }
   
   virtual void TearDown()
   {
   }
   
};

//Tests Constructor
TEST_F(Galaxy_Test, Constructor)
{
   EXPECT_TRUE(gal1.isAvailable());
   EXPECT_FALSE(gal2.isAvailable());
}

//Tests getName
TEST_F(Galaxy_Test, GetName)
{
   EXPECT_EQ(gal1.getName(), "gal1");
   EXPECT_EQ(gal3.getName(), "gal3");
}

//Tests GetStar when Galaxy has no Stars
TEST_F(Galaxy_Test, GetStar_Name_Empty)
{
   EXPECT_TRUE(gal2.getStar("none") == NULL);
}

//Tests GetStar with a nonexistent Star name
TEST_F(Galaxy_Test, GetStar_Name_None)
{
   EXPECT_TRUE(gal1.getStar("none") == NULL);
}

//Tests GetStar with a valid Star name
TEST_F(Galaxy_Test, GetStar_Name_Valid)
{
   Star* test1 = gal1.getStar("test1");
   if(test1 == NULL)
      GTEST_FAIL();
   else
      EXPECT_EQ(test1->getName(), "test1");
      
   Star* test3 = gal1.getStar("test3");
   if(test3 == NULL)
      GTEST_FAIL();
   else
      EXPECT_EQ(test3->getName(), "test3");
}

//Tests GetStar when Galaxy has no Stars
TEST_F(Galaxy_Test, GetStar_Number_Empty)
{
   EXPECT_TRUE(gal2.getStar(1) == NULL);
   EXPECT_TRUE(gal2.getStar(0) == NULL);
}

//Tests GetStar with a nonexistent Star number
TEST_F(Galaxy_Test, GetStar_Number_None)
{
   EXPECT_TRUE(gal1.getStar(4) == NULL);
   EXPECT_TRUE(gal1.getStar(0) == NULL);
}

//Tests GetStar with a valid Star number
TEST_F(Galaxy_Test, GetStar_Number_Valid)
{
   Star* test1 = gal1.getStar(1);
   if(test1 == NULL)
      GTEST_FAIL();
   else
      EXPECT_EQ(test1->getName(), "test1");
      
   Star* test3 = gal1.getStar(3);
   if(test3 == NULL)
      GTEST_FAIL();
   else
      EXPECT_EQ(test3->getName(), "test3");
}

//Tests adding too many stars
TEST_F(Galaxy_Test, AddStar_TooMany)
{
   Star* test4 = new Star("test4");
   gal1.addStar(test4);
   Star* test5 = new Star("test5");
   gal1.addStar(test5);
   Star* test6 = new Star("test6");
   gal1.addStar(test6);
   Star* test7 = new Star("test7");
   EXPECT_FALSE(gal1.addStar(test7));
}

//Tests adding a star with a duplicate name
TEST_F(Galaxy_Test, AddStar_RepeatName)
{
   Star* test3_dup = new Star("test3");
   EXPECT_FALSE(gal1.addStar(test3_dup));
}

//Tests adding valid stars
TEST_F(Galaxy_Test, AddStar_Valid)
{
   Star* test4 = new Star("test4");
   EXPECT_TRUE(gal1.addStar(test4));
   Star* test5 = new Star("test5");
   EXPECT_TRUE(gal1.addStar(test5));
   Star* test6 = new Star("test6");
   EXPECT_TRUE(gal1.addStar(test6));
}

//Tests adding too many successors
TEST_F(Galaxy_Test, AddSuccessor_TooMany)
{
   Galaxy gal5 = Galaxy("gal5", false);
   Galaxy gal6 = Galaxy("gal6", false);
   Galaxy gal7 = Galaxy("gal7", false);
   gal1.addSuccessor(&gal5);
   gal1.addSuccessor(&gal6);
   EXPECT_FALSE(gal1.addSuccessor(&gal7));
}

//Tests adding valid successors
TEST_F(Galaxy_Test, AddSuccessor_Valid)
{
   Galaxy gal5 = Galaxy("gal5", false);
   Galaxy gal6 = Galaxy("gal6", false);
   EXPECT_TRUE(gal1.addSuccessor(&gal5));
   EXPECT_TRUE(gal1.addSuccessor(&gal6));
}

//Tests that oneCompleted makes proper galaxies available
TEST_F(Galaxy_Test, oneCompleted)
{
   gal1.oneCompleted();
   EXPECT_TRUE(gal2.isAvailable());
   EXPECT_TRUE(gal3.isAvailable());
   EXPECT_FALSE(gal4.isAvailable());
}