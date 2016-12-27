#ifndef tws_is_matrix_hpp
#define tws_is_matrix_hpp

#include <type_traits>
#include <iostream>

namespace tws {

  template <typename T>
  struct is_matrix
  : std::false_type
  {} ;

/*  template <typename T>
  typename std::enable_if< is_vector<T>::value, std::ostream &>::type operator<<( std::ostream& os, T const& v ) {
    os << "(" << v.size() << ")[" << v(0) ;
    for (typename T::size_type i=1; i<(v.size()); ++i) {
      os << "," << v(i) ;
    }
    os << "]" ;
    return os ;
  }*/

}

#endif
