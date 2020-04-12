#ifndef IPV4_ADDRESS
#define IPV4_ADDRESS

#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace otus
{
    using byte = uint8_t;

    class IPv4Address
    {
    public:
        constexpr static int size { 4 };

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
            static_assert(I >= 1 && I <= size, "Octet index is out of range.");
            return getOctet(I);
        }

        /** Get address octet by number (runtime version). First octet is 1, last is 4.
         *  Exception
         */
        byte getOctet(int index) const { return data.at(index - 1); }

        std::vector<byte>::const_iterator begin() const { return data.begin(); }

        std::vector<byte>::const_iterator end() const { return data.end(); }

        class InvalidAddressString: public std::logic_error
        {
        public:
            explicit InvalidAddressString(const std::string &input):
            std::logic_error(
                "Invalid IPv4 address \"" + input +
                "\" has been given to IPv4Address.") { }
        };
private: std::vector<byte> data = std::vector<byte>(size);

        static bool isValidOctet(int i);
    };

    std::ostream &operator <<(std::ostream &stream, const IPv4Address &addr);
}

#endif
