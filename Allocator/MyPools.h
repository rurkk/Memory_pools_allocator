#include <cstddef>
#include <cstdlib>
#include <iostream>

struct PoolsParameters {
  static std::vector<unsigned> s_BLOCK_SIZES;
  static unsigned s_POOL_SIZE;
  static size_t s_NUM_BLOCK_SIZES;
};

struct Pool {
  char* pool_;
  char* head_;
  Pool(unsigned block_size, unsigned num_blocks) : pool_(new char[block_size * num_blocks]), head_(pool_) {
    char* p = pool_;
    for (unsigned i = 0; i < num_blocks - 1; i++) {
      *((char**) p) = p + block_size;
      p += block_size;
    }
    *((char**) p) = nullptr;
  }

  void* allocate() {
    if (head_) {
      char* p = head_;
      head_ = *((char**) p);

      return p;
    }

    return nullptr;
  }

  void deallocate(void* p) {
    void* new_head;
    new_head = p;
    *((char**) p) = head_;
    head_ = (char*) new_head;
  }

  ~Pool() {
    delete[] pool_;
  }
};

struct Pools {
 private:
  Pool** pools_ = new Pool*[PoolsParameters::s_NUM_BLOCK_SIZES];

  Pools() {
    for (size_t i = 0; i < PoolsParameters::s_NUM_BLOCK_SIZES; i++) {
      unsigned block_size = PoolsParameters::s_BLOCK_SIZES[i];
      unsigned num_blocks = PoolsParameters::s_POOL_SIZE / block_size;
      pools_[i] = new Pool(block_size, num_blocks);
    }
  }
 public:

  static Pools& getInstance() {
    static Pools instance;

    return instance;
  }

  void* allocate(size_t size) {
    for (size_t i = 0; i < PoolsParameters::s_NUM_BLOCK_SIZES; i++) {
      if (size <= PoolsParameters::s_BLOCK_SIZES[i]) {
        void* p = pools_[i]->allocate();
        if (p != nullptr) {
          return p;
        }
      }
    }

    throw std::bad_alloc();
  }

  void deallocate(void* p) {
    for (auto& i : pools_) {
      if (i->pool_ <= p and p < i->pool_ + PoolsParameters::s_POOL_SIZE) {
        i->deallocate(p);

        return;
      }
    }
  }

  ~Pools() = default;
};
