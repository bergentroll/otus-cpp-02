#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#include "ipv4_address.h"
#include "helpers.h"

// TODO Add namespace.

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
    // TODO Specify.
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    std::sort(ip_pool.rbegin(), ip_pool.rend());
    // printIPv4Vector(ip_pool);

    // Efficient implementation without copying.
    //std::for_each(
    //    ip_pool.begin(),
    //    ip_pool.end(),
    //    [](const auto &addr) { if (addr.oct1 == 1) std::cout << addr << std::endl; });

    //decltype(ip_pool) result (ip_pool.size());
    // All glory to LISP!
    //result.resize(
    //    std::distance(result.begin(),
    //    std::copy_if(
    //        ip_pool.begin(),
    //        ip_pool.end(),
    //        result.begin(),
    //        [](const auto &addr) { return (addr.oct1 == 1); })));
    auto result = filter(ip_pool, 1);
    printIPv4Vector(result);

    // TODO filter by first and second bytes and output
    // ip = filter(46, 70)
    //std::for_each(
    //    ip_pool.begin(),
    //    ip_pool.end(),
    //    [](const auto &addr) { if (addr.oct1 == 46 && addr.oct2 == 70) std::cout << addr << std::endl; });

    // TODO filter by any byte and output
    // ip = filter_any(46)

    // 186.204.34.46
    // 186.46.222.194
    // 185.46.87.231
    // 185.46.86.132
    // 185.46.86.131
    // 185.46.86.131
    // 185.46.86.22
    // 185.46.85.204
    // 185.46.85.78
    // 68.46.218.208
    // 46.251.197.23
    // 46.223.254.56
    // 46.223.254.56
    // 46.182.19.219
    // 46.161.63.66
    // 46.161.61.51
    // 46.161.60.92
    // 46.161.60.35
    // 46.161.58.202
    // 46.161.56.241
    // 46.161.56.203
    // 46.161.56.174
    // 46.161.56.106
    // 46.161.56.106
    // 46.101.163.119
    // 46.101.127.145
    // 46.70.225.39
    // 46.70.147.26
    // 46.70.113.73
    // 46.70.29.76
    // 46.55.46.98
    // 46.49.43.85
    // 39.46.86.85
    // 5.189.203.46
    /*
    catch(const std::exception &e)
    {
    }
    */

    return 0;
}
