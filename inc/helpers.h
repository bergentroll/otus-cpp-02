#ifndef HELPERS
#define HELPERS

#include <vector>
#include <string>
#include <functional>

namespace otus
{
    class IPv4Address;

    std::vector<std::string> split(const std::string &str, char d);

    std::vector<IPv4Address> filter(
        const std::vector<IPv4Address> &, const std::function<bool(const IPv4Address &)> &func);
    std::vector<IPv4Address> filter(
        const std::vector<IPv4Address> &, int oct1);
    std::vector<IPv4Address> filter(
        const std::vector<IPv4Address> &, int oct1, int oct2);
    std::vector<IPv4Address> filter(
        const std::vector<IPv4Address> &, int oct1, int oct2, int oct3);
    std::vector<IPv4Address> filter_any(
        const std::vector<IPv4Address> &, int val);
}

#endif
