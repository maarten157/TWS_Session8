#ifndef tws_matrix_hpp
#define tws_matrix_hpp
//(C) Copyright Karl Meerbergen, Gowri Suryanarayana, Yuya Suzuki & Joris Tavernier, 2016.
#include <vector>
#include <cassert>
#include <cmath>
#include <iostream>
#include <type_traits>
#include <algorithm>
#include <random>
#include <chrono>
#include "is_matrix.hpp"

namespace tws {
  template <typename T>
  class matrix {
    int Rows, Columns;
    private:
      typedef std::vector<T> data_type ;

    public:
      typedef T value_type ;
      typedef int size_type;

    public:
      inline matrix(size_type m, size_type n )
      : data_(m * n )
      { Rows = m; Columns = n ; }

      inline matrix(size_type m, size_type n, T val )
      : data_(m * n,val )
      { Rows = m; Columns = n ;  }

      matrix( matrix<T> const& m )
      : data_( m.data_ )
      { }

      template <typename Matrix>
      matrix( Matrix const& m )
      : data_( m.size() )
      {
        for (size_type i=0; i<size(); ++i) { data_[i] = m[i] ; }
      }

      inline size_type size() const { return data_.size() ; }

      inline size_type rows() const { return Rows ;}

      inline size_type columns() const { return Columns;}

      inline value_type operator[](size_type i) const
      { return data_[i] ; }

      inline value_type& operator[](size_type i)
      { return data_[i] ; }


      inline value_type operator()(size_type i, size_type j) const
      { return data_[(j)*Rows+(i)] ; }

      inline value_type& operator()(size_type i, size_type j)
      { return data_[(j)*Rows+(i)] ; }


      template <typename Scalar>
      inline void operator=(matrix<Scalar> const& m ) {
         std::copy(m.begin(),m.end(),data_.begin());
         Rows=m.rows();
         Columns=m.columns();
      }

      template <typename Matrix>
      inline void operator=(Matrix const& m ) {
         for (size_type i=0; i<size(); ++i) { data_[i] = m[i] ; }
         Rows=m.rows();
         Columns=m.columns();
      }

      template <typename Matrix>
      inline void operator-=(Matrix const& m ) {
         assert(this->rows()==m.rows());
         assert(this->columns()==m.columns());
         for (size_type i=0; i<size(); ++i) { data_[i] = data_[i]-m[i] ; }
      }

      template <typename Matrix>
      inline void operator+=(Matrix const& m ) {
         assert(this->rows()==m.rows());
         assert(this->columns()==m.columns());
         for (size_type i=0; i<size(); ++i) { data_[i] = data_[i]+m[i] ; }
      }

      void randomize(){
         int seed = 1;
         #ifdef NDEBUG
            seed = std::chrono::system_clock::now().time_since_epoch().count();
         #endif
         auto engine = std::default_random_engine(seed);
         std::uniform_real_distribution<value_type> distribution(0.0,1.0);
         for (size_type i=0; i<size(); ++i) { data_[i] =distribution(engine) ; }
      }

    public:
      friend std::ostream& operator<<( std::ostream& ostr, matrix<T> const& m ) {
        ostr << "(" << m.rows() << ", " <<m.columns() << ")" << std::endl ;
        for (int i=0; i<m.rows(); ++i) {
          for (int j=0; j<m.columns(); ++j){
          ostr << m(i,j) << " " ;
          }
        ostr << std::endl;
        }
      ostr << std::endl ;
        return ostr ;
      }

    private:
      data_type data_ ;

  } ;

  template <typename T>
  struct is_matrix< matrix<T> >
  : std::true_type
  {} ;

}
#endif
