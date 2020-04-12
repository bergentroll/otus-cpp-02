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
        IPv4Address() { };

        IPv4Address(const std::string &address);

        operator std::string() const;

        bool operator <(const IPv4Address &other) const;

        bool operator >(const IPv4Address &other) const { return other < *this; }

        bool operator ==(const IPv4Address &other) const;

        bool operator !=(const IPv4Address &other) const { return !(*this == other); }

        bool operator >=(const IPv4Address &other) const { return (*this > other || *this == other); }

        bool operator <=(const IPv4Address &other) const { return (*this < other || *this == other); }

        /// Get address octet by number. First octet is 1, last is 4.
        template <int I>
        byte getOctet() const
        {
            static_assert(I >= 1 && I <= 4, "Octet index is out of range.");
            return getOctet(I);
        }

        /** Get address octet by number (runtime version). First octet is 1, last is 4.
         *  Exception
         */
        byte getOctet(int index) const { return data.at(index - 1); }

        std::vector<byte>::const_iterator begin() const { return data.begin(); }

        std::vector<byte>::const_iterator end() const { return data.end(); }

        class InvalidOctet: public std::runtime_error
        {
        public:
            int value;

            explicit InvalidOctet(int octet):
            std::runtime_error("Invalid octet " + std::to_string(octet) + " given to IPv4Address.") { }
        };

    private:
        std::vector<byte> data = std::vector<byte>(4);

        static byte validateByte(int i);
    };

    std::ostream &operator <<(std::ostream &stream, const IPv4Address &addr);
}

#endif
