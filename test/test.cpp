#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "ipv4_address.h"
#include "helpers.h"

using namespace std;
using namespace otus;

TEST(ipv4_address, default_ctr)
{
    ASSERT_TRUE(IPv4Address{ } == IPv4Address{ "0.0.0.0" });
}

TEST(ipv4_address, string_ctr)
{
    ASSERT_EQ(string(IPv4Address{ "127.0.0.1" }), "127.0.0.1");
    ASSERT_THROW(IPv4Address{ "127.0.0.1 " }, IPv4Address::InvalidAddressString);
    ASSERT_THROW(IPv4Address{ "327.0.0.1" }, IPv4Address::InvalidAddressString);
    ASSERT_THROW(IPv4Address{ "127.0.1" }, IPv4Address::InvalidAddressString);
    ASSERT_THROW(IPv4Address{ "127.zero.0.1" }, IPv4Address::InvalidAddressString);
    ASSERT_THROW(IPv4Address{ "0x27.0.0.1" }, IPv4Address::InvalidAddressString);
}

TEST(ipv4_address, comparison_operators)
{
    auto addr_local = IPv4Address{ "127.0.0.1" };
    auto addr_local_2 = IPv4Address{ "127.0.0.1" };
    auto addr_private = IPv4Address{ "192.168.0.99" };

    ASSERT_EQ(addr_local, addr_local_2);
    ASSERT_TRUE(addr_local >= addr_local_2);
    ASSERT_GT(addr_private, addr_local);
    ASSERT_LT(addr_local, addr_private);
}

TEST(helpers, split)
{
    ASSERT_EQ(
        vector<string>({ "Alef", "Bekar", "Zeta" }),
        split("Alef,Bekar,Zeta", ','));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
