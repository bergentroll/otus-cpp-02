#ifndef HELPERS
#define HELPERS

#include <vector>
#include <string>
#include <functional>

#include <range/v3/view/any_view.hpp>
#include <range/v3/view/filter.hpp>

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

    template <typename T>
    auto filter_rng(const T &origin, byte oct1)
    {
      return origin | ranges::views::filter(
          [oct1](const auto &addr) { return (addr.getOctet(1) == oct1); });
    }

    template <typename T>
    auto filter_rng(
        const T &origin, byte oct1, byte oct2)
    {
        return origin | ranges::views::filter(
          [oct1, oct2](const auto &addr)
          {
              return (
                addr.getOctet(1) == oct1 &&
                addr.getOctet(2) == oct2);
          });
    }

    template <typename T>
    auto filter_rng(
        const T &origin, byte oct1, byte oct2, byte oct3)
    {
        return origin | ranges::views::filter(
            [oct1, oct2, oct3](const auto &addr)
            {
                return (
                    addr.getOctet(1) == oct1 &&
                    addr.getOctet(2) == oct2 &&
                    addr.template getOctet<3>() == oct3);
            });
    }

    template <typename T>
    auto filter_any_rng(const T &origin, byte val)
    {
        return origin | ranges::views::filter(
            [val](const auto &addr)
            {
                for (const auto oct: addr) if (oct == val) return true;
                return false;
            });
    }
}

#endif
