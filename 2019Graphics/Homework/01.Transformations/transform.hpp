#ifndef KMUCS_GRAPHICS_TRANSFORM_HPP
#define KMUCS_GRAPHICS_TRANSFORM_HPP

#include <cmath>
#include "vec.hpp"
#include "mat.hpp"
#include "operator.hpp"

namespace kmuvcl
{
    namespace math
    {
#ifndef M_PI
        const float M_PI = 3.14159265358979323846f;
#endif

        template <typename T>
        mat<4, 4, T> translate(T dx, T dy, T dz)
        {
            mat<4, 4, T> translateMat;

            vec<4,T> col(1,0,0,0);
            vec<4,T> col1(0,1,0,0);
            vec<4,T> col2(0,0,1,0);
            vec<4,T> col3(dx,dy,dz,1);

            translateMat.set_ith_column(0,col);
            translateMat.set_ith_column(1,col1);
            translateMat.set_ith_column(2,col2);
            translateMat.set_ith_column(3,col3);

            return translateMat;
        }

        template <typename T>
        mat<4, 4, T> rotate(T angle, T x, T y, T z)
        {
            mat<4, 4, T> rotateMat;

            T v_size = sqrt(x*x + y*y + z*z);

            x /= v_size;
            y /= v_size;
            z /= v_size;

            T PI = 3.14159265358979323846;
            T radian = ( angle * PI / 180.0000);

            vec<4,T> col0( cos(radian) + x*x*(1-cos(radian)), y*x*(1-cos(radian)) + z*sin(radian), z*x*(1-cos(radian)) - y*sin(radian), 0 );
            vec<4,T> col1( x*y*(1-cos(radian)) - z*sin(radian), cos(radian) + y*y*(1-cos(radian)), z*y*(1-cos(radian)) + x*sin(radian), 0 );
            vec<4,T> col2( x*z*(1-cos(radian))+y*sin(radian),  y*z*(1-cos(radian))-x*sin(radian), cos(radian)+z*z*(1-cos(radian)), 0 );
            vec<4,T> col3(0,0,0,1);

            rotateMat.set_ith_column(0,col0);
            rotateMat.set_ith_column(1,col1);
            rotateMat.set_ith_column(2,col2);
            rotateMat.set_ith_column(3,col3);
            // TODO: Fill up this function properly

            return rotateMat;
        }

        template<typename T>
        mat<4, 4, T> scale(T sx, T sy, T sz)
        {
            mat<4, 4, T> scaleMat;

            vec<4,T> col(sx,0,0,0);
            vec<4,T> col1(0,sy,0,0);
            vec<4,T> col2(0,0,sz,0);
            vec<4,T> col3(0,0,0,1);

            scaleMat.set_ith_column(0,col);
            scaleMat.set_ith_column(1,col1);
            scaleMat.set_ith_column(2,col2);
            scaleMat.set_ith_column(3,col3);
            // TODO: Fill up this function properly

            return scaleMat;
        }

        template<typename T>
        mat<4, 4, T> lookAt(T eyeX, T eyeY, T eyeZ, T centerX, T centerY, T centerZ, T upX, T upY, T upZ)
        {
            mat<4, 4, T> viewMat;

            // TODO: Fill up this function properly
            // 시점 변환 행렬 view transformation

            mat<4,4,T> rightMat;
            mat<4,4,T> leftMat;

            vec<4,T> col0(1,0,0,0);
            vec<4,T> col1(0,1,0,0);
            vec<4,T> col2(0,0,1,0);
            vec<4,T> col3(-eyeX,-eyeY,-eyeZ,1);

            rightMat.set_ith_column(0,col0);
            rightMat.set_ith_column(1,col1);
            rightMat.set_ith_column(2,col2);
            rightMat.set_ith_column(3,col3);

            // Get Z-Vector
            T z_x = eyeX - centerX;
            T z_y = eyeY - centerY;
            T z_z = eyeZ - centerZ;

            T z_size = sqrt(z_x*z_x + z_y*z_y + z_z*z_z);
            z_x /= z_size;
            z_y /= z_size;
            z_z /= z_size;

            vec<3,T> z_vector(z_x,z_y,z_z);

            // up - eye
            T y_x = upX; // - eyeX;
            T y_y = upY; // - eyeY;
            T y_z = upZ; // - eyeZ;

            vec<3,T> tmp_y(y_x,y_y,y_z);

            // cross product
            vec<3,T> x_vector = cross(tmp_y,z_vector);

            T x_size = sqrt(x_vector(0)*x_vector(0)
                          + x_vector(1)*x_vector(1)
                        + x_vector(2)*x_vector(2));

            x_vector(0) = x_vector(0)/x_size;
            x_vector(1) = x_vector(1)/x_size;
            x_vector(2) = x_vector(2)/x_size;

            //cross product for get real Y vector
            vec<3,T> y_vector = cross(z_vector,x_vector);

            vec<4,T> row_x(x_vector(0),x_vector(1),x_vector(2),0);
            vec<4,T> row_y(y_vector(0),y_vector(1),y_vector(2),0);
            vec<4,T> row_z(z_vector(0),z_vector(1),z_vector(2),0);
            vec<4,T> row_4(0,0,0,1);

            leftMat.set_ith_row(0,row_x);
            leftMat.set_ith_row(1,row_y);
            leftMat.set_ith_row(2,row_z);
            leftMat.set_ith_row(3,row_4);

            std::cout << "left Mat" << '\n' << leftMat << '\n';
            std::cout << "right Mat " << '\n' << rightMat << '\n';
            viewMat = leftMat * rightMat;

            return viewMat;
        }

        template<typename T>
        mat<4, 4, T> ortho(T left, T right, T bottom, T top, T nearVal, T farVal)
        {
            mat<4, 4, T> orthoMat;

            // TODO: Fill up this function properly
            vec<4,T> col0(2/(right-left),0,0,0);
            vec<4,T> col1(0,2/(top-bottom),0,0);
            vec<4,T> col2(0,0,-2/(farVal-nearVal),0);
            vec<4,T> col3(-(right+left)/(right-left),-(top+bottom)/(top-bottom),-(farVal+nearVal)/(farVal-nearVal),1);

            orthoMat.set_ith_column(0,col0);
            orthoMat.set_ith_column(1,col1);
            orthoMat.set_ith_column(2,col2);
            orthoMat.set_ith_column(3,col3);

            return orthoMat;
        }

        template<typename T>
        mat<4, 4, T> frustum(T left, T right, T bottom, T top, T nearVal, T farVal)
        {
           mat<4, 4, T> frustumMat;

           // TODO: Fill up this function properly
           vec<4,T> col0( 2*nearVal/(right-left) , 0 , 0 , 0 );
           vec<4,T> col1( 0 , 2*nearVal/(top-bottom) , 0 , 0 );
           vec<4,T> col2( (right+left)/(right-left) , (top+bottom)/(top-bottom) , -(farVal+nearVal)/(farVal-nearVal) , -1 );
           vec<4,T> col3( 0 , 0 , -(2*farVal*nearVal)/(farVal-nearVal) , 0 );

           frustumMat.set_ith_column(0,col0);
           frustumMat.set_ith_column(1,col1);
           frustumMat.set_ith_column(2,col2);
           frustumMat.set_ith_column(3,col3);

           return frustumMat;
        }

        template<typename T>
        mat<4, 4, T> perspective(T fovy, T aspect, T zNear, T zFar)
        {
          T  right = 0;
          T  top = 0;
          T PI = 3.14159265358979323846;

          top = zNear * tan(fovy*PI/360.0);
          right = top * aspect;

          // TODO: Fill up this function properly

          return frustum(-right, right, -top, top, zNear, zFar);
        }
    }
}
#endif
