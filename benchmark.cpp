#include <iostream>
#include <unordered_map>
#include <chrono>
#include <cstdlib>
#include <vector>

typedef size_t join_single_key_t;
typedef size_t pos_t;
typedef std::unordered_multimap<join_single_key_t, pos_t> hmap_t; 

int main() {
  // Initialize mmup
  hmap_t mmup;

  std::vector<size_t> randVals;

  //generate random values
  std::srand(std::time(0));
  for (size_t i = 0; i < 10000; ++i) {
    randVals.push_back(std::rand());
  }

  auto t0 = std::chrono::high_resolution_clock::now();

  // TODO create different random vals for the key and the value
  for (auto val : randVals) {
    mmup.insert(hmap_t::value_type(val, val));
  }

  auto t1 = std::chrono::high_resolution_clock::now();
  std::cout << "Ticks was: " << (t1 - t0).count() << std::endl;

  return 0;
}
