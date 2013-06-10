#include <stan/agrad/fwd/matrix/divide.hpp>
#include <gtest/gtest.h>
#include <stan/agrad/fwd/fvar.hpp>
#include <stan/math/matrix/divide.hpp>
#include <stan/agrad/var.hpp>

using stan::agrad::fvar;
using stan::agrad::var;
TEST(AgradFwdMatrix, divide_scalar) {
  using stan::agrad::divide;
  double d1, d2;
  fvar<double>   v1, v2;

  d1 = 10;
  v1 = 10;
   v1.d_ = 1.0;
  d2 = -2;
  v2 = -2;
   v2.d_ = 1.0;
  
  EXPECT_FLOAT_EQ(  -5, divide(d1, d2));
  EXPECT_FLOAT_EQ(  -5, divide(d1, v2).val_);
  EXPECT_FLOAT_EQ(  -5, divide(v1, d2).val_);
  EXPECT_FLOAT_EQ(  -5, divide(v1, v2).val_);
  EXPECT_FLOAT_EQ(-2.5, divide(d1, v2).d_);
  EXPECT_FLOAT_EQ(-0.5, divide(v1, d2).d_);
  EXPECT_FLOAT_EQ(  -3, divide(v1, v2).d_);

  d2 = 0;
  v2 = 0;

  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), divide(d1, d2));
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), divide(d1, v2).val_);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), divide(v1, d2).val_);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), divide(v1, v2).val_);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), divide(v1, d2).d_);
  EXPECT_TRUE(std::isnan(divide(d1, v2).d_));
  EXPECT_TRUE(std::isnan(divide(v1, v2).d_));

  d1 = 0;
  v1 = 0;
  EXPECT_TRUE(std::isnan(divide(d1, d2)));
  EXPECT_TRUE(std::isnan(divide(d1, v2).val_));
  EXPECT_TRUE(std::isnan(divide(v1, d2).val_));
  EXPECT_TRUE(std::isnan(divide(v1, v2).val_));
  EXPECT_TRUE(std::isnan(divide(d1, v2).d_));
  EXPECT_TRUE(std::isnan(divide(v1, d2).d_));
  EXPECT_TRUE(std::isnan(divide(v1, v2).d_));
}
TEST(AgradFwdMatrix, divide_vector) {
  using stan::math::divide;
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
  
  vector_d output_d;
  output_d = divide(d1, d2);
  EXPECT_FLOAT_EQ(-50, output_d(0));
  EXPECT_FLOAT_EQ(  0, output_d(1));
  EXPECT_FLOAT_EQ(1.5, output_d(2));

  vector_fv output;
  output = divide(d1, v2);
  EXPECT_FLOAT_EQ( -50, output(0).val_);
  EXPECT_FLOAT_EQ(   0, output(1).val_);
  EXPECT_FLOAT_EQ( 1.5, output(2).val_);
  EXPECT_FLOAT_EQ( -25, output(0).d_);
  EXPECT_FLOAT_EQ(   0, output(1).d_);
  EXPECT_FLOAT_EQ(0.75, output(2).d_);

  output = divide(v1, d2);
  EXPECT_FLOAT_EQ(  -50, output(0).val_);
  EXPECT_FLOAT_EQ(    0, output(1).val_);
  EXPECT_FLOAT_EQ(  1.5, output(2).val_);
  EXPECT_FLOAT_EQ( -0.5, output(0).d_);
  EXPECT_FLOAT_EQ( -0.5, output(1).d_);
  EXPECT_FLOAT_EQ( -0.5, output(2).d_);

  output = divide(v1, v2);
  EXPECT_FLOAT_EQ( -50, output(0).val_);
  EXPECT_FLOAT_EQ(   0, output(1).val_);
  EXPECT_FLOAT_EQ( 1.5, output(2).val_);
  EXPECT_FLOAT_EQ(-25.5, output(0).d_);
  EXPECT_FLOAT_EQ( -0.5, output(1).d_);
  EXPECT_FLOAT_EQ( 0.25, output(2).d_);

  d2 = 0;
  v2 = 0;
  output_d = divide(d1, d2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output_d(0));
  EXPECT_TRUE (std::isnan(output_d(1)));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), output_d(2));

  output = divide(d1, v2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(0).val_);
  EXPECT_TRUE (std::isnan(output(1).val_));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), output(2).val_);
  EXPECT_TRUE (std::isnan(output(0).d_));
  EXPECT_TRUE (std::isnan(output(1).d_));
  EXPECT_TRUE (std::isnan(output(2).d_));

  output = divide(v1, d2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(0).val_);
  EXPECT_TRUE (std::isnan(output(1).val_));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), output(2).val_);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(0).d_);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(1).d_);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(2).d_);

  output = divide(v1, v2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(0).val_);
  EXPECT_TRUE (std::isnan(output(1).val_));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), output(2).val_);
  EXPECT_TRUE (std::isnan(output(0).d_));
  EXPECT_TRUE (std::isnan(output(1).d_));
  EXPECT_TRUE (std::isnan(output(2).d_));
}
TEST(AgradFwdMatrix, divide_rowvector) {
  using stan::math::divide;
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
  
  row_vector_d output_d = divide(d1, d2);
  EXPECT_FLOAT_EQ(-50, output_d(0));
  EXPECT_FLOAT_EQ(  0, output_d(1));
  EXPECT_FLOAT_EQ(1.5, output_d(2));

  row_vector_fv output;
  output = divide(d1, v2);
  EXPECT_FLOAT_EQ( -50, output(0).val_);
  EXPECT_FLOAT_EQ(   0, output(1).val_);
  EXPECT_FLOAT_EQ( 1.5, output(2).val_);
  EXPECT_FLOAT_EQ( -25, output(0).d_);
  EXPECT_FLOAT_EQ(   0, output(1).d_);
  EXPECT_FLOAT_EQ(0.75, output(2).d_);

  output = divide(v1, d2);
  EXPECT_FLOAT_EQ(  -50, output(0).val_);
  EXPECT_FLOAT_EQ(    0, output(1).val_);
  EXPECT_FLOAT_EQ(  1.5, output(2).val_);
  EXPECT_FLOAT_EQ( -0.5, output(0).d_);
  EXPECT_FLOAT_EQ( -0.5, output(1).d_);
  EXPECT_FLOAT_EQ( -0.5, output(2).d_);

  output = divide(v1, v2);
  EXPECT_FLOAT_EQ( -50, output(0).val_);
  EXPECT_FLOAT_EQ(   0, output(1).val_);
  EXPECT_FLOAT_EQ( 1.5, output(2).val_);
  EXPECT_FLOAT_EQ(-25.5, output(0).d_);
  EXPECT_FLOAT_EQ( -0.5, output(1).d_);
  EXPECT_FLOAT_EQ( 0.25, output(2).d_);

  d2 = 0;
  v2 = 0;
  output_d = divide(d1, d2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output_d(0));
  EXPECT_TRUE(std::isnan(output_d(1)));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), output_d(2));

  output = divide(d1, v2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(0).val_);
  EXPECT_TRUE(std::isnan(output(1).val_));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), output(2).val_);
  EXPECT_TRUE(std::isnan(output(0).d_));
  EXPECT_TRUE(std::isnan(output(1).d_));
  EXPECT_TRUE(std::isnan(output(2).d_));

  output = divide(v1, d2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(0).val_);
  EXPECT_TRUE (std::isnan(output(1).val_));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), output(2).val_);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(0).d_);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(1).d_);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(2).d_);

  output = divide(v1, v2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(0).val_);
  EXPECT_TRUE (std::isnan(output(1).val_));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), output(2).val_);
  EXPECT_TRUE(std::isnan(output(0).d_));
  EXPECT_TRUE(std::isnan(output(1).d_));
  EXPECT_TRUE(std::isnan(output(2).d_));
}
TEST(AgradFwdMatrix, divide_matrix) {
  using stan::math::divide;
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
  
  matrix_d output_d = divide(d1, d2);
  EXPECT_FLOAT_EQ(-50, output_d(0,0));
  EXPECT_FLOAT_EQ(  0, output_d(0,1));
  EXPECT_FLOAT_EQ(1.5, output_d(1,0));
  EXPECT_FLOAT_EQ( -2, output_d(1,1));

  matrix_fv output;
  output = divide(d1, v2);
  EXPECT_FLOAT_EQ( -50, output(0,0).val_);
  EXPECT_FLOAT_EQ(   0, output(0,1).val_);
  EXPECT_FLOAT_EQ( 1.5, output(1,0).val_);
  EXPECT_FLOAT_EQ(  -2, output(1,1).val_);
  EXPECT_FLOAT_EQ( -25, output(0,0).d_);
  EXPECT_FLOAT_EQ(   0, output(0,1).d_);
  EXPECT_FLOAT_EQ(0.75, output(1,0).d_);
  EXPECT_FLOAT_EQ(  -1, output(1,1).d_);
  
  output = divide(v1, d2);
  EXPECT_FLOAT_EQ( -50, output(0,0).val_);
  EXPECT_FLOAT_EQ(   0, output(0,1).val_);
  EXPECT_FLOAT_EQ( 1.5, output(1,0).val_);
  EXPECT_FLOAT_EQ(  -2, output(1,1).val_);
  EXPECT_FLOAT_EQ(-0.5, output(0,0).d_);
  EXPECT_FLOAT_EQ(-0.5, output(0,1).d_);
  EXPECT_FLOAT_EQ(-0.5, output(1,0).d_);
  EXPECT_FLOAT_EQ(-0.5, output(1,1).d_);
  
  output = divide(v1, v2);
  EXPECT_FLOAT_EQ(  -50, output(0,0).val_);
  EXPECT_FLOAT_EQ(    0, output(0,1).val_);
  EXPECT_FLOAT_EQ(  1.5, output(1,0).val_);
  EXPECT_FLOAT_EQ(   -2, output(1,1).val_);
  EXPECT_FLOAT_EQ(-25.5, output(0,0).d_);
  EXPECT_FLOAT_EQ( -0.5, output(0,1).d_);
  EXPECT_FLOAT_EQ( 0.25, output(1,0).d_);
  EXPECT_FLOAT_EQ( -1.5, output(1,1).d_);

  d2 = 0;
  v2 = 0;
  output_d = divide(d1, d2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output_d(0,0));
  EXPECT_TRUE(std::isnan(output_d(0,1)));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), output_d(1,0));
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output_d(1,1));

  output = divide(d1, v2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(0,0).val_);
  EXPECT_TRUE (std::isnan(output(0,1).val_));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), output(1,0).val_);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(1,1).val_);
  EXPECT_TRUE (std::isnan(output(0,0).d_));
  EXPECT_TRUE (std::isnan(output(0,1).d_));
  EXPECT_TRUE (std::isnan(output(1,0).d_));
  EXPECT_TRUE (std::isnan(output(1,1).d_));

  output = divide(v1, d2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(0,0).val_);
  EXPECT_TRUE (std::isnan(output(0,1).val_));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), output(1,0).val_);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(1,1).val_);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(0,0).d_);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(0,1).d_);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(1,0).d_);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(1,1).d_);

  output = divide(v1, v2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(0,0).val_);
  EXPECT_TRUE (std::isnan(output(0,1).val_));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), output(1,0).val_);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(1,1).val_);
  EXPECT_TRUE (std::isnan(output(0,0).d_));
  EXPECT_TRUE (std::isnan(output(0,1).d_));
  EXPECT_TRUE (std::isnan(output(1,0).d_));
  EXPECT_TRUE (std::isnan(output(1,1).d_));
}
TEST(AgradFwdFvarVarMatrix, divide_scalar) {
  using stan::agrad::divide;
  double d1, d2;
  fvar<var> v1, v2;

  d1 = 10;
  v1 = 10;
   v1.d_ = 1.0;
  d2 = -2;
  v2 = -2;
   v2.d_ = 1.0;
  
  EXPECT_FLOAT_EQ(  -5, divide(d1, d2));
  EXPECT_FLOAT_EQ(  -5, divide(d1, v2).val_.val());
  EXPECT_FLOAT_EQ(  -5, divide(v1, d2).val_.val());
  EXPECT_FLOAT_EQ(  -5, divide(v1, v2).val_.val());
  EXPECT_FLOAT_EQ(-2.5, divide(d1, v2).d_.val());
  EXPECT_FLOAT_EQ(-0.5, divide(v1, d2).d_.val());
  EXPECT_FLOAT_EQ(  -3, divide(v1, v2).d_.val());

  d2 = 0;
  v2 = 0;

  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), divide(d1, d2));
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  divide(d1, v2).val_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  divide(v1, d2).val_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  divide(v1, v2).val_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  divide(v1, d2).d_.val());
  EXPECT_TRUE(std::isnan(divide(d1, v2).d_.val()));
  EXPECT_TRUE(std::isnan(divide(v1, v2).d_.val()));

  d1 = 0;
  v1 = 0;
  EXPECT_TRUE(std::isnan(divide(d1, d2)));
  EXPECT_TRUE(std::isnan(divide(d1, v2).val_.val()));
  EXPECT_TRUE(std::isnan(divide(v1, d2).val_.val()));
  EXPECT_TRUE(std::isnan(divide(v1, v2).val_.val()));
  EXPECT_TRUE(std::isnan(divide(d1, v2).d_.val()));
  EXPECT_TRUE(std::isnan(divide(v1, d2).d_.val()));
  EXPECT_TRUE(std::isnan(divide(v1, v2).d_.val()));
}
TEST(AgradFwdFvarVarMatrix, divide_vector) {
  using stan::math::divide;
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
  
  vector_d output_d;
  output_d = divide(d1, d2);
  EXPECT_FLOAT_EQ(-50, output_d(0));
  EXPECT_FLOAT_EQ(  0, output_d(1));
  EXPECT_FLOAT_EQ(1.5, output_d(2));

  vector_fvv output;
  output = divide(d1, v2);
  EXPECT_FLOAT_EQ( -50, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ( 1.5, output(2).val_.val());
  EXPECT_FLOAT_EQ( -25, output(0).d_.val());
  EXPECT_FLOAT_EQ(   0, output(1).d_.val());
  EXPECT_FLOAT_EQ(0.75, output(2).d_.val());

  output = divide(v1, d2);
  EXPECT_FLOAT_EQ(  -50, output(0).val_.val());
  EXPECT_FLOAT_EQ(    0, output(1).val_.val());
  EXPECT_FLOAT_EQ(  1.5, output(2).val_.val());
  EXPECT_FLOAT_EQ( -0.5, output(0).d_.val());
  EXPECT_FLOAT_EQ( -0.5, output(1).d_.val());
  EXPECT_FLOAT_EQ( -0.5, output(2).d_.val());

  output = divide(v1, v2);
  EXPECT_FLOAT_EQ( -50, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ( 1.5, output(2).val_.val());
  EXPECT_FLOAT_EQ(-25.5, output(0).d_.val());
  EXPECT_FLOAT_EQ( -0.5, output(1).d_.val());
  EXPECT_FLOAT_EQ( 0.25, output(2).d_.val());

  d2 = 0;
  v2 = 0;
  output_d = divide(d1, d2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output_d(0));
  EXPECT_TRUE (std::isnan(output_d(1)));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), output_d(2));

  output = divide(d1, v2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(0).val_.val());
  EXPECT_TRUE (std::isnan(output(1).val_.val()));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), 
                  output(2).val_.val());
  EXPECT_TRUE (std::isnan(output(0).d_.val()));
  EXPECT_TRUE (std::isnan(output(1).d_.val()));
  EXPECT_TRUE (std::isnan(output(2).d_.val()));

  output = divide(v1, d2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(0).val_.val());
  EXPECT_TRUE (std::isnan(output(1).val_.val()));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), 
                  output(2).val_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(0).d_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(1).d_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(2).d_.val());

  output = divide(v1, v2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(0).val_.val());
  EXPECT_TRUE (std::isnan(output(1).val_.val()));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), 
                  output(2).val_.val());
  EXPECT_TRUE (std::isnan(output(0).d_.val()));
  EXPECT_TRUE (std::isnan(output(1).d_.val()));
  EXPECT_TRUE (std::isnan(output(2).d_.val()));
}
TEST(AgradFwdFvarVarMatrix, divide_rowvector) {
  using stan::math::divide;
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
  
  row_vector_d output_d = divide(d1, d2);
  EXPECT_FLOAT_EQ(-50, output_d(0));
  EXPECT_FLOAT_EQ(  0, output_d(1));
  EXPECT_FLOAT_EQ(1.5, output_d(2));

  row_vector_fvv output;
  output = divide(d1, v2);
  EXPECT_FLOAT_EQ( -50, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ( 1.5, output(2).val_.val());
  EXPECT_FLOAT_EQ( -25, output(0).d_.val());
  EXPECT_FLOAT_EQ(   0, output(1).d_.val());
  EXPECT_FLOAT_EQ(0.75, output(2).d_.val());

  output = divide(v1, d2);
  EXPECT_FLOAT_EQ(  -50, output(0).val_.val());
  EXPECT_FLOAT_EQ(    0, output(1).val_.val());
  EXPECT_FLOAT_EQ(  1.5, output(2).val_.val());
  EXPECT_FLOAT_EQ( -0.5, output(0).d_.val());
  EXPECT_FLOAT_EQ( -0.5, output(1).d_.val());
  EXPECT_FLOAT_EQ( -0.5, output(2).d_.val());

  output = divide(v1, v2);
  EXPECT_FLOAT_EQ( -50, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ( 1.5, output(2).val_.val());
  EXPECT_FLOAT_EQ(-25.5, output(0).d_.val());
  EXPECT_FLOAT_EQ( -0.5, output(1).d_.val());
  EXPECT_FLOAT_EQ( 0.25, output(2).d_.val());

  d2 = 0;
  v2 = 0;
  output_d = divide(d1, d2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output_d(0));
  EXPECT_TRUE(std::isnan(output_d(1)));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), output_d(2));

  output = divide(d1, v2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(0).val_.val());
  EXPECT_TRUE(std::isnan(output(1).val_.val()));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), 
                  output(2).val_.val());
  EXPECT_TRUE(std::isnan(output(0).d_.val()));
  EXPECT_TRUE(std::isnan(output(1).d_.val()));
  EXPECT_TRUE(std::isnan(output(2).d_.val()));

  output = divide(v1, d2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(0).val_.val());
  EXPECT_TRUE (std::isnan(output(1).val_.val()));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), 
                  output(2).val_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(0).d_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(1).d_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(2).d_.val());

  output = divide(v1, v2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(0).val_.val());
  EXPECT_TRUE (std::isnan(output(1).val_.val()));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), 
                  output(2).val_.val());
  EXPECT_TRUE(std::isnan(output(0).d_.val()));
  EXPECT_TRUE(std::isnan(output(1).d_.val()));
  EXPECT_TRUE(std::isnan(output(2).d_.val()));
}
TEST(AgradFwdFvarVarMatrix, divide_matrix) {
  using stan::math::divide;
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
  
  matrix_d output_d = divide(d1, d2);
  EXPECT_FLOAT_EQ(-50, output_d(0,0));
  EXPECT_FLOAT_EQ(  0, output_d(0,1));
  EXPECT_FLOAT_EQ(1.5, output_d(1,0));
  EXPECT_FLOAT_EQ( -2, output_d(1,1));

  matrix_fvv output;
  output = divide(d1, v2);
  EXPECT_FLOAT_EQ( -50, output(0,0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(0,1).val_.val());
  EXPECT_FLOAT_EQ( 1.5, output(1,0).val_.val());
  EXPECT_FLOAT_EQ(  -2, output(1,1).val_.val());
  EXPECT_FLOAT_EQ( -25, output(0,0).d_.val());
  EXPECT_FLOAT_EQ(   0, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(0.75, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(  -1, output(1,1).d_.val());
  
  output = divide(v1, d2);
  EXPECT_FLOAT_EQ( -50, output(0,0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(0,1).val_.val());
  EXPECT_FLOAT_EQ( 1.5, output(1,0).val_.val());
  EXPECT_FLOAT_EQ(  -2, output(1,1).val_.val());
  EXPECT_FLOAT_EQ(-0.5, output(0,0).d_.val());
  EXPECT_FLOAT_EQ(-0.5, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(-0.5, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(-0.5, output(1,1).d_.val());
  
  output = divide(v1, v2);
  EXPECT_FLOAT_EQ(  -50, output(0,0).val_.val());
  EXPECT_FLOAT_EQ(    0, output(0,1).val_.val());
  EXPECT_FLOAT_EQ(  1.5, output(1,0).val_.val());
  EXPECT_FLOAT_EQ(   -2, output(1,1).val_.val());
  EXPECT_FLOAT_EQ(-25.5, output(0,0).d_.val());
  EXPECT_FLOAT_EQ( -0.5, output(0,1).d_.val());
  EXPECT_FLOAT_EQ( 0.25, output(1,0).d_.val());
  EXPECT_FLOAT_EQ( -1.5, output(1,1).d_.val());

  d2 = 0;
  v2 = 0;
  output_d = divide(d1, d2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output_d(0,0));
  EXPECT_TRUE(std::isnan(output_d(0,1)));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), output_d(1,0));
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output_d(1,1));

  output = divide(d1, v2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(0,0).val_.val());
  EXPECT_TRUE (std::isnan(output(0,1).val_.val()));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), 
                  output(1,0).val_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(1,1).val_.val());
  EXPECT_TRUE (std::isnan(output(0,0).d_.val()));
  EXPECT_TRUE (std::isnan(output(0,1).d_.val()));
  EXPECT_TRUE (std::isnan(output(1,0).d_.val()));
  EXPECT_TRUE (std::isnan(output(1,1).d_.val()));

  output = divide(v1, d2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(0,0).val_.val());
  EXPECT_TRUE (std::isnan(output(0,1).val_.val()));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), 
                  output(1,0).val_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(),
                  output(1,1).val_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(0,0).d_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(0,1).d_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(),
                  output(1,0).d_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(1,1).d_.val());

  output = divide(v1, v2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(0,0).val_.val());
  EXPECT_TRUE (std::isnan(output(0,1).val_.val()));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), 
                  output(1,0).val_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(),
 output(1,1).val_.val());
  EXPECT_TRUE (std::isnan(output(0,0).d_.val()));
  EXPECT_TRUE (std::isnan(output(0,1).d_.val()));
  EXPECT_TRUE (std::isnan(output(1,0).d_.val()));
  EXPECT_TRUE (std::isnan(output(1,1).d_.val()));
}
TEST(AgradFwdFvarFvarMatrix, divide_scalar) {
  using stan::agrad::divide;
  double d1, d2;
  fvar<fvar<double> > v1, v2;

  d1 = 10;
  v1.val_.val_ = 10;
  v1.d_.val_ = 1.0;
  d2 = -2;
  v2.val_.val_ = -2;
  v2.d_.val_ = 1.0;
  
  EXPECT_FLOAT_EQ(  -5, divide(d1, d2));
  EXPECT_FLOAT_EQ(  -5, divide(d1, v2).val_.val());
  EXPECT_FLOAT_EQ(  -5, divide(v1, d2).val_.val());
  EXPECT_FLOAT_EQ(  -5, divide(v1, v2).val_.val());
  EXPECT_FLOAT_EQ(-2.5, divide(d1, v2).d_.val());
  EXPECT_FLOAT_EQ(-0.5, divide(v1, d2).d_.val());
  EXPECT_FLOAT_EQ(  -3, divide(v1, v2).d_.val());

  d2 = 0;
  v2 = 0;

  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), divide(d1, d2));
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  divide(d1, v2).val_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  divide(v1, d2).val_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  divide(v1, v2).val_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  divide(v1, d2).d_.val());
  EXPECT_TRUE(std::isnan(divide(d1, v2).d_.val()));
  EXPECT_TRUE(std::isnan(divide(v1, v2).d_.val()));

  d1 = 0;
  v1 = 0;
  EXPECT_TRUE(std::isnan(divide(d1, d2)));
  EXPECT_TRUE(std::isnan(divide(d1, v2).val_.val()));
  EXPECT_TRUE(std::isnan(divide(v1, d2).val_.val()));
  EXPECT_TRUE(std::isnan(divide(v1, v2).val_.val()));
  EXPECT_TRUE(std::isnan(divide(d1, v2).d_.val()));
  EXPECT_TRUE(std::isnan(divide(v1, d2).d_.val()));
  EXPECT_TRUE(std::isnan(divide(v1, v2).d_.val()));
}
TEST(AgradFwdFvarFvarMatrix, divide_vector) {
  using stan::math::divide;
  using stan::math::vector_d;
  using stan::agrad::vector_ffv;

  vector_d d1(3);
  vector_ffv v1(3);
  double d2;
  fvar<fvar<double> > v2,a,b,c;
  
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
  
  vector_d output_d;
  output_d = divide(d1, d2);
  EXPECT_FLOAT_EQ(-50, output_d(0));
  EXPECT_FLOAT_EQ(  0, output_d(1));
  EXPECT_FLOAT_EQ(1.5, output_d(2));

  vector_ffv output;
  output = divide(d1, v2);
  EXPECT_FLOAT_EQ( -50, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ( 1.5, output(2).val_.val());
  EXPECT_FLOAT_EQ( -25, output(0).d_.val());
  EXPECT_FLOAT_EQ(   0, output(1).d_.val());
  EXPECT_FLOAT_EQ(0.75, output(2).d_.val());

  output = divide(v1, d2);
  EXPECT_FLOAT_EQ(  -50, output(0).val_.val());
  EXPECT_FLOAT_EQ(    0, output(1).val_.val());
  EXPECT_FLOAT_EQ(  1.5, output(2).val_.val());
  EXPECT_FLOAT_EQ( -0.5, output(0).d_.val());
  EXPECT_FLOAT_EQ( -0.5, output(1).d_.val());
  EXPECT_FLOAT_EQ( -0.5, output(2).d_.val());

  output = divide(v1, v2);
  EXPECT_FLOAT_EQ( -50, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ( 1.5, output(2).val_.val());
  EXPECT_FLOAT_EQ(-25.5, output(0).d_.val());
  EXPECT_FLOAT_EQ( -0.5, output(1).d_.val());
  EXPECT_FLOAT_EQ( 0.25, output(2).d_.val());

  d2 = 0;
  v2 = 0;
  output_d = divide(d1, d2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output_d(0));
  EXPECT_TRUE (std::isnan(output_d(1)));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), output_d(2));

  output = divide(d1, v2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(0).val_.val());
  EXPECT_TRUE (std::isnan(output(1).val_.val()));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), 
                  output(2).val_.val());
  EXPECT_TRUE (std::isnan(output(0).d_.val()));
  EXPECT_TRUE (std::isnan(output(1).d_.val()));
  EXPECT_TRUE (std::isnan(output(2).d_.val()));

  output = divide(v1, d2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(0).val_.val());
  EXPECT_TRUE (std::isnan(output(1).val_.val()));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), 
                  output(2).val_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(0).d_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(1).d_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(2).d_.val());

  output = divide(v1, v2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(0).val_.val());
  EXPECT_TRUE (std::isnan(output(1).val_.val()));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), output(2).val_.val());
  EXPECT_TRUE (std::isnan(output(0).d_.val()));
  EXPECT_TRUE (std::isnan(output(1).d_.val()));
  EXPECT_TRUE (std::isnan(output(2).d_.val()));
}
TEST(AgradFwdFvarFvarMatrix, divide_rowvector) {
  using stan::math::divide;
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_ffv;

  row_vector_d d1(3);
  row_vector_ffv v1(3);
  double d2;
  fvar<fvar<double> > v2,a,b,c;
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
  
  row_vector_d output_d = divide(d1, d2);
  EXPECT_FLOAT_EQ(-50, output_d(0));
  EXPECT_FLOAT_EQ(  0, output_d(1));
  EXPECT_FLOAT_EQ(1.5, output_d(2));

  row_vector_ffv output;
  output = divide(d1, v2);
  EXPECT_FLOAT_EQ( -50, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ( 1.5, output(2).val_.val());
  EXPECT_FLOAT_EQ( -25, output(0).d_.val());
  EXPECT_FLOAT_EQ(   0, output(1).d_.val());
  EXPECT_FLOAT_EQ(0.75, output(2).d_.val());

  output = divide(v1, d2);
  EXPECT_FLOAT_EQ(  -50, output(0).val_.val());
  EXPECT_FLOAT_EQ(    0, output(1).val_.val());
  EXPECT_FLOAT_EQ(  1.5, output(2).val_.val());
  EXPECT_FLOAT_EQ( -0.5, output(0).d_.val());
  EXPECT_FLOAT_EQ( -0.5, output(1).d_.val());
  EXPECT_FLOAT_EQ( -0.5, output(2).d_.val());

  output = divide(v1, v2);
  EXPECT_FLOAT_EQ( -50, output(0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(1).val_.val());
  EXPECT_FLOAT_EQ( 1.5, output(2).val_.val());
  EXPECT_FLOAT_EQ(-25.5, output(0).d_.val());
  EXPECT_FLOAT_EQ( -0.5, output(1).d_.val());
  EXPECT_FLOAT_EQ( 0.25, output(2).d_.val());

  d2 = 0;
  v2 = 0;
  output_d = divide(d1, d2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output_d(0));
  EXPECT_TRUE(std::isnan(output_d(1)));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), output_d(2));

  output = divide(d1, v2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(0).val_.val());
  EXPECT_TRUE(std::isnan(output(1).val_.val()));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), 
                  output(2).val_.val());
  EXPECT_TRUE(std::isnan(output(0).d_.val()));
  EXPECT_TRUE(std::isnan(output(1).d_.val()));
  EXPECT_TRUE(std::isnan(output(2).d_.val()));

  output = divide(v1, d2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(0).val_.val());
  EXPECT_TRUE (std::isnan(output(1).val_.val()));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(),
                  output(2).val_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(0).d_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(1).d_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output(2).d_.val());

  output = divide(v1, v2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(0).val_.val());
  EXPECT_TRUE (std::isnan(output(1).val_.val()));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), 
                  output(2).val_.val());
  EXPECT_TRUE(std::isnan(output(0).d_.val()));
  EXPECT_TRUE(std::isnan(output(1).d_.val()));
  EXPECT_TRUE(std::isnan(output(2).d_.val()));
}
TEST(AgradFwdFvarFvarMatrix, divide_matrix) {
  using stan::math::divide;
  using stan::math::matrix_d;
  using stan::agrad::matrix_ffv;

  matrix_d d1(2,2);
  matrix_ffv v1(2,2);
  double d2;
  fvar<fvar<double> > v2,a,b,c,d;
  
  a.val_.val_ = 100.0;
  b.val_.val_ = 0.0;
  c.val_.val_ = -3.0;
  d.val_.val_ = 4.0;
  a.d_.val_ = 1.0;
  b.d_.val_ = 1.0;
  c.d_.val_ = 1.0;
  d.d_.val_ = 1.0;
  d1 << 100, 0, -3, 4;
  v1 << a,b,c,d;
  d2 = -2;
  v2.val_.val_ = -2;
  v2.d_.val_ = 1.0;
  
  matrix_d output_d = divide(d1, d2);
  EXPECT_FLOAT_EQ(-50, output_d(0,0));
  EXPECT_FLOAT_EQ(  0, output_d(0,1));
  EXPECT_FLOAT_EQ(1.5, output_d(1,0));
  EXPECT_FLOAT_EQ( -2, output_d(1,1));

  matrix_ffv output;
  output = divide(d1, v2);
  EXPECT_FLOAT_EQ( -50, output(0,0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(0,1).val_.val());
  EXPECT_FLOAT_EQ( 1.5, output(1,0).val_.val());
  EXPECT_FLOAT_EQ(  -2, output(1,1).val_.val());
  EXPECT_FLOAT_EQ( -25, output(0,0).d_.val());
  EXPECT_FLOAT_EQ(   0, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(0.75, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(  -1, output(1,1).d_.val());
  
  output = divide(v1, d2);
  EXPECT_FLOAT_EQ( -50, output(0,0).val_.val());
  EXPECT_FLOAT_EQ(   0, output(0,1).val_.val());
  EXPECT_FLOAT_EQ( 1.5, output(1,0).val_.val());
  EXPECT_FLOAT_EQ(  -2, output(1,1).val_.val());
  EXPECT_FLOAT_EQ(-0.5, output(0,0).d_.val());
  EXPECT_FLOAT_EQ(-0.5, output(0,1).d_.val());
  EXPECT_FLOAT_EQ(-0.5, output(1,0).d_.val());
  EXPECT_FLOAT_EQ(-0.5, output(1,1).d_.val());
  
  output = divide(v1, v2);
  EXPECT_FLOAT_EQ(  -50, output(0,0).val_.val());
  EXPECT_FLOAT_EQ(    0, output(0,1).val_.val());
  EXPECT_FLOAT_EQ(  1.5, output(1,0).val_.val());
  EXPECT_FLOAT_EQ(   -2, output(1,1).val_.val());
  EXPECT_FLOAT_EQ(-25.5, output(0,0).d_.val());
  EXPECT_FLOAT_EQ( -0.5, output(0,1).d_.val());
  EXPECT_FLOAT_EQ( 0.25, output(1,0).d_.val());
  EXPECT_FLOAT_EQ( -1.5, output(1,1).d_.val());

  d2 = 0;
  v2 = 0;
  output_d = divide(d1, d2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output_d(0,0));
  EXPECT_TRUE(std::isnan(output_d(0,1)));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), output_d(1,0));
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), output_d(1,1));

  output = divide(d1, v2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(0,0).val_.val());
  EXPECT_TRUE (std::isnan(output(0,1).val_.val()));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), 
                  output(1,0).val_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(1,1).val_.val());
  EXPECT_TRUE (std::isnan(output(0,0).d_.val()));
  EXPECT_TRUE (std::isnan(output(0,1).d_.val()));
  EXPECT_TRUE (std::isnan(output(1,0).d_.val()));
  EXPECT_TRUE (std::isnan(output(1,1).d_.val()));

  output = divide(v1, d2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(0,0).val_.val());
  EXPECT_TRUE (std::isnan(output(0,1).val_.val()));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), 
                  output(1,0).val_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(1,1).val_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(0,0).d_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(0,1).d_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(1,0).d_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(1,1).d_.val());

  output = divide(v1, v2);
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(0,0).val_.val());
  EXPECT_TRUE (std::isnan(output(0,1).val_.val()));
  EXPECT_FLOAT_EQ(-std::numeric_limits<double>::infinity(), 
                  output(1,0).val_.val());
  EXPECT_FLOAT_EQ(std::numeric_limits<double>::infinity(), 
                  output(1,1).val_.val());
  EXPECT_TRUE (std::isnan(output(0,0).d_.val()));
  EXPECT_TRUE (std::isnan(output(0,1).d_.val()));
  EXPECT_TRUE (std::isnan(output(1,0).d_.val()));
  EXPECT_TRUE (std::isnan(output(1,1).d_.val()));
}
