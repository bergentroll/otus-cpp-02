#ifndef IPV4_ADDRESS
#define IPV4_ADDRESS

#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace otus
{
    using byte = uint8_t;

    // TODO Access to members.
    class IPv4Address
    {
    public:
        byte oct1, oct2, oct3, oct4;

        IPv4Address(): oct1(0), oct2(0), oct3(0), oct4(0) { }

        IPv4Address(const std::string &address);

        operator std::string() const;

        bool operator <(const IPv4Address &other) const;

        bool operator >(const IPv4Address &other) const { return other < *this; }

        bool operator ==(const IPv4Address &other) const;

        bool operator !=(const IPv4Address &other) const { return !(*this == other); }

        bool operator >=(const IPv4Address &other) const { return (*this > other || *this == other); }

        bool operator <=(const IPv4Address &other) const { return (*this < other || *this == other); }

        class InvalidOctet: public std::runtime_error
        {
        public:
            int value;

            explicit InvalidOctet(int octet):
            std::runtime_error("Invalid octet " + std::to_string(octet) + " given to IPv4Address.") { }
        };

    private:
        static byte validateByte(int i);
    };

    std::ostream &operator <<(std::ostream &stream, const IPv4Address &addr);
}

#endif
