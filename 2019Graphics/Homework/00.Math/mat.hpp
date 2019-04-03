#ifndef KMUVCL_GRAPHICS_MAT_HPP
#define KMUVCL_GRAPHICS_MAT_HPP

#include <iostream>
#include <cstring>
#include <cstdarg>

namespace kmuvcl {
  namespace math {

    template <unsigned int M, unsigned int N, typename T>
    class mat
    {
    public:
      mat()
      {
        set_to_zero();
      }

      mat(const T elem)
      {
        std::fill(val, val + M*N, elem);
      }

      T& operator()(unsigned int r, unsigned int c)
      {
        // TODO: Fill up this function properly
        // Notice: The matrix is column major
        // val(r,c)

        int where = r + c*N;
        return  val[where];
      }

      const T& operator()(unsigned int r, unsigned int c) const
      {
        // TODO: Fill up this function properly
        // Notice: The matrix is column major
        int where = r + c*N;
        return  val[where];
      }

      void printval(){
        for (size_t i = 0; i < N*M; i++) {
          /* code */
          std::cout << "val[" << i << "] : " << val[i]  << '\n';
        }
      }

      // type casting operators
      operator const T* () const
      {
        return  val;
      }

      operator T* ()
      {
        return  val;
      }

      void set_to_zero()
      {
        // TODO: Fill up this function properly
        std::fill_n(val,M*N,0);
      }

      // ith columns을 vec로 구성해 어떻게 전달할 것인가??
      void get_ith_column(unsigned int i, vec<M, T>& col) const
      {
        // TODO: Fill up this function properly
        for (size_t j = 0; j < N; j++) {
          /* code */
          col(j) = this->val[i*M+j];
        }
      }

      void set_ith_column(unsigned int i, const vec<M, T>& col)
      {
        // TODO: Fill up this function properly
        for (size_t j = 0; j < N; j++) {
          /* code */
          this->val[i*M+j] = col(j);
        }

      }

      void get_ith_row(unsigned int i, vec<N, T>& row) const
      {
       // TODO: Fill up this function properly
       for (size_t j = 0; j < M; j++) {
         /* code */
         row(j) = this->val[i+j*N];
       }
      }

      void set_ith_row(unsigned int i, const vec<N, T>& row)
      {
        // TODO: Fill up this function properly
        for (size_t j = 0; j < M; j++) {
          /* code */
          this->val[i+j*N] = row(j);
        }
      }

      mat<N, M, T> transpose() const
      {
        // TODO: Fill up this function properly
        mat<N, M, T>  trans;
        for (size_t i = 0; i < N; i++) {
          /* code */
          vec<M,T> tmp;
          this->get_ith_column(i,tmp);
          trans.set_ith_row(i,tmp);
        }

        return  trans;
      }

    protected:
      T val[M*N];   // column major
    };

    typedef mat<3, 3, float>    mat3x3f;
    typedef mat<3, 3, double>   mat3x3d;

    typedef mat<4, 4, float>    mat4x4f;
    typedef mat<4, 4, double>   mat4x4d;

  } // math
} // kmuvcl

#include "operator.hpp"

#endif // #ifndef KMUVCL_GRAPHICS_MAT_HPP
