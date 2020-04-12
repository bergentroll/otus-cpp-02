#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#include "ipv4_address.h"
#include "helpers.h"

using namespace otus;

void printIPv4Vector(const std::vector<IPv4Address> &vec)
{
    for (auto &addr: vec)
    {
        std::cout << addr << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    std::vector<IPv4Address> ip_pool;

    try
    {
        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            ip_pool.push_back(IPv4Address(v.at(0)));
        }
    }
    catch (IPv4Address::InvalidAddressString &e)
    {
        std::cerr << e.what() << std::endl;
    }

    std::sort(ip_pool.rbegin(), ip_pool.rend());
    printIPv4Vector(ip_pool);

    auto result = filter(ip_pool, 1);
    printIPv4Vector(result);

    // Efficient implementation without copying.
    /*
    std::for_each(
        ip_pool.begin(),
        ip_pool.end(),
        [](const auto &addr)
        {
            if (addr.template getOctet<1>() == 1)
                std::cout << addr << std::endl;
        });
    */

    result = filter(ip_pool, 46, 70);
    printIPv4Vector(result);

    result = filter_any(ip_pool, 46);
    printIPv4Vector(result);

    return 0;
}
