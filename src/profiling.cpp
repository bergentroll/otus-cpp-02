#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>

#include "ipv4_address.h"
#include "helpers.h"

using namespace std;
using namespace otus;
using namespace chrono;

int make_random(int max) {
  static default_random_engine engine{random_device()()};
  uniform_int_distribution<> dist(0, max);
  return(dist(engine));
}

vector<IPv4Address> create_pool(size_t size) {
  vector<IPv4Address> result(size);

  for(auto &addr: result) {
    addr = IPv4Address(
      to_string(make_random(255)) + '.' +
      to_string(make_random(255)) + '.' +
      to_string(make_random(255)) + '.' +
      to_string(make_random(255)));
  }

  return result;
}

int main(int argc, char const **argv) {
  std::vector<IPv4Address> ip_pool { create_pool(1e6) };

  auto start_time { high_resolution_clock::now() };

  sort(ip_pool.rbegin(), ip_pool.rend());
  auto result = filter(ip_pool, 1);
  result = filter(ip_pool, 46, 70);
  result = filter_any(ip_pool, 46);

  auto finish_time { high_resolution_clock::now() };
  cout
    << "Duration is: "
    << duration_cast<milliseconds>(finish_time - start_time).count()
    << " milliseconds." << endl;

  return EXIT_SUCCESS;
}
