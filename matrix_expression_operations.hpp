#ifndef tws_et_matrix_exprecion_operators_hpp
#define tws_et_matrix_exprecion_operators_hpp

#include "is_matrix.hpp"
#include <cassert>
#include <type_traits>

namespace tws {

  template <typename M1, typename M2>
  class matrix_sum {
    public:
      typedef typename std::common_type< typename M1::value_type
                                       , typename M2::value_type
                                       >::type value_type ;
      typedef typename M1::size_type size_type ;

      static_assert( is_matrix<M1>::value, "V1 should be a matrix" ) ;
      static_assert( is_matrix<M2>::value, "V2 should be a matrix" ) ;

    public:
      matrix_sum( M1 const& m1, M2 const& m2 )
      : m1_( m1 )
      , m2_( m2 )
      {
        assert( m1_.rows()==m2_.rows() ) ;
        assert( m1_.columns()==m2_.columns() ) ;
      }

      size_type size() const {
        return m1_.size() ;
      }
      size_type rows() const {
        return m1_.rows();
      }

      size_type columns() const {
        return m1_.columns();
      }


      value_type operator[] (size_type i) const {
        assert( i>=0 && i<size() ) ;
        return m1_[i] + m2_[i] ;
      }

    private:
      M1 const& m1_ ;
      M2 const& m2_ ;
  } ;

  template <typename M1, typename M2>
  typename std::enable_if< is_matrix<M1>::value && is_matrix<M2>::value, matrix_sum<M1,M2> >::type operator+( M1 const& m1, M2 const& m2 ) {
    return matrix_sum<M1,M2>( m1, m2 ) ;
  }

  template <typename M1, typename M2>
  struct is_matrix< matrix_sum<M1,M2> >
  {
    static bool const value = is_matrix<M1>::value && is_matrix<M2>::value ;
  };

// difference
  template <typename M1, typename M2>
  class matrix_dif {
    public:
      typedef typename std::common_type< typename M1::value_type
                                       , typename M2::value_type
                                       >::type value_type ;
      typedef typename M1::size_type size_type ;

      static_assert( is_matrix<M1>::value, "M1 should be a matrix" ) ;
      static_assert( is_matrix<M2>::value, "M2 should be a matrix" ) ;

    public:
      matrix_dif( M1 const& m1, M2 const& m2 )
      : m1_( m1 )
      , m2_( m2 )
      {
        assert( m1_.rows()==m2_.rows() ) ;
        assert( m1_.columns()==m2_.columns() ) ;
      }


      size_type size() const {
        return m1_.size() ;
      }
      size_type rows() const {
        return m1_.rows();
      }

      size_type columns() const {
        return m1_.columns();
      }


      value_type operator[] (size_type i) const {
        assert( i>=0 && i<size() ) ;
        return m1_[i] - m2_[i] ;
      }


    private:
      M1 const& m1_ ;
      M2 const& m2_ ;
  } ;

  template <typename M1, typename M2>
  typename std::enable_if< is_matrix<M1>::value && is_matrix<M2>::value, matrix_dif<M1,M2> >::type operator-( M1 const& m1, M2 const& m2 ) {
    return matrix_dif<M1,M2>( m1, m2 ) ;
  }

  template <typename M1, typename M2>
  struct is_matrix< matrix_dif<M1,M2> >
  {
    static bool const value = is_matrix<M1>::value && is_matrix<M2>::value ;
  };


// product scalar

  template <typename M1, typename S1>
  class matrix_mul {
    public:
      typedef typename std::common_type< typename M1::value_type
                                       , S1
                                       >::type value_type ;
      typedef typename M1::size_type size_type ;

      static_assert( is_matrix<M1>::value, "M1 should be a matrix" ) ;

//      static_assert( is_matrix<V2>::value, "V2 should be a matrix" ) ;

// constructor
    public:
      matrix_mul( M1 const& m1, S1 const& s1 )
      : m1_( m1 )
      , s1_( s1 )
      {}


      size_type size() const {
        return m1_.size() ;
      }

      size_type rows() const {
        return m1_.rows();
      }

      size_type columns() const {
        return m1_.columns();
      }

      value_type operator[] (size_type i) const {
        assert( i>=0 && i<size() ) ;
        return m1_[i] * s1_ ;
      }

    private:
      M1 const& m1_ ;
      S1 const& s1_ ;
  } ;

  template <typename M1, typename S1>
  typename std::enable_if< is_matrix<M1>::value , matrix_mul<M1,S1> >::type operator*( M1 const& m1, S1 const& s1 ) {
      return matrix_mul<M1,S1>( m1, s1 ) ;
  }

  template <typename M1, typename S1>
  typename std::enable_if< is_matrix<M1>::value , matrix_mul<M1,S1> >::type operator*( S1 const& s1, M1 const& m1 ) {
      return matrix_mul<M1,S1>( m1, s1 ) ;
  }


  template <typename M1, typename S1>
  struct is_matrix< matrix_mul<M1,S1> >
  {
    static bool const value = is_matrix<M1>::value;// && is_matrix<V2>::value ;
  };


// transpose

  template <typename M1>
  class matrix_trans {
    public:
      typedef typename std::common_type< typename M1::value_type>::type value_type ;
      typedef typename M1::size_type size_type ;

      static_assert( is_matrix<M1>::value, "M1 should be a matrix" ) ;

//      static_assert( is_matrix<V2>::value, "V2 should be a matrix" ) ;

// constructor
    public:
      matrix_trans( M1 const& m1)
      :m1_( m1 ) // matrix m1_(m1.columns,m1.rows,m1(0,0)) //m1_( m1 )
      {}

      size_type size() const {
        return m1_.size() ;
      }

      size_type rows() const {
        return m1_.columns();
      }

      size_type columns() const {
        return m1_.rows();
      }

      value_type operator[] (size_type i) const {
        assert( i>=0 && i<size() ) ;
        return m1_[(i/m1_.columns())+(m1_.rows()*(i%m1_.columns()))] ;
      }

    private:
      M1 const& m1_ ;
  } ;

  template <typename M1>
  struct is_matrix< matrix_trans<M1> >
  {
    static bool const value = is_matrix<M1>::value;// && is_matrix<V2>::value ;
  };

}
  template <typename M1>
  inline decltype(auto) transpose( M1 const& m1 ){
      return tws::matrix_trans<M1>( m1 ) ;
  };


//} // namespace tws

#endif

