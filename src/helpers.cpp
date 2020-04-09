#include <algorithm>

#include "helpers.h"
#include "ipv4_address.h"

using vector = std::vector<IPv4Address>;

std::vector<std::string> split(const std::string &str, char d)
{
    // TODO Refactoring
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

vector filter(const vector &origin, const std::function<bool(const IPv4Address &)> &func)
{
    vector result (origin.size());
    // All glory to LISP!
    result.resize(
        std::distance(result.begin(),
        std::copy_if(
            origin.begin(),
            origin.end(),
            result.begin(),
            func)));
    return result;
}

vector filter(const vector &origin, int oct1)
{
    return filter(origin, [oct1](const auto &addr) { return (addr.oct1 == oct1); });
}

std::vector<IPv4Address> filter(IPv4Address &addr, int oct1, int oct2);
std::vector<IPv4Address> filter(IPv4Address &addr, int oct1, int oct2, int oct3);
std::vector<IPv4Address> filter_any(IPv4Address &addr, int val);
