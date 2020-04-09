#include "ipv4_address.h"
#include "helpers.h"

IPv4Address::IPv4Address(const std::string &address)
{
    // TODO Validation;
    auto splited = split(address, '.');
    oct1 = std::stoi(splited.at(0));
    oct2 = std::stoi(splited.at(1));
    oct3 = std::stoi(splited.at(2));
    oct4 = std::stoi(splited.at(3));
}

IPv4Address::operator std::string() const
{
    return
        std::to_string(oct1) + '.' +
        std::to_string(oct2) + '.' +
        std::to_string(oct3) + '.' +
        std::to_string(oct4);
}

bool IPv4Address::operator <(const IPv4Address &other) const
{
    if (oct1 < other.oct1) return true;
    else if (oct1 > other.oct1) return false;

    if (oct2 < other.oct2) return true;
    else if (oct2 > other.oct2) return false;

    if (oct3 < other.oct3) return true;
    else if (oct3 > other.oct3) return false;

    if (oct4 < other.oct4) return true;
    else if (oct4 > other.oct4) return false;

    return false;
}

bool IPv4Address::operator ==(const IPv4Address &other) const
{
    return (
        oct1 == other.oct1 &&
        oct2 == other.oct2 &&
        oct3 == other.oct3 &&
        oct4 == other.oct4);
}

std::ostream &operator <<(std::ostream &stream, const IPv4Address &addr)
{
    stream << std::string(addr);
    return stream;
}
