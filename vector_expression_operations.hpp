#ifndef tws_et_vector_exprecion_operators_hpp
#define tws_et_vector_exprecion_operators_hpp

#include "is_vector.hpp"
#include <cassert>
#include <type_traits>

namespace tws {

  template <typename V1, typename V2>
  class vector_sum {
    public:
      typedef typename std::common_type< typename V1::value_type
                                       , typename V2::value_type
                                       >::type value_type ;
      typedef typename V1::size_type size_type ;

      static_assert( is_vector<V1>::value, "V1 should be a Vector" ) ;
      static_assert( is_vector<V2>::value, "V2 should be a Vector" ) ;

    public:
      vector_sum( V1 const& v1, V2 const& v2 )
      : v1_( v1 )
      , v2_( v2 )
      {
        assert( v1_.size()==v2_.size() ) ;
      }

      size_type size() const {
        return v1_.size() ;
      }

      value_type operator() (size_type i) const {
        assert( i>=0 && i<size() ) ;
        return v1_(i) + v2_(i) ;
      }

      value_type operator[] (size_type i) const {
        assert( i>=0 && i<size() ) ;
        return v1_(i) + v2_(i) ;
      }

    private:
      V1 const& v1_ ;
      V2 const& v2_ ;
  } ;

  template <typename V1, typename V2>
  typename std::enable_if< is_vector<V1>::value && is_vector<V2>::value, vector_sum<V1,V2> >::type operator+( V1 const& v1, V2 const& v2 ) {
    return vector_sum<V1,V2>( v1, v2 ) ;
  }

  template <typename V1, typename V2>
  struct is_vector< vector_sum<V1,V2> >
  {
    static bool const value = is_vector<V1>::value && is_vector<V2>::value ;
  };

// difference
  template <typename V1, typename V2>
  class vector_dif {
    public:
      typedef typename std::common_type< typename V1::value_type
                                       , typename V2::value_type
                                       >::type value_type ;
      typedef typename V1::size_type size_type ;

      static_assert( is_vector<V1>::value, "V1 should be a Vector" ) ;
      static_assert( is_vector<V2>::value, "V2 should be a Vector" ) ;

    public:
      vector_dif( V1 const& v1, V2 const& v2 )
      : v1_( v1 )
      , v2_( v2 )
      {
        assert( v1_.size()==v2_.size() ) ;
      }


      size_type size() const {
        return v1_.size() ;
      }

      value_type operator() (size_type i) const {
        assert( i>=0 && i<size() ) ;
        return v1_(i) - v2_(i) ;
      }

      value_type operator[] (size_type i) const {
        assert( i>=0 && i<size() ) ;
        return v1_(i) - v2_(i) ;
      }

    private:
      V1 const& v1_ ;
      V2 const& v2_ ;
  } ;

  template <typename V1, typename V2>
  typename std::enable_if< is_vector<V1>::value && is_vector<V2>::value, vector_dif<V1,V2> >::type operator-( V1 const& v1, V2 const& v2 ) {
    return vector_dif<V1,V2>( v1, v2 ) ;
  }

  template <typename V1, typename V2>
  struct is_vector< vector_dif<V1,V2> >
  {
    static bool const value = is_vector<V1>::value && is_vector<V2>::value ;
  };

// product scalar

  template <typename V1, typename S1>
  class vector_mul {
    public:
      typedef typename std::common_type< typename V1::value_type
                                       , S1
                                       >::type value_type ;
      typedef typename V1::size_type size_type ;

      static_assert( is_vector<V1>::value, "V1 should be a Vector" ) ;

    public:
      vector_mul( V1 const& v1, S1 const& s1 )
      : v1_( v1 )
      , s1_( s1 )
      {}

      size_type size() const {
        return v1_.size() ;
      }

      value_type operator() (size_type i) const {
        assert( i>=0 && i<size() ) ;
        return v1_(i) * s1_ ;
      }

      value_type operator[] (size_type i) const {
        assert( i>=0 && i<size() ) ;
        return v1_(i) * s1_ ;
      }

    private:
      V1 const& v1_ ;
      S1 const& s1_ ;
  } ;

  template <typename V1, typename S1>
  typename std::enable_if< is_vector<V1>::value , vector_mul<V1,S1> >::type operator*( V1 const& v1, S1 const& s1 ) {
      return vector_mul<V1,S1>( v1, s1 ) ;
  }

  template <typename V1, typename S1>
  typename std::enable_if< is_vector<V1>::value , vector_mul<V1,S1> >::type operator*( S1 const& s1, V1 const& v1 ) {
      return vector_mul<V1,S1>( v1, s1 ) ;
  }

  template <typename V1, typename S1>
  struct is_vector< vector_mul<V1,S1> >
  {
    static bool const value = is_vector<V1>::value;
  };

// product Matrix-vector

  template <typename M1, typename V1>
  class matrix_vector_mul {
    public:
      typedef typename std::common_type< typename M1::value_type
                                       , typename V1::value_type
                                       >::type value_type ;
      typedef typename V1::size_type size_type ;

      static_assert( is_matrix<M1>::value, "M1 should be a Matrix" ) ;
      static_assert( is_vector<V1>::value, "V1 should be a Vector" ) ;

    public:
      matrix_vector_mul( M1 const& m1, V1 const& v1 )
      : m1_( m1 )
      , v1_( v1 )
      {}

      size_type size() const {
        return m1_.rows() ;
      }

      value_type operator() (size_type i) const {
        assert( i>=0 && i<size() ) ;
        assert( m1_.columns()==v1_.size());
        typename V1::value_type sum_row;
        sum_row = 0.0;
        for (typename V1::size_type j=0;j<m1_.columns();j++) sum_row += m1_[i+j*m1_.rows()]*v1_[j] ;
        return sum_row ;
      }

      value_type operator[] (size_type i) const {
        assert( i>=0 && i<size() ) ;
        assert( m1_.columns()==v1_.size());
        typename V1::value_type sum_row;
        sum_row = 0.0;
        for (typename V1::size_type j=0;j<m1_.columns();j++) sum_row += m1_[i+j*m1_.rows()]*v1_[j]  ;
        return sum_row ;
      }

    private:
      M1 const& m1_ ;
      V1 const& v1_ ;
  } ;

  template <typename M1, typename V1>
  struct is_vector< matrix_vector_mul<M1,V1> >
  {
    static bool const value = is_vector<V1>::value;
  };

} // namespace tws

  template <typename M1, typename V1>
  inline decltype(auto) multiply( M1 const& m1, V1 const& v1 ){
      return tws::matrix_vector_mul<M1,V1>( m1,v1 ) ;
  };

#endif

