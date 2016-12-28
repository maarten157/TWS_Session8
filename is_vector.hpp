#ifndef tws_is_vector_hpp
#define tws_is_vector_hpp

#include <type_traits>
#include <iostream>

namespace tws {
  template <typename T>
  struct is_vector
  : std::false_type
  {} ;
}

#endif
