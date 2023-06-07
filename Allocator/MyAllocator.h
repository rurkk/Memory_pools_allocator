#include <vector>
#include "MyPools.h"

template<typename T>
class Allocator {
 public:
  using value_type = T;
  using pointer = T*;

  explicit Allocator() {}
  Allocator(const Allocator& other) = default;
  ~Allocator() = default;

  pointer allocate(size_t n) {
    return (pointer) pools_.allocate(n * sizeof(value_type));
  }

  void deallocate(pointer ptr, size_t n) {
    pools_.deallocate(ptr);
  }
 private:
  static Pools& pools_;
};

template<typename T>
Pools& Allocator<T>::pools_ = Pools::getInstance();

template<typename T, typename W>
bool operator==(const Allocator<T>& lhs, const Allocator<W>& rhs) {
  return lhs.pools_ == rhs.pools_;
}

template<typename T, typename W>
bool operator!=(const Allocator<T>& lhs, const Allocator<W>& rhs) {
  return !(lhs == rhs);
}