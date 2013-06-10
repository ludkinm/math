#include <stan/agrad/fwd/matrix/multiply.hpp>
#include <gtest/gtest.h>
#include <stan/math/matrix/multiply.hpp>
#include <stan/math/matrix/typedefs.hpp>
#include <stan/agrad/fwd/matrix/typedefs.hpp>
#include <stan/agrad/fwd/fvar.hpp>
#include <stan/agrad/var.hpp>
#include <stan/agrad/rev/matrix/multiply.hpp>

using stan::agrad::fvar;  
using stan::agrad::var;  
using stan::agrad::multiply;

TEST(AgradFwdMatrix, multiply_vector_scalar) {
  using stan::math::vector_d;
  using stan::agrad::vector_fv;

  vector_d d1(3);
  vector_fv v1(3);
  double d2;
  fvar<double> v2;
  
  d1 << 100, 0, -3;
  v1 << 100, 0, -3;
   v1(0).d_ = 1.0;  
   v1(1).d_ = 1.0;
   v1(2).d_ = 1.0;
  d2 = -2;
  v2 = -2;
   v2.d_ = 1.0;  

  vector_fv output;
  output = multiply(d1, v2);
  EXPECT_FLOAT_EQ(-200, output(0).val_);
  EXPECT_FLOAT_EQ(   0, output(1).val_);
  EXPECT_FLOAT_EQ(   6, output(2).val_);
  EXPECT_FLOAT_EQ( 100, output(0).d_);
  EXPECT_FLOAT_EQ(   0, output(1).d_);
  EXPECT_FLOAT_EQ(  -3, output(2).d_);

  output = multiply(v2, d1);
  EXPECT_FLOAT_EQ(-200, output(0).val_);
  EXPECT_FLOAT_EQ(   0, output(1).val_);
  EXPECT_FLOAT_EQ(   6, output(2).val_);
  EXPECT_FLOAT_EQ( 100, output(0).d_);
  EXPECT_FLOAT_EQ(   0, output(1).d_);
  EXPECT_FLOAT_EQ(  -3, output(2).d_);

  output = multiply(v1, d2);
  EXPECT_FLOAT_EQ(-200, output(0).val_);
  EXPECT_FLOAT_EQ(   0, output(1).val_);
  EXPECT_FLOAT_EQ(   6, output(2).val_);
  EXPECT_FLOAT_EQ(  -2, output(0).d_);
  EXPECT_FLOAT_EQ(  -2, output(1).d_);
  EXPECT_FLOAT_EQ(  -2, output(2).d_);

  output = multiply(d2, v1);
  EXPECT_FLOAT_EQ(-200, output(0).val_);
  EXPECT_FLOAT_EQ(   0, output(1).val_);
  EXPECT_FLOAT_EQ(   6, output(2).val_);
  EXPECT_FLOAT_EQ(  -2, output(0).d_);
  EXPECT_FLOAT_EQ(  -2, output(1).d_);
  EXPECT_FLOAT_EQ(  -2, output(2).d_);

  output = multiply(v1, v2);
  EXPECT_FLOAT_EQ(-200, output(0).val_);
  EXPECT_FLOAT_EQ(   0, output(1).val_);
  EXPECT_FLOAT_EQ(   6, output(2).val_);
  EXPECT_FLOAT_EQ(  98, output(0).d_);
  EXPECT_FLOAT_EQ(  -2, output(1).d_);
  EXPECT_FLOAT_EQ(  -5, output(2).d_);

  output = multiply(v2, v1);
  EXPECT_FLOAT_EQ(-200, output(0).val_);
  EXPECT_FLOAT_EQ(   0, output(1).val_);
  EXPECT_FLOAT_EQ(   6, output(2).val_);
  EXPECT_FLOAT_EQ(  98, output(0).d_);
  EXPECT_FLOAT_EQ(  -2, output(1).d_);
  EXPECT_FLOAT_EQ(  -5, output(2).d_);
}

TEST(AgradFwdMatrix, multiply_rowvector_scalar) {
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_fv;

  row_vector_d d1(3);
  row_vector_fv v1(3);
  double d2;
  fvar<double> v2;
  
  d1 << 100, 0, -3;
  v1 << 100, 0, -3;
   v1(0).d_ = 1.0;  
   v1(1).d_ = 1.0;
   v1(2).d_ = 1.0;
  d2 = -2;
  v2 = -2;
   v2.d_ = 1.0;
  
  row_vector_fv output;
  output = multiply(d1, v2);
  EXPECT_FLOAT_EQ(-200, output(0).val_);
  EXPECT_FLOAT_EQ(   0, output(1).val_);
  EXPECT_FLOAT_EQ(   6, output(2).val_);
  EXPECT_FLOAT_EQ( 100, output(0).d_);
  EXPECT_FLOAT_EQ(   0, output(1).d_);
  EXPECT_FLOAT_EQ(  -3, output(2).d_);

  output = multiply(v1, d2);
  EXPECT_FLOAT_EQ(-200, output(0).val_);
  EXPECT_FLOAT_EQ(   0, output(1).val_);
  EXPECT_FLOAT_EQ(   6, output(2).val_);
  EXPECT_FLOAT_EQ(  -2, output(0).d_);
  EXPECT_FLOAT_EQ(  -2, output(1).d_);
  EXPECT_FLOAT_EQ(  -2, output(2).d_);

  output = multiply(v1, v2);
  EXPECT_FLOAT_EQ(-200, output(0).val_);
  EXPECT_FLOAT_EQ(   0, output(1).val_);
  EXPECT_FLOAT_EQ(   6, output(2).val_);
  EXPECT_FLOAT_EQ(  98, output(0).d_);
  EXPECT_FLOAT_EQ(  -2, output(1).d_);
  EXPECT_FLOAT_EQ(  -5, output(2).d_);

  output = multiply(v2, d1);
  EXPECT_FLOAT_EQ(-200, output(0).val_);
  EXPECT_FLOAT_EQ(   0, output(1).val_);
  EXPECT_FLOAT_EQ(   6, output(2).val_);
  EXPECT_FLOAT_EQ( 100, output(0).d_);
  EXPECT_FLOAT_EQ(   0, output(1).d_);
  EXPECT_FLOAT_EQ(  -3, output(2).d_);

  output = multiply(d2, v1);
  EXPECT_FLOAT_EQ(-200, output(0).val_);
  EXPECT_FLOAT_EQ(   0, output(1).val_);
  EXPECT_FLOAT_EQ(   6, output(2).val_);
  EXPECT_FLOAT_EQ(  -2, output(0).d_);
  EXPECT_FLOAT_EQ(  -2, output(1).d_);
  EXPECT_FLOAT_EQ(  -2, output(2).d_);

  output = multiply(v2, v1);
  EXPECT_FLOAT_EQ(-200, output(0).val_);
  EXPECT_FLOAT_EQ(   0, output(1).val_);
  EXPECT_FLOAT_EQ(   6, output(2).val_);
  EXPECT_FLOAT_EQ(  98, output(0).d_);
  EXPECT_FLOAT_EQ(  -2, output(1).d_);
  EXPECT_FLOAT_EQ(  -5, output(2).d_);
}
TEST(AgradFwdMatrix, multiply_matrix_scalar) {
  using stan::math::matrix_d;
  using stan::agrad::matrix_fv;
  
  matrix_d d1(2,2);
  matrix_fv v1(2,2);
  double d2;
  fvar<double> v2;
  
  d1 << 100, 0, -3, 4;
  v1 << 100, 0, -3, 4;
   v1(0,0).d_ = 1.0; 
   v1(0,1).d_ = 1.0; 
   v1(1,0).d_ = 1.0; 
   v1(1,1).d_ = 1.0; 
  d2 = -2;
  v2 = -2;
   v2.d_ = 1.0;

  matrix_fv output;
  output = multiply(d1, v2);
  EXPECT_FLOAT_EQ(-200, output(0,0).val_);
  EXPECT_FLOAT_EQ(   0, output(0,1).val_);
  EXPECT_FLOAT_EQ(   6, output(1,0).val_);
  EXPECT_FLOAT_EQ(  -8, output(1,1).val_);
  EXPECT_FLOAT_EQ( 100, output(0,0).d_);
  EXPECT_FLOAT_EQ(   0, output(0,1).d_);
  EXPECT_FLOAT_EQ(  -3, output(1,0).d_);
  EXPECT_FLOAT_EQ(   4, output(1,1).d_);

  output = multiply(v1, d2);
  EXPECT_FLOAT_EQ(-200, output(0,0).val_);
  EXPECT_FLOAT_EQ(   0, output(0,1).val_);
  EXPECT_FLOAT_EQ(   6, output(1,0).val_);
  EXPECT_FLOAT_EQ(  -8, output(1,1).val_);
  EXPECT_FLOAT_EQ(  -2, output(0,0).d_);
  EXPECT_FLOAT_EQ(  -2, output(0,1).d_);
  EXPECT_FLOAT_EQ(  -2, output(1,0).d_);
  EXPECT_FLOAT_EQ(  -2, output(1,1).d_);
 
  output = multiply(v1, v2);
  EXPECT_FLOAT_EQ(-200, output(0,0).val_);
  EXPECT_FLOAT_EQ(   0, output(0,1).val_);
  EXPECT_FLOAT_EQ(   6, output(1,0).val_);
  EXPECT_FLOAT_EQ(  -8, output(1,1).val_);
  EXPECT_FLOAT_EQ(  98, output(0,0).d_);
  EXPECT_FLOAT_EQ(  -2, output(0,1).d_);
  EXPECT_FLOAT_EQ(  -5, output(1,0).d_);
  EXPECT_FLOAT_EQ(   2, output(1,1).d_);

  output = multiply(v2, d1);
  EXPECT_FLOAT_EQ(-200, output(0,0).val_);
  EXPECT_FLOAT_EQ(   0, output(0,1).val_);
  EXPECT_FLOAT_EQ(   6, output(1,0).val_);
  EXPECT_FLOAT_EQ(  -8, output(1,1).val_);
  EXPECT_FLOAT_EQ( 100, output(0,0).d_);
  EXPECT_FLOAT_EQ(   0, output(0,1).d_);
  EXPECT_FLOAT_EQ(  -3, output(1,0).d_);
  EXPECT_FLOAT_EQ(   4, output(1,1).d_);

  output = multiply(d2, v1);
  EXPECT_FLOAT_EQ(-200, output(0,0).val_);
  EXPECT_FLOAT_EQ(   0, output(0,1).val_);
  EXPECT_FLOAT_EQ(   6, output(1,0).val_);
  EXPECT_FLOAT_EQ(  -8, output(1,1).val_);
  EXPECT_FLOAT_EQ(  -2, output(0,0).d_);
  EXPECT_FLOAT_EQ(  -2, output(0,1).d_);
  EXPECT_FLOAT_EQ(  -2, output(1,0).d_);
  EXPECT_FLOAT_EQ(  -2, output(1,1).d_);
 
  output = multiply(v2, v1);
  EXPECT_FLOAT_EQ(-200, output(0,0).val_);
  EXPECT_FLOAT_EQ(   0, output(0,1).val_);
  EXPECT_FLOAT_EQ(   6, output(1,0).val_);
  EXPECT_FLOAT_EQ(  -8, output(1,1).val_);
  EXPECT_FLOAT_EQ(  98, output(0,0).d_);
  EXPECT_FLOAT_EQ(  -2, output(0,1).d_);
  EXPECT_FLOAT_EQ(  -5, output(1,0).d_);
  EXPECT_FLOAT_EQ(   2, output(1,1).d_);
}
TEST(AgradFwdMatrix, multiply_rowvector_vector) {
  using stan::math::vector_d;
  using stan::agrad::vector_fv;
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_fv;

  row_vector_d d1(3);
  row_vector_fv v1(3);
  vector_d d2(3);
  vector_fv v2(3);
  
  d1 << 1, 3, -5;
  v1 << 1, 3, -5;
   v1(0).d_ = 1.0;
   v1(1).d_ = 1.0;
   v1(2).d_ = 1.0;
  d2 << 4, -2, -1;
  v2 << 4, -2, -1;
   v2(0).d_ = 1.0;
   v2(1).d_ = 1.0;
   v2(2).d_ = 1.0;

  EXPECT_FLOAT_EQ( 3, multiply(v1, v2).val_);
  EXPECT_FLOAT_EQ( 3, multiply(v1, d2).val_);
  EXPECT_FLOAT_EQ( 3, multiply(d1, v2).val_);
  EXPECT_FLOAT_EQ( 0, multiply(v1, v2).d_);
  EXPECT_FLOAT_EQ( 1, multiply(v1 ,d2).d_);
  EXPECT_FLOAT_EQ(-1, multiply(d1 ,v2).d_);

  d1.resize(1);
  v1.resize(1);
  EXPECT_THROW(multiply(v1, v2), std::domain_error);
  EXPECT_THROW(multiply(v1, d2), std::domain_error);
  EXPECT_THROW(multiply(d1, v2), std::domain_error);
}
TEST(AgradFwdMatrix, multiply_vector_rowvector) {
  using stan::agrad::matrix_fv;
  using stan::math::vector_d;
  using stan::agrad::vector_fv;
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_fv;

  vector_d d1(3);
  vector_fv v1(3);
  row_vector_d d2(3);
  row_vector_fv v2(3);
  
  d1 << 1, 3, -5;
  v1 << 1, 3, -5;
   v1(0).d_ = 1.0;
   v1(1).d_ = 1.0;
   v1(2).d_ = 1.0;
  d2 << 4, -2, -1;
  v2 << 4, -2, -1;
   v2(0).d_ = 1.0;
   v2(1).d_ = 1.0;
   v2(2).d_ = 1.0;

  matrix_fv output = multiply(v1, v2);
  EXPECT_EQ(3, output.rows());
  EXPECT_EQ(3, output.cols());
  EXPECT_FLOAT_EQ(  4, output(0,0).val_);
  EXPECT_FLOAT_EQ( -2, output(0,1).val_);
  EXPECT_FLOAT_EQ( -1, output(0,2).val_);
  EXPECT_FLOAT_EQ( 12, output(1,0).val_);
  EXPECT_FLOAT_EQ( -6, output(1,1).val_);
  EXPECT_FLOAT_EQ( -3, output(1,2).val_);
  EXPECT_FLOAT_EQ(-20, output(2,0).val_);  
  EXPECT_FLOAT_EQ( 10, output(2,1).val_);
  EXPECT_FLOAT_EQ(  5, output(2,2).val_);
  EXPECT_FLOAT_EQ(  5, output(0,0).d_);
  EXPECT_FLOAT_EQ( -1, output(0,1).d_);
  EXPECT_FLOAT_EQ(  0, output(0,2).d_);
  EXPECT_FLOAT_EQ(  7, output(1,0).d_);
  EXPECT_FLOAT_EQ(  1, output(1,1).d_);
  EXPECT_FLOAT_EQ(  2, output(1,2).d_);
  EXPECT_FLOAT_EQ( -1, output(2,0).d_);
  EXPECT_FLOAT_EQ( -7, output(2,1).d_);
  EXPECT_FLOAT_EQ( -6, output(2,2).d_);
  
  output = multiply(v1, d2);
  EXPECT_EQ(3, output.rows());
  EXPECT_EQ(3, output.cols());
  EXPECT_FLOAT_EQ(  4, output(0,0).val_);
  EXPECT_FLOAT_EQ( -2, output(0,1).val_);
  EXPECT_FLOAT_EQ( -1, output(0,2).val_);
  EXPECT_FLOAT_EQ( 12, output(1,0).val_);
  EXPECT_FLOAT_EQ( -6, output(1,1).val_);
  EXPECT_FLOAT_EQ( -3, output(1,2).val_);
  EXPECT_FLOAT_EQ(-20, output(2,0).val_);  
  EXPECT_FLOAT_EQ( 10, output(2,1).val_);
  EXPECT_FLOAT_EQ(  5, output(2,2).val_);
  EXPECT_FLOAT_EQ(  4, output(0,0).d_);
  EXPECT_FLOAT_EQ( -2, output(0,1).d_);
  EXPECT_FLOAT_EQ( -1, output(0,2).d_);
  EXPECT_FLOAT_EQ(  4, output(1,0).d_);
  EXPECT_FLOAT_EQ( -2, output(1,1).d_);
  EXPECT_FLOAT_EQ( -1, output(1,2).d_);
  EXPECT_FLOAT_EQ(  4, output(2,0).d_);
  EXPECT_FLOAT_EQ( -2, output(2,1).d_);
  EXPECT_FLOAT_EQ( -1, output(2,2).d_);
  
  output = multiply(d1, v2);
  EXPECT_EQ(3, output.rows());
  EXPECT_EQ(3, output.cols());
  EXPECT_FLOAT_EQ(  4, output(0,0).val_);
  EXPECT_FLOAT_EQ( -2, output(0,1).val_);
  EXPECT_FLOAT_EQ( -1, output(0,2).val_);
  EXPECT_FLOAT_EQ( 12, output(1,0).val_);
  EXPECT_FLOAT_EQ( -6, output(1,1).val_);
  EXPECT_FLOAT_EQ( -3, output(1,2).val_);
  EXPECT_FLOAT_EQ(-20, output(2,0).val_);  
  EXPECT_FLOAT_EQ( 10, output(2,1).val_);
  EXPECT_FLOAT_EQ(  5, output(2,2).val_);
  EXPECT_FLOAT_EQ(  1, output(0,0).d_);
  EXPECT_FLOAT_EQ(  1, output(0,1).d_);
  EXPECT_FLOAT_EQ(  1, output(0,2).d_);
  EXPECT_FLOAT_EQ(  3, output(1,0).d_);
  EXPECT_FLOAT_EQ(  3, output(1,1).d_);
  EXPECT_FLOAT_EQ(  3, output(1,2).d_);
  EXPECT_FLOAT_EQ( -5, output(2,0).d_);
  EXPECT_FLOAT_EQ( -5, output(2,1).d_);
  EXPECT_FLOAT_EQ( -5, output(2,2).d_);
}
TEST(AgradFwdMatrix, multiply_matrix_vector) {
  using stan::math::matrix_d;
  using stan::agrad::matrix_fv;
  using stan::math::vector_d;
  using stan::agrad::vector_fv;

  matrix_d d1(3,2);
  matrix_fv v1(3,2);
  vector_d d2(2);
  vector_fv v2(2);
  
  d1 << 1, 3, -5, 4, -2, -1;
  v1 << 1, 3, -5, 4, -2, -1;
   v1(0,0).d_ = 1.0;
   v1(0,1).d_ = 1.0;
   v1(1,0).d_ = 1.0;
   v1(1,1).d_ = 1.0;
   v1(2,0).d_ = 1.0;
   v1(2,1).d_ = 1.0;
  d2 << -2, 4;
  v2 << -2, 4;
   v2(0).d_ = 1.0;
   v2(1).d_ = 1.0;

  vector_fv output = multiply(v1, v2);
  EXPECT_EQ(3, output.size());
  EXPECT_FLOAT_EQ(10, output(0).val_);
  EXPECT_FLOAT_EQ(26, output(1).val_);
  EXPECT_FLOAT_EQ( 0, output(2).val_);
  EXPECT_FLOAT_EQ( 6, output(0).d_);
  EXPECT_FLOAT_EQ( 1, output(1).d_);
  EXPECT_FLOAT_EQ(-1, output(2).d_);
  
  output = multiply(v1, d2);
  EXPECT_EQ(3, output.size());
  EXPECT_FLOAT_EQ(10, output(0).val_);
  EXPECT_FLOAT_EQ(26, output(1).val_);
  EXPECT_FLOAT_EQ( 0, output(2).val_);
  EXPECT_FLOAT_EQ( 2, output(0).d_);
  EXPECT_FLOAT_EQ( 2, output(1).d_);
  EXPECT_FLOAT_EQ( 2, output(2).d_);
  
  output = multiply(d1, v2);
  EXPECT_EQ(3, output.size());
  EXPECT_FLOAT_EQ(10, output(0).val_);
  EXPECT_FLOAT_EQ(26, output(1).val_);
  EXPECT_FLOAT_EQ( 0, output(2).val_);
  EXPECT_FLOAT_EQ( 4, output(0).d_);
  EXPECT_FLOAT_EQ(-1, output(1).d_);
  EXPECT_FLOAT_EQ(-3, output(2).d_);
}
TEST(AgradFwdMatrix, multiply_matrix_vector_exception) {
  using stan::math::matrix_d;
  using stan::agrad::matrix_fv;
  using stan::math::vector_d;
  using stan::agrad::vector_fv;

  matrix_d d1(3,2);
  matrix_fv v1(3,2);
  vector_d d2(4);
  vector_fv v2(4);
  EXPECT_THROW(multiply(v1, v2), std::domain_error);
  EXPECT_THROW(multiply(v1, d2), std::domain_error);
  EXPECT_THROW(multiply(d1, v2), std::domain_error);
}
TEST(AgradFwdMatrix, multiply_rowvector_matrix) {
  using stan::math::matrix_d;
  using stan::agrad::matrix_fv;
  using stan::agrad::vector_fv;
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_fv;

  row_vector_d d1(3);
  row_vector_fv v1(3);
  matrix_d d2(3,2);
  matrix_fv v2(3,2);
  
  d1 << -2, 4, 1;
  v1 << -2, 4, 1;
   v1(0).d_ = 1.0;
   v1(1).d_ = 1.0;
   v1(2).d_ = 1.0;
  d2 << 1, 3, -5, 4, -2, -1;
  v2 << 1, 3, -5, 4, -2, -1;
   v2(0,0).d_ = 1.0;
   v2(0,1).d_ = 1.0;
   v2(1,0).d_ = 1.0;
   v2(1,1).d_ = 1.0;
   v2(2,0).d_ = 1.0;
   v2(2,1).d_ = 1.0;

  vector_fv output = multiply(v1, v2);
  EXPECT_EQ(2, output.size());
  EXPECT_FLOAT_EQ(-24, output(0).val_);
  EXPECT_FLOAT_EQ(  9, output(1).val_);
  EXPECT_FLOAT_EQ( -3, output(0).d_);
  EXPECT_FLOAT_EQ(  9, output(1).d_);

  output = multiply(v1, d2);
  EXPECT_EQ(2, output.size());
  EXPECT_FLOAT_EQ(-24, output(0).val_);
  EXPECT_FLOAT_EQ(  9, output(1).val_);
  EXPECT_FLOAT_EQ( -6, output(0).d_);
  EXPECT_FLOAT_EQ(  6, output(1).d_);
  
  output = multiply(d1, v2);
  EXPECT_EQ(2, output.size());
  EXPECT_FLOAT_EQ(-24, output(0).val_);
  EXPECT_FLOAT_EQ(  9, output(1).val_);
  EXPECT_FLOAT_EQ(  3, output(0).d_);
  EXPECT_FLOAT_EQ(  3, output(1).d_);
}
TEST(AgradFwdMatrix, multiply_rowvector_matrix_exception) {
  using stan::math::matrix_d;
  using stan::agrad::matrix_fv;
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_fv;

  row_vector_d d1(4);
  row_vector_fv v1(4);
  matrix_d d2(3,2);
  matrix_fv v2(3,2);
  EXPECT_THROW(multiply(v1, v2), std::domain_error);
  EXPECT_THROW(multiply(v1, d2), std::domain_error);
  EXPECT_THROW(multiply(d1, v2), std::domain_error);
}
TEST(AgradFwdMatrix, multiply_matrix_matrix) {
  using stan::math::matrix_d;
  using stan::agrad::matrix_fv;

  matrix_d d1(2,3);
  matrix_fv v1(2,3);
  matrix_d d2(3,2);
  matrix_fv v2(3,2);
  
  d1 << 9, 24, 3, 46, -9, -33;
  v1 << 9, 24, 3, 46, -9, -33;
   v1(0,0).d_ = 1.0;
   v1(0,1).d_ = 1.0;
   v1(0,2).d_ = 1.0;
   v1(1,0).d_ = 1.0;
   v1(1,1).d_ = 1.0;
   v1(1,2).d_ = 1.0;
  d2 << 1, 3, -5, 4, -2, -1;
  v2 << 1, 3, -5, 4, -2, -1;
   v2(0,0).d_ = 1.0;
   v2(0,1).d_ = 1.0;
   v2(1,0).d_ = 1.0;
   v2(1,1).d_ = 1.0;
   v2(2,0).d_ = 1.0;
   v2(2,1).d_ = 1.0;

  matrix_fv output = multiply(v1, v2);
  EXPECT_EQ(2, output.rows());
  EXPECT_EQ(2, output.cols());
  EXPECT_FLOAT_EQ(-117, output(0,0).val_);
  EXPECT_FLOAT_EQ( 120, output(0,1).val_);
  EXPECT_FLOAT_EQ( 157, output(1,0).val_);
  EXPECT_FLOAT_EQ( 135, output(1,1).val_);
  EXPECT_FLOAT_EQ(  30, output(0,0).d_);
  EXPECT_FLOAT_EQ(  42, output(0,1).d_);
  EXPECT_FLOAT_EQ(  -2, output(1,0).d_);
  EXPECT_FLOAT_EQ(  10, output(1,1).d_);

  output = multiply(v1, d2);
  EXPECT_EQ(2, output.rows());
  EXPECT_EQ(2, output.cols());
  EXPECT_FLOAT_EQ(-117, output(0,0).val_);
  EXPECT_FLOAT_EQ( 120, output(0,1).val_);
  EXPECT_FLOAT_EQ( 157, output(1,0).val_);
  EXPECT_FLOAT_EQ( 135, output(1,1).val_);
  EXPECT_FLOAT_EQ(  -6, output(0,0).d_);
  EXPECT_FLOAT_EQ(   6, output(0,1).d_);
  EXPECT_FLOAT_EQ(  -6, output(1,0).d_);
  EXPECT_FLOAT_EQ(   6, output(1,1).d_);
  
  output = multiply(d1, v2);
  EXPECT_EQ(2, output.rows());
  EXPECT_EQ(2, output.cols());
  EXPECT_FLOAT_EQ(-117, output(0,0).val_);
  EXPECT_FLOAT_EQ( 120, output(0,1).val_);
  EXPECT_FLOAT_EQ( 157, output(1,0).val_);
  EXPECT_FLOAT_EQ( 135, output(1,1).val_);
}
TEST(AgradFwdMatrix, multiply_matrix_matrix_exception) {
  using stan::math::matrix_d;
  using stan::agrad::matrix_fv;

  matrix_d d1(2,2);
  matrix_fv v1(2,2);
  matrix_d d2(3,2);
  matrix_fv v2(3,2);

  EXPECT_THROW(multiply(v1, v2), std::domain_error);
  EXPECT_THROW(multiply(v1, d2), std::domain_error);
  EXPECT_THROW(multiply(d1, v2), std::domain_error);
}
TEST(AgradFwdFvarVarMatrix, multiply_vector_scalar) {
  using stan::math::vector_d;
  using stan::agrad::vector_fvv;

  vector_d d1(3);
  vector_fvv v1(3);
  double d2;
  fvar<var> v2;
  
  d1 << 100, 0, -3;
  v1 << 100, 0, -3;
   v1(0).d_ = 1.0;  
   v1(1).d_ = 1.0;
   v1(2).d_ = 1.0;
  d2 = -2;
  v2 = -2;
   v2.d_ = 1.0;  

  vector_fvv output;
  output = multiply(d1, v2);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ( 100, output(0).d_.val());
  EXPECT_FLOAT_EQ(   0, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -3, output(2).d_.val());

  output = multiply(v2, d1);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ( 100, output(0).d_.val());
  EXPECT_FLOAT_EQ(   0, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -3, output(2).d_.val());

  output = multiply(v1, d2);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ(  -2, output(0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(2).d_.val());

  output = multiply(d2, v1);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ(  -2, output(0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(2).d_.val());

  output = multiply(v1, v2);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ(  98, output(0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -5, output(2).d_.val());

  output = multiply(v2, v1);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ(  98, output(0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -5, output(2).d_.val());
}

TEST(AgradFwdFvarVarMatrix, multiply_rowvector_scalar) {
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_fvv;

  row_vector_d d1(3);
  row_vector_fvv v1(3);
  double d2;
  fvar<var> v2;
  
  d1 << 100, 0, -3;
  v1 << 100, 0, -3;
   v1(0).d_ = 1.0;  
   v1(1).d_ = 1.0;
   v1(2).d_ = 1.0;
  d2 = -2;
  v2 = -2;
   v2.d_ = 1.0;
  
  row_vector_fvv output;
  output = multiply(d1, v2);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ( 100, output(0).d_.val());
  EXPECT_FLOAT_EQ(   0, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -3, output(2).d_.val());

  output = multiply(v1, d2);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ(  -2, output(0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(2).d_.val());

  output = multiply(v1, v2);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ(  98, output(0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -5, output(2).d_.val());

  output = multiply(v2, d1);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ( 100, output(0).d_.val());
  EXPECT_FLOAT_EQ(   0, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -3, output(2).d_.val());

  output = multiply(d2, v1);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ(  -2, output(0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(2).d_.val());

  output = multiply(v2, v1);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ(  98, output(0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -5, output(2).d_.val());
}
TEST(AgradFwdFvarVarMatrix, multiply_matrix_scalar) {
  using stan::math::matrix_d;
  using stan::agrad::matrix_fvv;
  
  matrix_d d1(2,2);
  matrix_fvv v1(2,2);
  double d2;
  fvar<var> v2;
  
  d1 << 100, 0, -3, 4;
  v1 << 100, 0, -3, 4;
   v1(0,0).d_ = 1.0; 
   v1(0,1).d_ = 1.0; 
   v1(1,0).d_ = 1.0; 
   v1(1,1).d_ = 1.0; 
  d2 = -2;
  v2 = -2;
   v2.d_ = 1.0;

  matrix_fvv output;
  output = multiply(d1, v2);
  EXPECT_FLOAT_EQ(-200, output(0,0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(0,1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(1,0).val_.val());
  EXPECT_FLOAT_EQ(  -8, output(1,1).val_.val());
  EXPECT_FLOAT_EQ( 100, output(0,0).d_.val());
  EXPECT_FLOAT_EQ(   0, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(  -3, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(   4, output(1,1).d_.val());

  output = multiply(v1, d2);
  EXPECT_FLOAT_EQ(-200, output(0,0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(0,1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(1,0).val_.val());
  EXPECT_FLOAT_EQ(  -8, output(1,1).val_.val());
  EXPECT_FLOAT_EQ(  -2, output(0,0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1,1).d_.val());
 
  output = multiply(v1, v2);
  EXPECT_FLOAT_EQ(-200, output(0,0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(0,1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(1,0).val_.val());
  EXPECT_FLOAT_EQ(  -8, output(1,1).val_.val());
  EXPECT_FLOAT_EQ(  98, output(0,0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(  -5, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(   2, output(1,1).d_.val());

  output = multiply(v2, d1);
  EXPECT_FLOAT_EQ(-200, output(0,0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(0,1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(1,0).val_.val());
  EXPECT_FLOAT_EQ(  -8, output(1,1).val_.val());
  EXPECT_FLOAT_EQ( 100, output(0,0).d_.val());
  EXPECT_FLOAT_EQ(   0, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(  -3, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(   4, output(1,1).d_.val());

  output = multiply(d2, v1);
  EXPECT_FLOAT_EQ(-200, output(0,0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(0,1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(1,0).val_.val());
  EXPECT_FLOAT_EQ(  -8, output(1,1).val_.val());
  EXPECT_FLOAT_EQ(  -2, output(0,0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1,1).d_.val());
 
  output = multiply(v2, v1);
  EXPECT_FLOAT_EQ(-200, output(0,0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(0,1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(1,0).val_.val());
  EXPECT_FLOAT_EQ(  -8, output(1,1).val_.val());
  EXPECT_FLOAT_EQ(  98, output(0,0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(  -5, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(   2, output(1,1).d_.val());
}
TEST(AgradFwdFvarVarMatrix, multiply_rowvector_vector) {
  using stan::math::vector_d;
  using stan::agrad::vector_fvv;
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_fvv;

  row_vector_d d1(3);
  row_vector_fvv v1(3);
  vector_d d2(3);
  vector_fvv v2(3);
  
  d1 << 1, 3, -5;
  v1 << 1, 3, -5;
   v1(0).d_ = 1.0;
   v1(1).d_ = 1.0;
   v1(2).d_ = 1.0;
  d2 << 4, -2, -1;
  v2 << 4, -2, -1;
   v2(0).d_ = 1.0;
   v2(1).d_ = 1.0;
   v2(2).d_ = 1.0;

  EXPECT_FLOAT_EQ( 3, multiply(v1, v2).val_.val());
  EXPECT_FLOAT_EQ( 3, multiply(v1, d2).val_.val());
  EXPECT_FLOAT_EQ( 3, multiply(d1, v2).val_.val());
  EXPECT_FLOAT_EQ( 0, multiply(v1, v2).d_.val());
  EXPECT_FLOAT_EQ( 1, multiply(v1 ,d2).d_.val());
  EXPECT_FLOAT_EQ(-1, multiply(d1 ,v2).d_.val());

  d1.resize(1);
  v1.resize(1);
  EXPECT_THROW(multiply(v1, v2), std::domain_error);
  EXPECT_THROW(multiply(v1, d2), std::domain_error);
  EXPECT_THROW(multiply(d1, v2), std::domain_error);
}
TEST(AgradFwdFvarVarMatrix, multiply_vector_rowvector) {
  using stan::agrad::matrix_fvv;
  using stan::math::vector_d;
  using stan::agrad::vector_fvv;
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_fvv;

  vector_d d1(3);
  vector_fvv v1(3);
  row_vector_d d2(3);
  row_vector_fvv v2(3);
  
  d1 << 1, 3, -5;
  v1 << 1, 3, -5;
   v1(0).d_ = 1.0;
   v1(1).d_ = 1.0;
   v1(2).d_ = 1.0;
  d2 << 4, -2, -1;
  v2 << 4, -2, -1;
   v2(0).d_ = 1.0;
   v2(1).d_ = 1.0;
   v2(2).d_ = 1.0;

  matrix_fvv output = multiply(v1, v2);
  EXPECT_EQ(3, output.rows());
  EXPECT_EQ(3, output.cols());
  EXPECT_FLOAT_EQ(  4, output(0,0).val_.val());
  EXPECT_FLOAT_EQ( -2, output(0,1).val_.val());
  EXPECT_FLOAT_EQ( -1, output(0,2).val_.val());
  EXPECT_FLOAT_EQ( 12, output(1,0).val_.val());
  EXPECT_FLOAT_EQ( -6, output(1,1).val_.val());
  EXPECT_FLOAT_EQ( -3, output(1,2).val_.val());
  EXPECT_FLOAT_EQ(-20, output(2,0).val_.val());  
  EXPECT_FLOAT_EQ( 10, output(2,1).val_.val());
  EXPECT_FLOAT_EQ(  5, output(2,2).val_.val());
  EXPECT_FLOAT_EQ(  5, output(0,0).d_.val());
  EXPECT_FLOAT_EQ( -1, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(  0, output(0,2).d_.val());
  EXPECT_FLOAT_EQ(  7, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(  1, output(1,1).d_.val());
  EXPECT_FLOAT_EQ(  2, output(1,2).d_.val());
  EXPECT_FLOAT_EQ( -1, output(2,0).d_.val());
  EXPECT_FLOAT_EQ( -7, output(2,1).d_.val());
  EXPECT_FLOAT_EQ( -6, output(2,2).d_.val());
  
  output = multiply(v1, d2);
  EXPECT_EQ(3, output.rows());
  EXPECT_EQ(3, output.cols());
  EXPECT_FLOAT_EQ(  4, output(0,0).val_.val());
  EXPECT_FLOAT_EQ( -2, output(0,1).val_.val());
  EXPECT_FLOAT_EQ( -1, output(0,2).val_.val());
  EXPECT_FLOAT_EQ( 12, output(1,0).val_.val());
  EXPECT_FLOAT_EQ( -6, output(1,1).val_.val());
  EXPECT_FLOAT_EQ( -3, output(1,2).val_.val());
  EXPECT_FLOAT_EQ(-20, output(2,0).val_.val());  
  EXPECT_FLOAT_EQ( 10, output(2,1).val_.val());
  EXPECT_FLOAT_EQ(  5, output(2,2).val_.val());
  EXPECT_FLOAT_EQ(  4, output(0,0).d_.val());
  EXPECT_FLOAT_EQ( -2, output(0,1).d_.val());
  EXPECT_FLOAT_EQ( -1, output(0,2).d_.val());
  EXPECT_FLOAT_EQ(  4, output(1,0).d_.val());
  EXPECT_FLOAT_EQ( -2, output(1,1).d_.val());
  EXPECT_FLOAT_EQ( -1, output(1,2).d_.val());
  EXPECT_FLOAT_EQ(  4, output(2,0).d_.val());
  EXPECT_FLOAT_EQ( -2, output(2,1).d_.val());
  EXPECT_FLOAT_EQ( -1, output(2,2).d_.val());
  
  output = multiply(d1, v2);
  EXPECT_EQ(3, output.rows());
  EXPECT_EQ(3, output.cols());
  EXPECT_FLOAT_EQ(  4, output(0,0).val_.val());
  EXPECT_FLOAT_EQ( -2, output(0,1).val_.val());
  EXPECT_FLOAT_EQ( -1, output(0,2).val_.val());
  EXPECT_FLOAT_EQ( 12, output(1,0).val_.val());
  EXPECT_FLOAT_EQ( -6, output(1,1).val_.val());
  EXPECT_FLOAT_EQ( -3, output(1,2).val_.val());
  EXPECT_FLOAT_EQ(-20, output(2,0).val_.val());  
  EXPECT_FLOAT_EQ( 10, output(2,1).val_.val());
  EXPECT_FLOAT_EQ(  5, output(2,2).val_.val());
  EXPECT_FLOAT_EQ(  1, output(0,0).d_.val());
  EXPECT_FLOAT_EQ(  1, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(  1, output(0,2).d_.val());
  EXPECT_FLOAT_EQ(  3, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(  3, output(1,1).d_.val());
  EXPECT_FLOAT_EQ(  3, output(1,2).d_.val());
  EXPECT_FLOAT_EQ( -5, output(2,0).d_.val());
  EXPECT_FLOAT_EQ( -5, output(2,1).d_.val());
  EXPECT_FLOAT_EQ( -5, output(2,2).d_.val());
}
TEST(AgradFwdFvarVarMatrix, multiply_matrix_vector) {
  using stan::math::matrix_d;
  using stan::agrad::matrix_fvv;
  using stan::math::vector_d;
  using stan::agrad::vector_fvv;

  matrix_d d1(3,2);
  matrix_fvv v1(3,2);
  vector_d d2(2);
  vector_fvv v2(2);
  
  d1 << 1, 3, -5, 4, -2, -1;
  v1 << 1, 3, -5, 4, -2, -1;
   v1(0,0).d_ = 1.0;
   v1(0,1).d_ = 1.0;
   v1(1,0).d_ = 1.0;
   v1(1,1).d_ = 1.0;
   v1(2,0).d_ = 1.0;
   v1(2,1).d_ = 1.0;
  d2 << -2, 4;
  v2 << -2, 4;
   v2(0).d_ = 1.0;
   v2(1).d_ = 1.0;

  vector_fvv output = multiply(v1, v2);
  EXPECT_EQ(3, output.size());
  EXPECT_FLOAT_EQ(10, output(0).val_.val());
  EXPECT_FLOAT_EQ(26, output(1).val_.val());
  EXPECT_FLOAT_EQ( 0, output(2).val_.val());
  EXPECT_FLOAT_EQ( 6, output(0).d_.val());
  EXPECT_FLOAT_EQ( 1, output(1).d_.val());
  EXPECT_FLOAT_EQ(-1, output(2).d_.val());
  
  output = multiply(v1, d2);
  EXPECT_EQ(3, output.size());
  EXPECT_FLOAT_EQ(10, output(0).val_.val());
  EXPECT_FLOAT_EQ(26, output(1).val_.val());
  EXPECT_FLOAT_EQ( 0, output(2).val_.val());
  EXPECT_FLOAT_EQ( 2, output(0).d_.val());
  EXPECT_FLOAT_EQ( 2, output(1).d_.val());
  EXPECT_FLOAT_EQ( 2, output(2).d_.val());
  
  output = multiply(d1, v2);
  EXPECT_EQ(3, output.size());
  EXPECT_FLOAT_EQ(10, output(0).val_.val());
  EXPECT_FLOAT_EQ(26, output(1).val_.val());
  EXPECT_FLOAT_EQ( 0, output(2).val_.val());
  EXPECT_FLOAT_EQ( 4, output(0).d_.val());
  EXPECT_FLOAT_EQ(-1, output(1).d_.val());
  EXPECT_FLOAT_EQ(-3, output(2).d_.val());
}
TEST(AgradFwdFvarVarMatrix, multiply_matrix_vector_exception) {
  using stan::math::matrix_d;
  using stan::agrad::matrix_fvv;
  using stan::math::vector_d;
  using stan::agrad::vector_fvv;

  matrix_d d1(3,2);
  matrix_fvv v1(3,2);
  vector_d d2(4);
  vector_fvv v2(4);
  EXPECT_THROW(multiply(v1, v2), std::domain_error);
  EXPECT_THROW(multiply(v1, d2), std::domain_error);
  EXPECT_THROW(multiply(d1, v2), std::domain_error);
}
TEST(AgradFwdFvarVarMatrix, multiply_rowvector_matrix) {
  using stan::math::matrix_d;
  using stan::agrad::matrix_fvv;
  using stan::agrad::vector_fvv;
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_fvv;

  row_vector_d d1(3);
  row_vector_fvv v1(3);
  matrix_d d2(3,2);
  matrix_fvv v2(3,2);
  
  d1 << -2, 4, 1;
  v1 << -2, 4, 1;
   v1(0).d_ = 1.0;
   v1(1).d_ = 1.0;
   v1(2).d_ = 1.0;
  d2 << 1, 3, -5, 4, -2, -1;
  v2 << 1, 3, -5, 4, -2, -1;
   v2(0,0).d_ = 1.0;
   v2(0,1).d_ = 1.0;
   v2(1,0).d_ = 1.0;
   v2(1,1).d_ = 1.0;
   v2(2,0).d_ = 1.0;
   v2(2,1).d_ = 1.0;

  vector_fvv output = multiply(v1, v2);
  EXPECT_EQ(2, output.size());
  EXPECT_FLOAT_EQ(-24, output(0).val_.val());
  EXPECT_FLOAT_EQ(  9, output(1).val_.val());
  EXPECT_FLOAT_EQ( -3, output(0).d_.val());
  EXPECT_FLOAT_EQ(  9, output(1).d_.val());

  output = multiply(v1, d2);
  EXPECT_EQ(2, output.size());
  EXPECT_FLOAT_EQ(-24, output(0).val_.val());
  EXPECT_FLOAT_EQ(  9, output(1).val_.val());
  EXPECT_FLOAT_EQ( -6, output(0).d_.val());
  EXPECT_FLOAT_EQ(  6, output(1).d_.val());
  
  output = multiply(d1, v2);
  EXPECT_EQ(2, output.size());
  EXPECT_FLOAT_EQ(-24, output(0).val_.val());
  EXPECT_FLOAT_EQ(  9, output(1).val_.val());
  EXPECT_FLOAT_EQ(  3, output(0).d_.val());
  EXPECT_FLOAT_EQ(  3, output(1).d_.val());
}
TEST(AgradFwdFvarVarMatrix, multiply_rowvector_matrix_exception) {
  using stan::math::matrix_d;
  using stan::agrad::matrix_fvv;
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_fvv;

  row_vector_d d1(4);
  row_vector_fvv v1(4);
  matrix_d d2(3,2);
  matrix_fvv v2(3,2);
  EXPECT_THROW(multiply(v1, v2), std::domain_error);
  EXPECT_THROW(multiply(v1, d2), std::domain_error);
  EXPECT_THROW(multiply(d1, v2), std::domain_error);
}
TEST(AgradFwdFvarVarMatrix, multiply_matrix_matrix) {
  using stan::math::matrix_d;
  using stan::agrad::matrix_fvv;

  matrix_d d1(2,3);
  matrix_fvv v1(2,3);
  matrix_d d2(3,2);
  matrix_fvv v2(3,2);
  
  d1 << 9, 24, 3, 46, -9, -33;
  v1 << 9, 24, 3, 46, -9, -33;
   v1(0,0).d_ = 1.0;
   v1(0,1).d_ = 1.0;
   v1(0,2).d_ = 1.0;
   v1(1,0).d_ = 1.0;
   v1(1,1).d_ = 1.0;
   v1(1,2).d_ = 1.0;
  d2 << 1, 3, -5, 4, -2, -1;
  v2 << 1, 3, -5, 4, -2, -1;
   v2(0,0).d_ = 1.0;
   v2(0,1).d_ = 1.0;
   v2(1,0).d_ = 1.0;
   v2(1,1).d_ = 1.0;
   v2(2,0).d_ = 1.0;
   v2(2,1).d_ = 1.0;

  matrix_fvv output = multiply(v1, v2);
  EXPECT_EQ(2, output.rows());
  EXPECT_EQ(2, output.cols());
  EXPECT_FLOAT_EQ(-117, output(0,0).val_.val());
  EXPECT_FLOAT_EQ( 120, output(0,1).val_.val());
  EXPECT_FLOAT_EQ( 157, output(1,0).val_.val());
  EXPECT_FLOAT_EQ( 135, output(1,1).val_.val());
  EXPECT_FLOAT_EQ(  30, output(0,0).d_.val());
  EXPECT_FLOAT_EQ(  42, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(  10, output(1,1).d_.val());

  output = multiply(v1, d2);
  EXPECT_EQ(2, output.rows());
  EXPECT_EQ(2, output.cols());
  EXPECT_FLOAT_EQ(-117, output(0,0).val_.val());
  EXPECT_FLOAT_EQ( 120, output(0,1).val_.val());
  EXPECT_FLOAT_EQ( 157, output(1,0).val_.val());
  EXPECT_FLOAT_EQ( 135, output(1,1).val_.val());
  EXPECT_FLOAT_EQ(  -6, output(0,0).d_.val());
  EXPECT_FLOAT_EQ(   6, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(  -6, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(   6, output(1,1).d_.val());
  
  output = multiply(d1, v2);
  EXPECT_EQ(2, output.rows());
  EXPECT_EQ(2, output.cols());
  EXPECT_FLOAT_EQ(-117, output(0,0).val_.val());
  EXPECT_FLOAT_EQ( 120, output(0,1).val_.val());
  EXPECT_FLOAT_EQ( 157, output(1,0).val_.val());
  EXPECT_FLOAT_EQ( 135, output(1,1).val_.val());
}
TEST(AgradFwdFvarVarMatrix, multiply_matrix_matrix_exception) {
  using stan::math::matrix_d;
  using stan::agrad::matrix_fvv;

  matrix_d d1(2,2);
  matrix_fvv v1(2,2);
  matrix_d d2(3,2);
  matrix_fvv v2(3,2);

  EXPECT_THROW(multiply(v1, v2), std::domain_error);
  EXPECT_THROW(multiply(v1, d2), std::domain_error);
  EXPECT_THROW(multiply(d1, v2), std::domain_error);
}
TEST(AgradFwdFvarFvarMatrix, multiply_vector_scalar) {
  using stan::math::vector_d;
  using stan::agrad::vector_ffv;

  vector_d d1(3);
  vector_ffv v1(3);
  double d2;
  fvar<fvar<double> > v2;
  
  fvar<fvar<double> > a,b,c;
  a.val_.val_ = 100.0;
  b.val_.val_ = 0.0;
  c.val_.val_ = -3.0;
  a.d_.val_ = 1.0;
  b.d_.val_ = 1.0;
  c.d_.val_ = 1.0;

  d1 << 100, 0, -3;
  v1 << a,b,c;
  d2 = -2;
  v2.val_.val_ = -2;
  v2.d_.val_ = 1.0;  

  vector_ffv output;
  output = multiply(d1, v2);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ( 100, output(0).d_.val());
  EXPECT_FLOAT_EQ(   0, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -3, output(2).d_.val());

  output = multiply(v2, d1);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ( 100, output(0).d_.val());
  EXPECT_FLOAT_EQ(   0, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -3, output(2).d_.val());

  output = multiply(v1, d2);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ(  -2, output(0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(2).d_.val());

  output = multiply(d2, v1);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ(  -2, output(0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(2).d_.val());

  output = multiply(v1, v2);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ(  98, output(0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -5, output(2).d_.val());

  output = multiply(v2, v1);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ(  98, output(0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -5, output(2).d_.val());
}

TEST(AgradFwdFvarFvarMatrix, multiply_rowvector_scalar) {
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_ffv;

  row_vector_d d1(3);
  row_vector_ffv v1(3);
  double d2;
  fvar<fvar<double> > v2;
  
  fvar<fvar<double> > a,b,c;
  a.val_.val_ = 100.0;
  b.val_.val_ = 0.0;
  c.val_.val_ = -3.0;
  a.d_.val_ = 1.0;
  b.d_.val_ = 1.0;
  c.d_.val_ = 1.0;

  d1 << 100, 0, -3;
  v1 << a,b,c;
  d2 = -2;
  v2.val_.val_ = -2;
  v2.d_.val_ = 1.0;
  
  row_vector_ffv output;
  output = multiply(d1, v2);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ( 100, output(0).d_.val());
  EXPECT_FLOAT_EQ(   0, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -3, output(2).d_.val());

  output = multiply(v1, d2);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ(  -2, output(0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(2).d_.val());

  output = multiply(v1, v2);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ(  98, output(0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -5, output(2).d_.val());

  output = multiply(v2, d1);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ( 100, output(0).d_.val());
  EXPECT_FLOAT_EQ(   0, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -3, output(2).d_.val());

  output = multiply(d2, v1);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ(  -2, output(0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(2).d_.val());

  output = multiply(v2, v1);
  EXPECT_FLOAT_EQ(-200, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(2).val_.val());
  EXPECT_FLOAT_EQ(  98, output(0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1).d_.val());
  EXPECT_FLOAT_EQ(  -5, output(2).d_.val());
}
TEST(AgradFwdFvarFvarMatrix, multiply_matrix_scalar) {
  using stan::math::matrix_d;
  using stan::agrad::matrix_ffv;
  
  matrix_d d1(2,2);
  matrix_ffv v1(2,2);
  double d2;
  fvar<fvar<double> > v2;

  fvar<fvar<double> > a,b,c,d,e;
  a.val_.val_ = 100.0;
  b.val_.val_ = 0.0;
  c.val_.val_ = -3.0;
  d.val_.val_ = 4.0;
  e.val_.val_ = -2.0;
  a.d_.val_ = 1.0;
  b.d_.val_ = 1.0;
  c.d_.val_ = 1.0;
  d.d_.val_ = 1.0;
  e.d_.val_ = 1.0;

  d1 << 100, 0, -3, 4;
  v1 << a,b,c,d;
  d2 = -2;
  v2 = e;

  matrix_ffv output;
  output = multiply(d1, v2);
  EXPECT_FLOAT_EQ(-200, output(0,0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(0,1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(1,0).val_.val());
  EXPECT_FLOAT_EQ(  -8, output(1,1).val_.val());
  EXPECT_FLOAT_EQ( 100, output(0,0).d_.val());
  EXPECT_FLOAT_EQ(   0, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(  -3, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(   4, output(1,1).d_.val());

  output = multiply(v1, d2);
  EXPECT_FLOAT_EQ(-200, output(0,0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(0,1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(1,0).val_.val());
  EXPECT_FLOAT_EQ(  -8, output(1,1).val_.val());
  EXPECT_FLOAT_EQ(  -2, output(0,0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1,1).d_.val());
 
  output = multiply(v1, v2);
  EXPECT_FLOAT_EQ(-200, output(0,0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(0,1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(1,0).val_.val());
  EXPECT_FLOAT_EQ(  -8, output(1,1).val_.val());
  EXPECT_FLOAT_EQ(  98, output(0,0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(  -5, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(   2, output(1,1).d_.val());

  output = multiply(v2, d1);
  EXPECT_FLOAT_EQ(-200, output(0,0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(0,1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(1,0).val_.val());
  EXPECT_FLOAT_EQ(  -8, output(1,1).val_.val());
  EXPECT_FLOAT_EQ( 100, output(0,0).d_.val());
  EXPECT_FLOAT_EQ(   0, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(  -3, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(   4, output(1,1).d_.val());

  output = multiply(d2, v1);
  EXPECT_FLOAT_EQ(-200, output(0,0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(0,1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(1,0).val_.val());
  EXPECT_FLOAT_EQ(  -8, output(1,1).val_.val());
  EXPECT_FLOAT_EQ(  -2, output(0,0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1,1).d_.val());
 
  output = multiply(v2, v1);
  EXPECT_FLOAT_EQ(-200, output(0,0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(0,1).val_.val());
  EXPECT_FLOAT_EQ(   6, output(1,0).val_.val());
  EXPECT_FLOAT_EQ(  -8, output(1,1).val_.val());
  EXPECT_FLOAT_EQ(  98, output(0,0).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(  -5, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(   2, output(1,1).d_.val());
}
TEST(AgradFwdFvarFvarMatrix, multiply_rowvector_vector) {
  using stan::math::vector_d;
  using stan::agrad::vector_ffv;
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_ffv;

  row_vector_d d1(3);
  row_vector_ffv v1(3);
  vector_d d2(3);
  vector_ffv v2(3);
  
  fvar<fvar<double> > a,b,c,d,e,f;
  a.val_.val_ = -2.0;
  b.val_.val_ = 4.0;
  c.val_.val_ = 1.0;
  d.val_.val_ = 3.0;
  e.val_.val_ = -5.0;
  f.val_.val_ = -1.0;
  a.d_.val_ = 1.0;
  b.d_.val_ = 1.0;
  c.d_.val_ = 1.0;
  d.d_.val_ = 1.0;
  e.d_.val_ = 1.0;
  f.d_.val_ = 1.0;

  d1 << 1, 3, -5;
  v1 << c,d,e;
  d2 << 4, -2, -1;
  v2 << b,a,f;

  EXPECT_FLOAT_EQ( 3, multiply(v1, v2).val_.val());
  EXPECT_FLOAT_EQ( 3, multiply(v1, d2).val_.val());
  EXPECT_FLOAT_EQ( 3, multiply(d1, v2).val_.val());
  EXPECT_FLOAT_EQ( 0, multiply(v1, v2).d_.val());
  EXPECT_FLOAT_EQ( 1, multiply(v1 ,d2).d_.val());
  EXPECT_FLOAT_EQ(-1, multiply(d1 ,v2).d_.val());

  d1.resize(1);
  v1.resize(1);
  EXPECT_THROW(multiply(v1, v2), std::domain_error);
  EXPECT_THROW(multiply(v1, d2), std::domain_error);
  EXPECT_THROW(multiply(d1, v2), std::domain_error);
}
TEST(AgradFwdFvarFvarMatrix, multiply_vector_rowvector) {
  using stan::agrad::matrix_ffv;
  using stan::math::vector_d;
  using stan::agrad::vector_ffv;
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_ffv;

  vector_d d1(3);
  vector_ffv v1(3);
  row_vector_d d2(3);
  row_vector_ffv v2(3);
  
  fvar<fvar<double> > a,b,c,d,e,f;
  a.val_.val_ = -2.0;
  b.val_.val_ = 4.0;
  c.val_.val_ = 1.0;
  d.val_.val_ = 3.0;
  e.val_.val_ = -5.0;
  f.val_.val_ = -1.0;
  a.d_.val_ = 1.0;
  b.d_.val_ = 1.0;
  c.d_.val_ = 1.0;
  d.d_.val_ = 1.0;
  e.d_.val_ = 1.0;
  f.d_.val_ = 1.0;

  d1 << 1, 3, -5;
  v1 << c,d,e;
  d2 << 4, -2, -1;
  v2 << b,a,f;

  matrix_ffv output = multiply(v1, v2);
  EXPECT_EQ(3, output.rows());
  EXPECT_EQ(3, output.cols());
  EXPECT_FLOAT_EQ(  4, output(0,0).val_.val());
  EXPECT_FLOAT_EQ( -2, output(0,1).val_.val());
  EXPECT_FLOAT_EQ( -1, output(0,2).val_.val());
  EXPECT_FLOAT_EQ( 12, output(1,0).val_.val());
  EXPECT_FLOAT_EQ( -6, output(1,1).val_.val());
  EXPECT_FLOAT_EQ( -3, output(1,2).val_.val());
  EXPECT_FLOAT_EQ(-20, output(2,0).val_.val());  
  EXPECT_FLOAT_EQ( 10, output(2,1).val_.val());
  EXPECT_FLOAT_EQ(  5, output(2,2).val_.val());
  EXPECT_FLOAT_EQ(  5, output(0,0).d_.val());
  EXPECT_FLOAT_EQ( -1, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(  0, output(0,2).d_.val());
  EXPECT_FLOAT_EQ(  7, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(  1, output(1,1).d_.val());
  EXPECT_FLOAT_EQ(  2, output(1,2).d_.val());
  EXPECT_FLOAT_EQ( -1, output(2,0).d_.val());
  EXPECT_FLOAT_EQ( -7, output(2,1).d_.val());
  EXPECT_FLOAT_EQ( -6, output(2,2).d_.val());
  
  output = multiply(v1, d2);
  EXPECT_EQ(3, output.rows());
  EXPECT_EQ(3, output.cols());
  EXPECT_FLOAT_EQ(  4, output(0,0).val_.val());
  EXPECT_FLOAT_EQ( -2, output(0,1).val_.val());
  EXPECT_FLOAT_EQ( -1, output(0,2).val_.val());
  EXPECT_FLOAT_EQ( 12, output(1,0).val_.val());
  EXPECT_FLOAT_EQ( -6, output(1,1).val_.val());
  EXPECT_FLOAT_EQ( -3, output(1,2).val_.val());
  EXPECT_FLOAT_EQ(-20, output(2,0).val_.val());  
  EXPECT_FLOAT_EQ( 10, output(2,1).val_.val());
  EXPECT_FLOAT_EQ(  5, output(2,2).val_.val());
  EXPECT_FLOAT_EQ(  4, output(0,0).d_.val());
  EXPECT_FLOAT_EQ( -2, output(0,1).d_.val());
  EXPECT_FLOAT_EQ( -1, output(0,2).d_.val());
  EXPECT_FLOAT_EQ(  4, output(1,0).d_.val());
  EXPECT_FLOAT_EQ( -2, output(1,1).d_.val());
  EXPECT_FLOAT_EQ( -1, output(1,2).d_.val());
  EXPECT_FLOAT_EQ(  4, output(2,0).d_.val());
  EXPECT_FLOAT_EQ( -2, output(2,1).d_.val());
  EXPECT_FLOAT_EQ( -1, output(2,2).d_.val());
  
  output = multiply(d1, v2);
  EXPECT_EQ(3, output.rows());
  EXPECT_EQ(3, output.cols());
  EXPECT_FLOAT_EQ(  4, output(0,0).val_.val());
  EXPECT_FLOAT_EQ( -2, output(0,1).val_.val());
  EXPECT_FLOAT_EQ( -1, output(0,2).val_.val());
  EXPECT_FLOAT_EQ( 12, output(1,0).val_.val());
  EXPECT_FLOAT_EQ( -6, output(1,1).val_.val());
  EXPECT_FLOAT_EQ( -3, output(1,2).val_.val());
  EXPECT_FLOAT_EQ(-20, output(2,0).val_.val());  
  EXPECT_FLOAT_EQ( 10, output(2,1).val_.val());
  EXPECT_FLOAT_EQ(  5, output(2,2).val_.val());
  EXPECT_FLOAT_EQ(  1, output(0,0).d_.val());
  EXPECT_FLOAT_EQ(  1, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(  1, output(0,2).d_.val());
  EXPECT_FLOAT_EQ(  3, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(  3, output(1,1).d_.val());
  EXPECT_FLOAT_EQ(  3, output(1,2).d_.val());
  EXPECT_FLOAT_EQ( -5, output(2,0).d_.val());
  EXPECT_FLOAT_EQ( -5, output(2,1).d_.val());
  EXPECT_FLOAT_EQ( -5, output(2,2).d_.val());
}
TEST(AgradFwdFvarFvarMatrix, multiply_matrix_vector) {
  using stan::math::matrix_d;
  using stan::agrad::matrix_ffv;
  using stan::math::vector_d;
  using stan::agrad::vector_ffv;

  matrix_d d1(3,2);
  matrix_ffv v1(3,2);
  vector_d d2(2);
  vector_ffv v2(2);
  
  fvar<fvar<double> > a,b,c,d,e,f;
  a.val_.val_ = -2.0;
  b.val_.val_ = 4.0;
  c.val_.val_ = 1.0;
  d.val_.val_ = 3.0;
  e.val_.val_ = -5.0;
  f.val_.val_ = -1.0;
  a.d_.val_ = 1.0;
  b.d_.val_ = 1.0;
  c.d_.val_ = 1.0;
  d.d_.val_ = 1.0;
  e.d_.val_ = 1.0;
  f.d_.val_ = 1.0;

  d1 << 1, 3, -5, 4, -2, -1;
  v1 << c,d,e,b,a,f;
  d2 << -2, 4;
  v2 << a,b;

  vector_ffv output = multiply(v1, v2);
  EXPECT_EQ(3, output.size());
  EXPECT_FLOAT_EQ(10, output(0).val_.val());
  EXPECT_FLOAT_EQ(26, output(1).val_.val());
  EXPECT_FLOAT_EQ( 0, output(2).val_.val());
  EXPECT_FLOAT_EQ( 6, output(0).d_.val());
  EXPECT_FLOAT_EQ( 1, output(1).d_.val());
  EXPECT_FLOAT_EQ(-1, output(2).d_.val());
  
  output = multiply(v1, d2);
  EXPECT_EQ(3, output.size());
  EXPECT_FLOAT_EQ(10, output(0).val_.val());
  EXPECT_FLOAT_EQ(26, output(1).val_.val());
  EXPECT_FLOAT_EQ( 0, output(2).val_.val());
  EXPECT_FLOAT_EQ( 2, output(0).d_.val());
  EXPECT_FLOAT_EQ( 2, output(1).d_.val());
  EXPECT_FLOAT_EQ( 2, output(2).d_.val());
  
  output = multiply(d1, v2);
  EXPECT_EQ(3, output.size());
  EXPECT_FLOAT_EQ(10, output(0).val_.val());
  EXPECT_FLOAT_EQ(26, output(1).val_.val());
  EXPECT_FLOAT_EQ( 0, output(2).val_.val());
  EXPECT_FLOAT_EQ( 4, output(0).d_.val());
  EXPECT_FLOAT_EQ(-1, output(1).d_.val());
  EXPECT_FLOAT_EQ(-3, output(2).d_.val());
}
TEST(AgradFwdFvarFvarMatrix, multiply_matrix_vector_exception) {
  using stan::math::matrix_d;
  using stan::agrad::matrix_ffv;
  using stan::math::vector_d;
  using stan::agrad::vector_ffv;

  matrix_d d1(3,2);
  matrix_ffv v1(3,2);
  vector_d d2(4);
  vector_ffv v2(4);
  EXPECT_THROW(multiply(v1, v2), std::domain_error);
  EXPECT_THROW(multiply(v1, d2), std::domain_error);
  EXPECT_THROW(multiply(d1, v2), std::domain_error);
}
TEST(AgradFwdFvarFvarMatrix, multiply_rowvector_matrix) {
  using stan::math::matrix_d;
  using stan::agrad::matrix_ffv;
  using stan::agrad::vector_ffv;
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_ffv;

  row_vector_d d1(3);
  row_vector_ffv v1(3);
  matrix_d d2(3,2);
  matrix_ffv v2(3,2);
  
  fvar<fvar<double> > a,b,c,d,e,f;
  a.val_.val_ = -2.0;
  b.val_.val_ = 4.0;
  c.val_.val_ = 1.0;
  d.val_.val_ = 3.0;
  e.val_.val_ = -5.0;
  f.val_.val_ = -1.0;
  a.d_.val_ = 1.0;
  b.d_.val_ = 1.0;
  c.d_.val_ = 1.0;
  d.d_.val_ = 1.0;
  e.d_.val_ = 1.0;
  f.d_.val_ = 1.0;

  d1 << -2, 4, 1;
  v1 << a,b,c;
  d2 << 1, 3, -5, 4, -2, -1;
  v2 << c,d,e,b,a,f;

  vector_ffv output = multiply(v1, v2);
  EXPECT_EQ(2, output.size());
  EXPECT_FLOAT_EQ(-24, output(0).val_.val());
  EXPECT_FLOAT_EQ(  9, output(1).val_.val());
  EXPECT_FLOAT_EQ( -3, output(0).d_.val());
  EXPECT_FLOAT_EQ(  9, output(1).d_.val());

  output = multiply(v1, d2);
  EXPECT_EQ(2, output.size());
  EXPECT_FLOAT_EQ(-24, output(0).val_.val());
  EXPECT_FLOAT_EQ(  9, output(1).val_.val());
  EXPECT_FLOAT_EQ( -6, output(0).d_.val());
  EXPECT_FLOAT_EQ(  6, output(1).d_.val());
  
  output = multiply(d1, v2);
  EXPECT_EQ(2, output.size());
  EXPECT_FLOAT_EQ(-24, output(0).val_.val());
  EXPECT_FLOAT_EQ(  9, output(1).val_.val());
  EXPECT_FLOAT_EQ(  3, output(0).d_.val());
  EXPECT_FLOAT_EQ(  3, output(1).d_.val());
}
TEST(AgradFwdFvarFvarMatrix, multiply_rowvector_matrix_exception) {
  using stan::math::matrix_d;
  using stan::agrad::matrix_ffv;
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_ffv;

  row_vector_d d1(4);
  row_vector_ffv v1(4);
  matrix_d d2(3,2);
  matrix_ffv v2(3,2);
  EXPECT_THROW(multiply(v1, v2), std::domain_error);
  EXPECT_THROW(multiply(v1, d2), std::domain_error);
  EXPECT_THROW(multiply(d1, v2), std::domain_error);
}
TEST(AgradFwdFvarFvarMatrix, multiply_matrix_matrix) {
  using stan::math::matrix_d;
  using stan::agrad::matrix_ffv;

  matrix_d d1(2,3);
  matrix_ffv v1(2,3);
  matrix_d d2(3,2);
  matrix_ffv v2(3,2);
  
  fvar<fvar<double> > a,b,c,d,e,f,g,h,i,j,k,l;
  a.val_.val_ = 9.0;
  b.val_.val_ = 24.0;
  c.val_.val_ = 3.0;
  d.val_.val_ = 46.0;
  e.val_.val_ = -9.0;
  f.val_.val_ = -33.0;
  g.val_.val_ = 1.0;
  h.val_.val_ = 3.0;
  i.val_.val_ = -5.0;
  j.val_.val_ = 4.0;
  k.val_.val_ = -2.0;
  l.val_.val_ = -1.0;
  a.d_.val_ = 1.0;
  b.d_.val_ = 1.0;
  c.d_.val_ = 1.0;
  d.d_.val_ = 1.0;
  e.d_.val_ = 1.0;
  f.d_.val_ = 1.0;
  g.d_.val_ = 1.0;
  h.d_.val_ = 1.0;
  i.d_.val_ = 1.0;
  j.d_.val_ = 1.0;
  k.d_.val_ = 1.0;
  l.d_.val_ = 1.0;

  d1 << 9, 24, 3, 46, -9, -33;
  v1 << a,b,c,d,e,f;
  d2 << 1, 3, -5, 4, -2, -1;
  v2 << g,h,i,j,k,l;

  matrix_ffv output = multiply(v1, v2);
  EXPECT_EQ(2, output.rows());
  EXPECT_EQ(2, output.cols());
  EXPECT_FLOAT_EQ(-117, output(0,0).val_.val());
  EXPECT_FLOAT_EQ( 120, output(0,1).val_.val());
  EXPECT_FLOAT_EQ( 157, output(1,0).val_.val());
  EXPECT_FLOAT_EQ( 135, output(1,1).val_.val());
  EXPECT_FLOAT_EQ(  30, output(0,0).d_.val());
  EXPECT_FLOAT_EQ(  42, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(  -2, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(  10, output(1,1).d_.val());

  output = multiply(v1, d2);
  EXPECT_EQ(2, output.rows());
  EXPECT_EQ(2, output.cols());
  EXPECT_FLOAT_EQ(-117, output(0,0).val_.val());
  EXPECT_FLOAT_EQ( 120, output(0,1).val_.val());
  EXPECT_FLOAT_EQ( 157, output(1,0).val_.val());
  EXPECT_FLOAT_EQ( 135, output(1,1).val_.val());
  EXPECT_FLOAT_EQ(  -6, output(0,0).d_.val());
  EXPECT_FLOAT_EQ(   6, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(  -6, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(   6, output(1,1).d_.val());
  
  output = multiply(d1, v2);
  EXPECT_EQ(2, output.rows());
  EXPECT_EQ(2, output.cols());
  EXPECT_FLOAT_EQ(-117, output(0,0).val_.val());
  EXPECT_FLOAT_EQ( 120, output(0,1).val_.val());
  EXPECT_FLOAT_EQ( 157, output(1,0).val_.val());
  EXPECT_FLOAT_EQ( 135, output(1,1).val_.val());
}
TEST(AgradFwdFvarFvarMatrix, multiply_matrix_matrix_exception) {
  using stan::math::matrix_d;
  using stan::agrad::matrix_ffv;

  matrix_d d1(2,2);
  matrix_ffv v1(2,2);
  matrix_d d2(3,2);
  matrix_ffv v2(3,2);

  EXPECT_THROW(multiply(v1, v2), std::domain_error);
  EXPECT_THROW(multiply(v1, d2), std::domain_error);
  EXPECT_THROW(multiply(d1, v2), std::domain_error);
}
