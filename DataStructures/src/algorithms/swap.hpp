#pragma once 

#include <utility> 


namespace algorithms
{
  template <typename T> 
  void swap (T& a, T& b)
  {
    T c(std::move(a)); a=std::move(b); b=std::move(c);
  }

  template <typename T, size_t N> 
  void swap (T (&a)[N], T (&b)[N])
  {
    for (size_t i = 0; i<N; ++i) swap (a[i],b[i]);
  }
}