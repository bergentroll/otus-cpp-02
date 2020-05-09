// This is an ad-hoc comparison of two library versions.

#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <sstream>

#include <range/v3/action/sort.hpp>
#include <range/v3/view/reverse.hpp>

#include "ipv4_address.h"
#include "helpers.h"

using namespace std;
using namespace std::chrono;
using namespace otus;

constexpr size_t POOL_SIZE { static_cast<size_t>(1e6) };

class StubPrint
{
    public:
    template <typename T>
    void operator()(T &&vec)
    {
        for (auto const &addr: vec)
        {
            ss << addr << endl;
        }
    }

    string obtain()
    {
        auto res { ss.str() };
        ss.str("");
        return res;
    }

    private:
    stringstream ss { };
};

StubPrint stub_print { };

int make_random(int max) {
    static default_random_engine engine{random_device()()};
    uniform_int_distribution<> dist(0, max);
    return(dist(engine));
}

vector<IPv4Address> create_pool(size_t size)
{
    vector<IPv4Address> result(size);

    for(auto &addr: result)
    {
        addr = IPv4Address(
            to_string(make_random(255)) + '.' +
            to_string(make_random(255)) + '.' +
            to_string(make_random(255)) + '.' +
            to_string(make_random(255)));
    }

    return result;
}

long run_legacy(vector<IPv4Address> ip_pool)
{
    auto start_time { high_resolution_clock::now() };

    sort(ip_pool.rbegin(), ip_pool.rend());
    stub_print(ip_pool);

    auto result = filter(ip_pool, 1);
    stub_print(result);

    result = filter(ip_pool, 46, 70);
    stub_print(result);

    result = filter_any(ip_pool, 46);
    stub_print(result);

    auto finish_time { high_resolution_clock::now() };
    return duration_cast<milliseconds>(finish_time - start_time).count();
}

long run_range_v3(vector<IPv4Address> ip_pool)
{
    auto start_time { high_resolution_clock::now() };

    ip_pool |= ranges::actions::sort;
    auto ip_pool_view { ip_pool | ranges::views::reverse };
    stub_print(ip_pool_view);

    auto result1 = filter_rng(ip_pool_view, 1);
    stub_print(result1);

    auto result2 = filter_rng(ip_pool_view, 46, 70);
    stub_print(result2);

    auto result3 = filter_any_rng(ip_pool_view, 46);
    stub_print(result3);

    auto finish_time { high_resolution_clock::now() };
    return duration_cast<milliseconds>(finish_time - start_time).count();
}

int main(int argc, char const **argv)
{
    vector<IPv4Address> ip_pool { create_pool(POOL_SIZE) };

    cout
        << "Legacy processing takes:   "
        << run_legacy(ip_pool)
        << " milliseconds." << endl;
    auto output_legacy { stub_print.obtain() };

    cout
        << "Range-v3 processing takes: "
        << run_range_v3(ip_pool)
        << " milliseconds." << endl;
    auto output_range_v3 { stub_print.obtain() };

    assert(output_legacy == output_range_v3);

    return EXIT_SUCCESS;
}
