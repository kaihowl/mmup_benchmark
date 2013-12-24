#include <iostream>
#include <unordered_map>
#include <chrono>
#include <cstdlib>
#include <vector>

#define NUM_VALS 100000

typedef size_t join_single_key_t;
typedef size_t pos_t;
typedef std::unordered_multimap<join_single_key_t, pos_t> hmap_t; 

void fillHashMaps(hmap_t &mmup1, hmap_t &mmup2) {
  std::srand(std::time(0));
  for (size_t i = 0; i < NUM_VALS; ++i) {
    mmup1.insert(hmap_t::value_type(std::rand(), std::rand()));
    mmup2.insert(hmap_t::value_type(std::rand(), std::rand()));
  }
}  

size_t runWithFreshMap() {
  
  // Initialize mmup
  hmap_t mmup, mmup2, fresh_mmup;

  fillHashMaps(mmup, mmup2);

  // start the timer
  auto t0 = std::chrono::high_resolution_clock::now();

  // merge hash maps in fresh hash map
  fresh_mmup.insert(mmup.begin(), mmup.end());
  fresh_mmup.insert(mmup2.begin(), mmup2.end());

  // end the timer
  auto t1 = std::chrono::high_resolution_clock::now();

  std::cout << "With fresh hash map: " << (t1 - t0).count() << " ticks" << std::endl;
  
  return (t1-t0).count();

}

size_t runWithReuseMap() {
  hmap_t mmup, mmup2;

  fillHashMaps(mmup, mmup2);

  // start timer 
  auto t0 = std::chrono::high_resolution_clock::now();

  // merge hash maps with inserting second in first
  mmup.insert(mmup2.begin(), mmup2.end());

  // end timer 2
  auto t1 = std::chrono::high_resolution_clock::now();

  std::cout << "With reusing one hash map: " << (t1 - t0).count() << " ticks" << std::endl;
  return (t1-t0).count();
}

size_t runWithReserveOnEmptyMap() {
  hmap_t mmup, mmup2, freshMap;

  fillHashMaps(mmup, mmup2);

  auto t0 = std::chrono::high_resolution_clock::now();

  freshMap.reserve(mmup.size() + mmup2.size());
  freshMap.insert(mmup.begin(), mmup.end());
  freshMap.insert(mmup2.begin(), mmup2.end());

  auto t1 = std::chrono::high_resolution_clock::now();

  return (t1-t0).count();
}



int main() {

  auto time1 = runWithFreshMap();
  auto time2 = runWithReuseMap();
  auto time3 = runWithReserveOnEmptyMap();
  std::cout << "Second method speed increase over first: " << 1 / (time2/ (float) time1) << std::endl;
  std::cout << "Third method speed increase over first: " << 1 / (time3/ (float) time1) << std::endl;

  return 0;
}
