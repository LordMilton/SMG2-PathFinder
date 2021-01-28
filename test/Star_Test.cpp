#include "gtest/gtest.h"
#include "Star.h"

class Star_Test : public testing::Test
{  protected:
   Star star = Star("test");

   virtual void SetUp()
   {
   }
   
   virtual void TearDown()
   {
   }
   
};

TEST_F(Star_Test, GetTime_Unset)
{
   EXPECT_EQ(star.getTime(), 3600000);
}

TEST_F(Star_Test, GetTime_Set)
{
   star.setTime(60000);
   EXPECT_EQ(star.getTime(), 60000);
}

TEST_F(Star_Test, GetTimeWithMedal_Unset)
{
   EXPECT_EQ(star.getTimeWithMedal(), 3600000);
}

TEST_F(Star_Test, GetTimeWithMedal_Set)
{
   star.setTimeWithMedal(60000);
   EXPECT_EQ(star.getTimeWithMedal(), 60000);
}

TEST_F(Star_Test, GetName)
{
   EXPECT_EQ(star.getName(), "test");
}