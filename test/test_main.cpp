#include <gtest.h>

int main(int arg1, char **arg2) 
{
    ::testing::InitGoogleTest(&arg1, arg2);
    return RUN_ALL_TESTS();
}
