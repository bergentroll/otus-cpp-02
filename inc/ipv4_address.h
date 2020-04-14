#ifndef IPV4_ADDRESS
#define IPV4_ADDRESS

#include <ostream>
#include <stdexcept>
#include <string>
#include <array>

namespace otus
{
    using byte = uint8_t;

    class IPv4Address
    {
    public:
        constexpr static int size { 4 };

        IPv4Address(): data() { };

        /** @brief Create object with text representation.
         *  @param address Dot separated octets expected.
         *  @throw InvalidAddressString On illformed input (octets amount, octets values.
         */
        IPv4Address(const std::string &address);

        operator std::string() const;

        bool operator <(const IPv4Address &other) const;

        bool operator >(const IPv4Address &other) const { return other < *this; }

        bool operator ==(const IPv4Address &other) const;

        bool operator !=(const IPv4Address &other) const { return !(*this == other); }

        bool operator >=(const IPv4Address &other) const { return (*this > other || *this == other); }

        bool operator <=(const IPv4Address &other) const { return (*this < other || *this == other); }

        /// Get address octet by number (compile time check).
        template <int I>
        byte getOctet() const
        {
            static_assert(I >= 1 && I <= size, "Octet index is out of range.");
            return getOctet(I);
        }

        /** @brief Get address octet by number (runtime version).
         *  @param index Number of octet starting from 1.
         *  @throw std::out_of_range On invalid octet index.
         */
        byte getOctet(int index) const { return data.at(index - 1); }

        std::array<byte, size>::const_iterator begin() const { return data.begin(); }

        std::array<byte, size>::const_iterator end() const { return data.end(); }

        class InvalidAddressString: public std::logic_error
        {
        public:
            explicit InvalidAddressString(const std::string &input):
            std::logic_error(
                "Invalid IPv4 address \"" + input +
                "\" has been given to IPv4Address.") { }
        };

    private:
        std::array<byte, size> data;

        static bool isValidOctet(int i);
    };

    std::ostream &operator <<(std::ostream &stream, const IPv4Address &addr);
}

#endif
