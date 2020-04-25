#ifndef HELPERS
#define HELPERS

#include <vector>
#include <string>
#include <functional>

#include <range/v3/view/any_view.hpp>

namespace otus
{
    using byte = uint8_t;

    class IPv4Address;

    std::vector<std::string> split(const std::string &str, char delim);

    std::vector<IPv4Address> filter(
        const std::vector<IPv4Address> &,
        const std::function<bool(const IPv4Address &)> &func);

    std::vector<IPv4Address> filter(
        const std::vector<IPv4Address> &, byte oct1);

    std::vector<IPv4Address> filter(
        const std::vector<IPv4Address> &, byte oct1, byte oct2);

    std::vector<IPv4Address> filter(
        const std::vector<IPv4Address> &, byte oct1, byte oct2, byte oct3);

    std::vector<IPv4Address> filter_any(
        const std::vector<IPv4Address> &, byte val);

    ranges::any_view<IPv4Address> filter_rng(
        const std::vector<IPv4Address> &, byte oct1);

    ranges::any_view<IPv4Address> filter_rng(
        const std::vector<IPv4Address> &, byte oct1, byte oct2);

    ranges::any_view<IPv4Address> filter_rng(
        const std::vector<IPv4Address> &, byte oct1, byte oct2, byte oct3);

    ranges::any_view<IPv4Address> filter_any_rng(
        const std::vector<IPv4Address> &, byte val);
}

#endif
