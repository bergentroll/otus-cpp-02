#ifndef IPV4_ADDRESS
#define IPV4_ADDRESS

#include <ostream>
#include <vector>
#include <string>

namespace otus
{
    // TODO Access to members.
    class IPv4Address
    {
    public:
        int oct1, oct2, oct3, oct4;

        IPv4Address(): oct1(0), oct2(0), oct3(0), oct4(0) { }

        IPv4Address(const std::string &address);

        operator std::string() const;

        bool operator <(const IPv4Address &other) const;

        bool operator >(const IPv4Address &other) const { return other < *this; }

        bool operator ==(const IPv4Address &other) const;

        bool operator !=(const IPv4Address &other) const { return !(*this == other); }

        bool operator >=(const IPv4Address &other) const { return (*this > other || *this == other); }

        bool operator <=(const IPv4Address &other) const { return (*this < other || *this == other); }
    };

    std::ostream &operator <<(std::ostream &stream, const IPv4Address &addr);
}

#endif
