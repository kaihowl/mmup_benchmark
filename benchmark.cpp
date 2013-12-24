#include <iostream>
#include <unordered_map>
#include <chrono>
#include <cstdlib>
#include <vector>

#define NUM_VALS 1000

typedef size_t join_single_key_t;
typedef size_t pos_t;
typedef std::unordered_multimap<join_single_key_t, pos_t> hmap_t; 

int main() {
  // Initialize mmup
  hmap_t mmup, mmup2, fresh_mmup;

  //generate random values
  std::srand(std::time(0));
  for (size_t i = 0; i < NUM_VALS; ++i) {
    mmup.insert(hmap_t::value_type(std::rand(), std::rand()));
    mmup2.insert(hmap_t::value_type(std::rand(), std::rand()));
  }

  // start the timer
  auto t0 = std::chrono::high_resolution_clock::now();

  // merge hash maps in fresh hash map
  fresh_mmup.insert(mmup.begin(), mmup.end());
  fresh_mmup.insert(mmup2.begin(), mmup2.end());

  // end the timer
  auto t1 = std::chrono::high_resolution_clock::now();

  std::cout << "With fresh hash map: " << (t1 - t0).count() << " ticks" << std::endl;

  // start timer 2
  auto t2 = std::chrono::high_resolution_clock::now();

  // merge hash maps with inserting second in first
  mmup.insert(mmup2.begin(), mmup2.end());

  // end timer 2
  auto t3 = std::chrono::high_resolution_clock::now();

  std::cout << "With reusing one hash map: " << (t3 - t2).count() << " ticks" << std::endl;

  return 0;
}
