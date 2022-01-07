#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <execution>
#include <numeric>
#include <ranges>
#include <thrust/iterator/counting_iterator.h>

struct member{
    int block; // this is just a placeholder, you cant actually do "blocks" here

    int get_thread(){
      return threadIdx.x;
    }

    member(int i)
      : block(i) // probably will just be setting it to blockIdx.x
      {}
};

template <typename T>
struct wrapper{
  T fun_t;
  void operator()(int i) const {
      member wrapper_member {i};
      fun_t(wrapper_member);
  }

  wrapper(T fun_t_rhs)
    : fun_t(fun_t_rhs) 
    {}
};

int main() {

    auto fun = [](member mem){
      int t = mem.get_thread();
      printf("thread! %d, ", t);
    };// takes member type

    wrapper wrap{fun};

#define N 1024

    auto iota_it = std::ranges::iota_view{0, N};
    //auto counting_it = thrust::counting_iterator<int>();
    std::for_each(std::execution::par, iota_it.begin(), iota_it.end(), [wrap](int i){
            // will need to make a simple wrapper to create a "member" then launch the actual function
           wrap(i); // wrap will make a member then do work
    });

    std::cout << "-------------------\n";

    return 0;
}
