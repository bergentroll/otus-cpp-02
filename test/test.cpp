#include <gtest/gtest.h>

TEST(test_helloworld, test_output)
{
 // std::ostringstream oss { };
 // helloworld::HelloWorld()(oss);
 // ASSERT_TRUE(oss.good());
 // ASSERT_EQ(oss.str(), "Hello, World!\n");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
