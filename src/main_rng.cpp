#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include <range/v3/action/sort.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/reverse.hpp>

#include "ipv4_address.h"
#include "helpers.h"

using namespace otus;

template <typename T>
void print(T &vec) {
    for (auto const &addr: vec)
        std::cout << addr << std::endl;
}

int main(int argc, char const *argv[])
{
    std::vector<IPv4Address> ip_pool;

    try
    {
        for (std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            ip_pool.push_back(IPv4Address(v.at(0)));
        }
    }
    catch (IPv4Address::InvalidAddressString &e)
    {
        std::cerr << e.what() << std::endl;
    }

    ip_pool |= ranges::actions::sort;
    auto ip_pool_view { ip_pool | ranges::views::reverse };
    print(ip_pool_view);

    auto view1 { filter_rng(ip_pool_view, 1) };
    print(view1);

    auto view2 { filter_rng(ip_pool_view, 46, 70) };
    print(view2);

    auto view3 { filter_any_rng(ip_pool_view, 46) };
    print(view3);

    return 0;
}
