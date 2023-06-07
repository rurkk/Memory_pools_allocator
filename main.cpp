#include "Allocator/MyAllocator.h"
#include <list>
#include <set>
#include <iostream>

int main() {
  int start;
  int finish;

  PoolsParameters::s_BLOCK_SIZES = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
  PoolsParameters::s_POOL_SIZE = 200000000;
  PoolsParameters::s_NUM_BLOCK_SIZES = 8;

  std::list<int, Allocator<int>> allocator_cntr;
  start = static_cast<int> (clock());
  for (int i = 0; i < 1e6; i++) {
    allocator_cntr.push_back(i);
//    if (i % 100000 == 0) {
//      std::cout << clock() - start << '\n';
//    }
  }
  finish = static_cast<int> (clock());
  std::cout << "\nmy allocator time: " << (finish - start) << '\n';

  start = static_cast<int> (clock());
  std::list<int> basic_cntr;
  for (int i = 0; i < 1e6; i++) {
    basic_cntr.push_back(i);
//    if (i % 100000 == 0) {
//      std::cout << clock() - start << '\n';
//    }
  }
  finish = static_cast<int> (clock());
  std::cout << "\nbasic allocator time: " << (finish - start) << '\n';
  std::cout << "-----------------------------\n\n";
  allocator_cntr.clear();
  basic_cntr.clear();



  std::vector<int, Allocator<int>> v;
  start = static_cast<int> (clock());
  for (int j = 0; j < 1e7; j ++) {
    v.push_back(j);
//    if (j % 1000000 == 0) {
//      std::cout << clock() - start << '\n';
//    }
  }
  finish = static_cast<int> (clock());
  std::cout << "\nmy allocator time: " << (finish - start)<< '\n';

  std::vector<int> v_b;
  start = static_cast<int> (clock());
  for (int j = 0; j < 1e7; j ++) {
    v_b.push_back(j);
//    if (j % 1000000 == 0) {
//      std::cout << clock() - start << '\n';
//    }
  }
  finish = static_cast<int> (clock());
  std::cout << "\nbasic allocator time: " << (finish - start) << '\n';
  std::cout << "-----------------------------\n\n";
  v.clear();
  v_b.clear();

  return 0;
}