#include <algorithm>
#include <sstream>

#include <range/v3/view/filter.hpp>

#include "helpers.h"
#include "ipv4_address.h"

using namespace otus;
using namespace ranges;
using ipv4_list = std::vector<IPv4Address>;

namespace otus
{
    std::vector<std::string> split(const std::string &str, char delim)
    {
        std::vector<std::string> result;
        std::string token;
        std::istringstream stream {str};
        while (std::getline(stream, token, delim)) result.push_back(token);
        return result;
    }

    ipv4_list filter(const ipv4_list &origin, const std::function<bool(const IPv4Address &)> &func)
    {
        ipv4_list result (origin.size());
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

    ipv4_list filter(const ipv4_list &origin, byte oct1)
    {
        return filter(
            origin,
            [oct1](const auto &addr)
            {
                return (addr.getOctet(1) == oct1);
            });
    }

    std::vector<IPv4Address> filter(const ipv4_list &origin, byte oct1, byte oct2)
    {
        return filter(
          origin,
          [oct1, oct2](const auto &addr)
          {
              return (
                addr.getOctet(1) == oct1 &&
                addr.getOctet(2) == oct2);
          });
    }

    ipv4_list filter(ipv4_list &origin, byte oct1, byte oct2, byte oct3)
    {
        return filter(
            origin,
            [oct1, oct2, oct3](const auto &addr)
            {
                return (
                    addr.getOctet(1) == oct1 &&
                    addr.getOctet(2) == oct2 &&
                    addr.template getOctet<3>() == oct3);
            });
    }

    ipv4_list filter_any(const ipv4_list &origin, byte val)
    {
        return filter(
            origin,
            [val](const auto &addr)
            {
                for (const auto oct: addr) if (oct == val) return true;
                return false;
            });
    }

    any_view<IPv4Address> filter_rng(const ipv4_list &origin, byte oct1)
    {
      return origin | views::filter(
          [oct1](const auto &addr) { return (addr.getOctet(1) == oct1); });
    }

    any_view<IPv4Address> filter_rng(const ipv4_list &origin, byte oct1, byte oct2)
    {
        return origin | views::filter(
          [oct1, oct2](const auto &addr)
          {
              return (
                addr.getOctet(1) == oct1 &&
                addr.getOctet(2) == oct2);
          });
    }

    any_view<IPv4Address> filter_rng(ipv4_list &origin, byte oct1, byte oct2, byte oct3)
    {
        return origin | views::filter(
            [oct1, oct2, oct3](const auto &addr)
            {
                return (
                    addr.getOctet(1) == oct1 &&
                    addr.getOctet(2) == oct2 &&
                    addr.template getOctet<3>() == oct3);
            });
    }

    any_view<IPv4Address> filter_any_rng(const ipv4_list &origin, byte val)
    {
        return origin | views::filter(
            [val](const auto &addr)
            {
                for (const auto oct: addr) if (oct == val) return true;
                return false;
            });
    }
}
