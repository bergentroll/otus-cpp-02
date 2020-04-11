#include <algorithm>
#include <sstream>

#include "helpers.h"
#include "ipv4_address.h"

using namespace otus;
using vector = std::vector<IPv4Address>;

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
        return filter(
            origin,
            [oct1](const auto &addr)
            {
                return (addr.oct1 == oct1);
            });
    }

    std::vector<IPv4Address> filter(const vector &origin, int oct1, int oct2)
    {
        return filter(
          origin,
          [oct1, oct2](const auto &addr)
          {
              return (addr.oct1 == oct1 && addr.oct2 == oct2);
          });
    }

    vector filter(vector &origin, int oct1, int oct2, int oct3)
    {
        return filter(
            origin,
            [oct1, oct2, oct3](const auto &addr)
            {
                return (addr.oct1 == oct1 && addr.oct2 == oct2 && addr.oct3 == oct3);
            });
    }

    vector filter_any(const vector &origin, int val)
    {
        return filter(
            origin,
            [val](const auto &addr)
            {
                return (
                    addr.oct1 == val ||
                    addr.oct2 == val ||
                    addr.oct3 == val ||
                    addr.oct4 == val);
            });
    }
}
