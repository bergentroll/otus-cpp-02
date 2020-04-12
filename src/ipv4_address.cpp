#include "ipv4_address.h"
#include "helpers.h"

using namespace otus;

IPv4Address::IPv4Address(const std::string &address)
{
    // TODO test-case str == '2x56'
    auto splited = split(address, '.');

    for (unsigned int i = 0; i < data.size(); i++)
        data[i] = validateByte(std::stoi(splited.at(i)));
}

IPv4Address::operator std::string() const
{
    std::string result { };

    for (unsigned int i = 0; i < data.size() - 1; i++)
        result += std::to_string(data[i]) + '.';

    result += std::to_string(data.back());

    return result;
}

bool IPv4Address::operator <(const IPv4Address &other) const
{
    for (unsigned int i = 0; i < data.size(); i++)
    {
        if (data[i] < other.data[i]) return true;
        else if (data[i] > other.data[i]) return false;
    }

    return false;
}

bool IPv4Address::operator ==(const IPv4Address &other) const
{
    for (unsigned int i = 0; i < data.size(); i++)
        if (data[i] != other.data[i]) return false;

    return true;
}

byte IPv4Address::validateByte(int i) {
    if (i < 0 || i > 255)
    {
        throw(InvalidOctet(i));
    }
    return i;
}

namespace otus
{
    std::ostream &operator <<(std::ostream &stream, const IPv4Address &addr)
    {
        stream << std::string(addr);
        return stream;
    }
}
