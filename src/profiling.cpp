#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>

#include <range/v3/action/sort.hpp>
#include <range/v3/view/reverse.hpp>

#include "ipv4_address.h"
#include "helpers.h"

using namespace std;
using namespace std::chrono;
using namespace otus;

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

long run_legacy()
{
  std::vector<IPv4Address> ip_pool { create_pool(1e6) };

  auto start_time { high_resolution_clock::now() };

  sort(ip_pool.rbegin(), ip_pool.rend());
  auto result = filter(ip_pool, 1);
  result = filter(ip_pool, 46, 70);
  result = filter_any(ip_pool, 46);

  auto finish_time { high_resolution_clock::now() };
  return duration_cast<milliseconds>(finish_time - start_time).count();
}

long run_range_v3()
{
  std::vector<IPv4Address> ip_pool { create_pool(1e6) };

  auto start_time { high_resolution_clock::now() };

  ip_pool |= ranges::actions::sort | ranges::views::reverse;
  auto result = filter_rng(ip_pool, 1);
  result = filter_rng(ip_pool, 46, 70);
  result = filter_any_rng(ip_pool, 46);

  auto finish_time { high_resolution_clock::now() };
  return duration_cast<milliseconds>(finish_time - start_time).count();
}

int main(int argc, char const **argv)
{
  cout << "Legacy processing takes:   " << run_legacy() << " milliseconds." << endl;
  cout << "Range-v3 processing takes: " << run_range_v3() << " milliseconds." << endl;
  return EXIT_SUCCESS;
}
