#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string &str, char d)
{
    // TODO Refactoring
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

// TODO Access to members.
class IPv4Address
{
public:
    int oct1, oct2, oct3, oct4;

    IPv4Address(): oct1(0), oct2(0), oct3(0), oct4(0) { }

    IPv4Address(const std::string &address) {
        // TODO Validation;
        auto splited = split(address, '.');
        oct1 = std::stoi(splited.at(0));
        oct2 = std::stoi(splited.at(1));
        oct3 = std::stoi(splited.at(2));
        oct4 = std::stoi(splited.at(3));
    }

    // TODO assignment ctr.

    operator std::string() const
    {
        return
            std::to_string(oct1) + '.' +
            std::to_string(oct2) + '.' +
            std::to_string(oct3) + '.' +
            std::to_string(oct4);
    }

    bool operator <(const IPv4Address &other) const
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

    bool operator >(const IPv4Address &other) const
    {
        return other < *this;
    }

    bool operator ==(const IPv4Address &other) const
    {
        return (
            oct1 == other.oct1 &&
            oct2 == other.oct2 &&
            oct3 == other.oct3 &&
            oct4 == other.oct4);
    }

    bool operator !=(const IPv4Address &other) const
    {
        return !(*this == other);
    }

    bool operator >=(const IPv4Address &other) const
    {
        return (*this > other || *this == other);
    }

    bool operator <=(const IPv4Address &other) const
    {
        return (*this < other || *this == other);
    }
};

std::ostream &operator <<(std::ostream &stream, const IPv4Address &addr)
{
    stream << std::string(addr);
    return stream;
}

void printIPv4Vector(const std::vector<IPv4Address> &vec)
{
    for (auto &addr: vec)
    {
        std::cout << addr << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    //try
    {
        std::vector<IPv4Address> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            ip_pool.push_back(IPv4Address(v.at(0)));
        }

        std::sort(ip_pool.rbegin(), ip_pool.rend());
        // printIPv4Vector(ip_pool);

        //std::for_each(
        //    ip_pool.begin(),
        //    ip_pool.end(),
        //    [](const auto &addr) { if (addr.oct1 == 1) std::cout << addr << std::endl; });

        //decltype(ip_pool) result (ip_pool.size());
        //std::copy_if(
        //    ip_pool.begin(),
        //    ip_pool.end(),
        //    result.begin(),
        //    [](const auto &addr) { return (addr.oct1 == 1); });
        //printIPv4Vector(result);

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        std::for_each(
            ip_pool.begin(),
            ip_pool.end(),
            [](const auto &addr) { if (addr.oct1 == 46 && addr.oct2 == 70) std::cout << addr << std::endl; });

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    /*
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    */

    return 0;
}
