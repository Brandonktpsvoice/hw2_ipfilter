#include "lib.h"
#include <gtest/gtest.h>

TEST (SquareRootTest, PositiveNos)
{ 
    EXPECT_EQ (hw::version(), PROJECT_VERSION_PATCH);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}