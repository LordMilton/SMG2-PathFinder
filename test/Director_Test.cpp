#include "gtest/gtest.h"
#include "Director.h"

class Director_Test : public testing::Test
{  protected:
   Director dir = Director("Test Worlds");

   virtual void SetUp()
   {
   }
   
   virtual void TearDown()
   {
   }
   
};

TEST_F(Director_Test, Constructor)
{
}