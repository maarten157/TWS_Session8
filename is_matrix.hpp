#ifndef tws_is_matrix_hpp
#define tws_is_matrix_hpp

#include <type_traits>
#include <iostream>

namespace tws {

  template <typename T>
  struct is_matrix
  : std::false_type
  {} ;
}

#endif
