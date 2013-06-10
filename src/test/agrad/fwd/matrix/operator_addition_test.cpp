#include <stan/math/matrix/add.hpp>
#include <gtest/gtest.h>
#include <stan/math/matrix/typedefs.hpp>
#include <stan/agrad/fwd/matrix/typedefs.hpp>
#include <stan/agrad/fvar.hpp>
#include <stan/agrad/var.hpp>

using stan::agrad::fvar;
TEST(AgradFwdMatrix,add_scalar_matrix) {
  using stan::agrad::matrix_fv;
  using stan::math::add;

  matrix_fv v(2,2);
  v << 1, 2, 3, 4;
   v(0,0).d_ = 1.0;
   v(0,1).d_ = 1.0;
   v(1,0).d_ = 1.0;
   v(1,1).d_ = 1.0;
  matrix_fv result;

  result = add(2.0,v);
  EXPECT_FLOAT_EQ(3.0,result(0,0).val_);
  EXPECT_FLOAT_EQ(4.0,result(0,1).val_);
  EXPECT_FLOAT_EQ(5.0,result(1,0).val_);
  EXPECT_FLOAT_EQ(6.0,result(1,1).val_);
  EXPECT_FLOAT_EQ(1.0,result(0,0).d_);
  EXPECT_FLOAT_EQ(1.0,result(0,1).d_);
  EXPECT_FLOAT_EQ(1.0,result(1,0).d_);
  EXPECT_FLOAT_EQ(1.0,result(1,1).d_);

  result = add(v,2.0);
  EXPECT_FLOAT_EQ(3.0,result(0,0).val_);
  EXPECT_FLOAT_EQ(4.0,result(0,1).val_);
  EXPECT_FLOAT_EQ(5.0,result(1,0).val_);
  EXPECT_FLOAT_EQ(6.0,result(1,1).val_);
  EXPECT_FLOAT_EQ(1.0,result(0,0).d_);
  EXPECT_FLOAT_EQ(1.0,result(0,1).d_);
  EXPECT_FLOAT_EQ(1.0,result(1,0).d_);
  EXPECT_FLOAT_EQ(1.0,result(1,1).d_);
}
TEST(AgradFwdMatrix,add_scalar_vector) {
  using stan::agrad::vector_fv;
  using stan::math::add;

  vector_fv v(4);
  v << 1, 2, 3, 4;
   v(0).d_ = 1.0;
   v(1).d_ = 1.0;
   v(2).d_ = 1.0;
   v(3).d_ = 1.0;
  vector_fv result;

  result = add(2.0,v);
  EXPECT_FLOAT_EQ(3.0,result(0).val_);
  EXPECT_FLOAT_EQ(4.0,result(1).val_);
  EXPECT_FLOAT_EQ(5.0,result(2).val_);
  EXPECT_FLOAT_EQ(6.0,result(3).val_);
  EXPECT_FLOAT_EQ(1.0,result(0).d_);
  EXPECT_FLOAT_EQ(1.0,result(1).d_);
  EXPECT_FLOAT_EQ(1.0,result(2).d_);
  EXPECT_FLOAT_EQ(1.0,result(3).d_);

  result = add(v,2.0);
  EXPECT_FLOAT_EQ(3.0,result(0).val_);
  EXPECT_FLOAT_EQ(4.0,result(1).val_);
  EXPECT_FLOAT_EQ(5.0,result(2).val_);
  EXPECT_FLOAT_EQ(6.0,result(3).val_);
  EXPECT_FLOAT_EQ(1.0,result(0).d_);
  EXPECT_FLOAT_EQ(1.0,result(1).d_);
  EXPECT_FLOAT_EQ(1.0,result(2).d_);
  EXPECT_FLOAT_EQ(1.0,result(3).d_);
}
TEST(AgradFwdMatrix,add_scalar_rowvector) {
  using stan::agrad::row_vector_fv;
  using stan::math::add;

  row_vector_fv v(4);
  v << 1, 2, 3, 4;
   v(0).d_ = 1.0;
   v(1).d_ = 1.0;
   v(2).d_ = 1.0;
   v(3).d_ = 1.0;
  row_vector_fv result;

  result = add(2.0,v);
  EXPECT_FLOAT_EQ(3.0,result(0).val_);
  EXPECT_FLOAT_EQ(4.0,result(1).val_);
  EXPECT_FLOAT_EQ(5.0,result(2).val_);
  EXPECT_FLOAT_EQ(6.0,result(3).val_);
  EXPECT_FLOAT_EQ(1.0,result(0).d_);
  EXPECT_FLOAT_EQ(1.0,result(1).d_);
  EXPECT_FLOAT_EQ(1.0,result(2).d_);
  EXPECT_FLOAT_EQ(1.0,result(3).d_);

  result = add(v,2.0);
  EXPECT_FLOAT_EQ(3.0,result(0).val_);
  EXPECT_FLOAT_EQ(4.0,result(1).val_);
  EXPECT_FLOAT_EQ(5.0,result(2).val_);
  EXPECT_FLOAT_EQ(6.0,result(3).val_);
  EXPECT_FLOAT_EQ(1.0,result(0).d_);
  EXPECT_FLOAT_EQ(1.0,result(1).d_);
  EXPECT_FLOAT_EQ(1.0,result(2).d_);
  EXPECT_FLOAT_EQ(1.0,result(3).d_);
}
TEST(AgradFwdMatrix, add_vector_vector) {
  using stan::math::add;
  using stan::math::vector_d;
  using stan::agrad::vector_fv;

  vector_d vd_1(5);
  vector_d vd_2(5);
  vector_fv vv_1(5);
  vector_fv vv_2(5);
  
  vd_1 << 1, 2, 3, 4, 5;
  vv_1 << 1, 2, 3, 4, 5;
   vv_1(0).d_ = 1.0;
   vv_1(1).d_ = 1.0;
   vv_1(2).d_ = 1.0;
   vv_1(3).d_ = 1.0;
   vv_1(4).d_ = 1.0;
  vd_2 << 2, 3, 4, 5, 6;
  vv_2 << 2, 3, 4, 5, 6;
   vv_2(0).d_ = 1.0;
   vv_2(1).d_ = 1.0;
   vv_2(2).d_ = 1.0;
   vv_2(3).d_ = 1.0;
   vv_2(4).d_ = 1.0;
  
  vector_d expected_output(5);
  expected_output << 3, 5, 7, 9, 11;
  
  vector_d output_d;
  output_d = add(vd_1, vd_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_d(0));
  EXPECT_FLOAT_EQ(expected_output(1), output_d(1));
  EXPECT_FLOAT_EQ(expected_output(2), output_d(2));
  EXPECT_FLOAT_EQ(expected_output(3), output_d(3));
  EXPECT_FLOAT_EQ(expected_output(4), output_d(4));  

  vector_fv output_v = add(vv_1, vd_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_v(0).val_);
  EXPECT_FLOAT_EQ(expected_output(1), output_v(1).val_);
  EXPECT_FLOAT_EQ(expected_output(2), output_v(2).val_);
  EXPECT_FLOAT_EQ(expected_output(3), output_v(3).val_);
  EXPECT_FLOAT_EQ(expected_output(4), output_v(4).val_); 
  EXPECT_FLOAT_EQ(1.0, output_v(0).d_);
  EXPECT_FLOAT_EQ(1.0, output_v(1).d_);
  EXPECT_FLOAT_EQ(1.0, output_v(2).d_);
  EXPECT_FLOAT_EQ(1.0, output_v(3).d_);
  EXPECT_FLOAT_EQ(1.0, output_v(4).d_); 

  output_v = add(vd_1, vv_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_v(0).val_);
  EXPECT_FLOAT_EQ(expected_output(1), output_v(1).val_);
  EXPECT_FLOAT_EQ(expected_output(2), output_v(2).val_);
  EXPECT_FLOAT_EQ(expected_output(3), output_v(3).val_);
  EXPECT_FLOAT_EQ(expected_output(4), output_v(4).val_); 
  EXPECT_FLOAT_EQ(1.0, output_v(0).d_);
  EXPECT_FLOAT_EQ(1.0, output_v(1).d_);
  EXPECT_FLOAT_EQ(1.0, output_v(2).d_);
  EXPECT_FLOAT_EQ(1.0, output_v(3).d_);
  EXPECT_FLOAT_EQ(1.0, output_v(4).d_);   

  output_v = add(vv_1, vv_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_v(0).val_);
  EXPECT_FLOAT_EQ(expected_output(1), output_v(1).val_);
  EXPECT_FLOAT_EQ(expected_output(2), output_v(2).val_);
  EXPECT_FLOAT_EQ(expected_output(3), output_v(3).val_);
  EXPECT_FLOAT_EQ(expected_output(4), output_v(4).val_); 
  EXPECT_FLOAT_EQ(2.0, output_v(0).d_);
  EXPECT_FLOAT_EQ(2.0, output_v(1).d_);
  EXPECT_FLOAT_EQ(2.0, output_v(2).d_);
  EXPECT_FLOAT_EQ(2.0, output_v(3).d_);
  EXPECT_FLOAT_EQ(2.0, output_v(4).d_);  
}
TEST(AgradFwdMatrix, add_vector_vector_exception) {
  using stan::math::add;
  using stan::math::vector_d;
  using stan::agrad::vector_fv;

  vector_d d1(5), d2(1);
  vector_fv v1(5), v2(1);
  
  EXPECT_THROW(add(d1, d2), std::domain_error);
  EXPECT_THROW(add(v1, d2), std::domain_error);
  EXPECT_THROW(add(d1, v2), std::domain_error);
  EXPECT_THROW(add(v1, v2), std::domain_error);
}
TEST(AgradFwdMatrix, add_rowvector_rowvector) {
  using stan::math::add;
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_fv;

  row_vector_d rvd_1(5), rvd_2(5);
  row_vector_fv rvv_1(5), rvv_2(5);

  rvd_1 << 1, 2, 3, 4, 5;
  rvv_1 << 1, 2, 3, 4, 5;
   rvv_1(0).d_ = 1.0;
   rvv_1(1).d_ = 1.0;
   rvv_1(2).d_ = 1.0;
   rvv_1(3).d_ = 1.0;
   rvv_1(4).d_ = 1.0;
  rvd_2 << 2, 3, 4, 5, 6;
  rvv_2 << 2, 3, 4, 5, 6;
   rvv_2(0).d_ = 1.0;
   rvv_2(1).d_ = 1.0;
   rvv_2(2).d_ = 1.0;
   rvv_2(3).d_ = 1.0;
   rvv_2(4).d_ = 1.0;
  
  row_vector_d expected_output(5);
  expected_output << 3, 5, 7, 9, 11;
  
  row_vector_d output_d = add(rvd_1, rvd_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_d(0));
  EXPECT_FLOAT_EQ(expected_output(1), output_d(1));
  EXPECT_FLOAT_EQ(expected_output(2), output_d(2));
  EXPECT_FLOAT_EQ(expected_output(3), output_d(3));
  EXPECT_FLOAT_EQ(expected_output(4), output_d(4));  

  row_vector_fv output_v = add(rvv_1, rvd_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_v(0).val_);
  EXPECT_FLOAT_EQ(expected_output(1), output_v(1).val_);
  EXPECT_FLOAT_EQ(expected_output(2), output_v(2).val_);
  EXPECT_FLOAT_EQ(expected_output(3), output_v(3).val_);
  EXPECT_FLOAT_EQ(expected_output(4), output_v(4).val_);  
  EXPECT_FLOAT_EQ(1.0, output_v(0).d_);
  EXPECT_FLOAT_EQ(1.0, output_v(1).d_);
  EXPECT_FLOAT_EQ(1.0, output_v(2).d_);
  EXPECT_FLOAT_EQ(1.0, output_v(3).d_);
  EXPECT_FLOAT_EQ(1.0, output_v(4).d_);

  output_v = add(rvd_1, rvv_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_v(0).val_);
  EXPECT_FLOAT_EQ(expected_output(1), output_v(1).val_);
  EXPECT_FLOAT_EQ(expected_output(2), output_v(2).val_);
  EXPECT_FLOAT_EQ(expected_output(3), output_v(3).val_);
  EXPECT_FLOAT_EQ(expected_output(4), output_v(4).val_);  
  EXPECT_FLOAT_EQ(1.0, output_v(0).d_);
  EXPECT_FLOAT_EQ(1.0, output_v(1).d_);
  EXPECT_FLOAT_EQ(1.0, output_v(2).d_);
  EXPECT_FLOAT_EQ(1.0, output_v(3).d_);
  EXPECT_FLOAT_EQ(1.0, output_v(4).d_);

  output_v = add(rvv_1, rvv_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_v(0).val_);
  EXPECT_FLOAT_EQ(expected_output(1), output_v(1).val_);
  EXPECT_FLOAT_EQ(expected_output(2), output_v(2).val_);
  EXPECT_FLOAT_EQ(expected_output(3), output_v(3).val_);
  EXPECT_FLOAT_EQ(expected_output(4), output_v(4).val_);  
  EXPECT_FLOAT_EQ(2.0, output_v(0).d_);
  EXPECT_FLOAT_EQ(2.0, output_v(1).d_);
  EXPECT_FLOAT_EQ(2.0, output_v(2).d_);
  EXPECT_FLOAT_EQ(2.0, output_v(3).d_);
  EXPECT_FLOAT_EQ(2.0, output_v(4).d_);
}
TEST(AgradFwdMatrix, add_rowvector_rowvector_exception) {
  using stan::math::add;
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_fv;

  row_vector_d d1(5), d2(2);
  row_vector_fv v1(5), v2(2);

  row_vector_fv output;
  EXPECT_THROW( add(d1, d2), std::domain_error);
  EXPECT_THROW( add(d1, v2), std::domain_error);
  EXPECT_THROW( add(v1, d2), std::domain_error);
  EXPECT_THROW( add(v1, v2), std::domain_error);
}
TEST(AgradFwdMatrix, add_matrix_matrix) {
  using stan::math::add;
  using stan::math::matrix_d;
  using stan::agrad::matrix_fv;

  matrix_d md_1(2,2), md_2(2,2);
  matrix_fv mv_1(2,2), mv_2(2,2);

  md_1 << -10, 1, 10, 0;
  mv_1 << -10, 1, 10, 0;
   mv_1(0,0).d_ = 1.0;
   mv_1(0,1).d_ = 1.0;
   mv_1(1,0).d_ = 1.0;
   mv_1(1,1).d_ = 1.0;
  md_2 << 10, -10, 1, 2;
  mv_2 << 10, -10, 1, 2;
   mv_2(0,0).d_ = 1.0;
   mv_2(0,1).d_ = 1.0;
   mv_2(1,0).d_ = 1.0;
   mv_2(1,1).d_ = 1.0;
  
  matrix_d expected_output(2,2);
  expected_output << 0, -9, 11, 2;
  
  matrix_d output_d = add(md_1, md_2);
  EXPECT_FLOAT_EQ(expected_output(0,0), output_d(0,0));
  EXPECT_FLOAT_EQ(expected_output(0,1), output_d(0,1));
  EXPECT_FLOAT_EQ(expected_output(1,0), output_d(1,0));
  EXPECT_FLOAT_EQ(expected_output(1,1), output_d(1,1));

  matrix_fv output_v = add(mv_1, md_2);
  EXPECT_FLOAT_EQ(expected_output(0,0), output_v(0,0).val_);
  EXPECT_FLOAT_EQ(expected_output(0,1), output_v(0,1).val_);
  EXPECT_FLOAT_EQ(expected_output(1,0), output_v(1,0).val_);
  EXPECT_FLOAT_EQ(expected_output(1,1), output_v(1,1).val_);
  EXPECT_FLOAT_EQ(1.0, output_v(0,0).d_);
  EXPECT_FLOAT_EQ(1.0, output_v(0,1).d_);
  EXPECT_FLOAT_EQ(1.0, output_v(1,0).d_);
  EXPECT_FLOAT_EQ(1.0, output_v(1,1).d_);

  output_v = add(md_1, mv_2);
  EXPECT_FLOAT_EQ(expected_output(0,0), output_v(0,0).val_);
  EXPECT_FLOAT_EQ(expected_output(0,1), output_v(0,1).val_);
  EXPECT_FLOAT_EQ(expected_output(1,0), output_v(1,0).val_);
  EXPECT_FLOAT_EQ(expected_output(1,1), output_v(1,1).val_);
  EXPECT_FLOAT_EQ(1.0, output_v(0,0).d_);
  EXPECT_FLOAT_EQ(1.0, output_v(0,1).d_);
  EXPECT_FLOAT_EQ(1.0, output_v(1,0).d_);
  EXPECT_FLOAT_EQ(1.0, output_v(1,1).d_);

  output_v = add(mv_1, mv_2);
  EXPECT_FLOAT_EQ(expected_output(0,0), output_v(0,0).val_);
  EXPECT_FLOAT_EQ(expected_output(0,1), output_v(0,1).val_);
  EXPECT_FLOAT_EQ(expected_output(1,0), output_v(1,0).val_);
  EXPECT_FLOAT_EQ(expected_output(1,1), output_v(1,1).val_);
  EXPECT_FLOAT_EQ(2.0, output_v(0,0).d_);
  EXPECT_FLOAT_EQ(2.0, output_v(0,1).d_);
  EXPECT_FLOAT_EQ(2.0, output_v(1,0).d_);
  EXPECT_FLOAT_EQ(2.0, output_v(1,1).d_);
}
TEST(AgradFwdMatrix, add_matrix_matrix_exception) {
  using stan::math::add;
  using stan::math::matrix_d;
  using stan::agrad::matrix_fv;
  
  matrix_d d1(2,2), d2(1,2);
  matrix_fv v1(2,2), v2(1,2);

  EXPECT_THROW(add(d1, d2), std::domain_error);
  EXPECT_THROW(add(d1, v2), std::domain_error);
  EXPECT_THROW(add(v1, d2), std::domain_error);
  EXPECT_THROW(add(v1, v2), std::domain_error);
}
TEST(AgradFwdFvarVarMatrix,add_scalar_matrix) {
  using stan::agrad::matrix_fvv;
  using stan::math::add;

  matrix_fvv v(2,2);
  v << 1, 2, 3, 4;
   v(0,0).d_ = 1.0;
   v(0,1).d_ = 1.0;
   v(1,0).d_ = 1.0;
   v(1,1).d_ = 1.0;
  matrix_fvv result;

  result = add(2.0,v);
  EXPECT_FLOAT_EQ(3.0,result(0,0).val_.val());
  EXPECT_FLOAT_EQ(4.0,result(0,1).val_.val());
  EXPECT_FLOAT_EQ(5.0,result(1,0).val_.val());
  EXPECT_FLOAT_EQ(6.0,result(1,1).val_.val());
  EXPECT_FLOAT_EQ(1.0,result(0,0).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(0,1).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(1,0).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(1,1).d_.val());

  result = add(v,2.0);
  EXPECT_FLOAT_EQ(3.0,result(0,0).val_.val());
  EXPECT_FLOAT_EQ(4.0,result(0,1).val_.val());
  EXPECT_FLOAT_EQ(5.0,result(1,0).val_.val());
  EXPECT_FLOAT_EQ(6.0,result(1,1).val_.val());
  EXPECT_FLOAT_EQ(1.0,result(0,0).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(0,1).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(1,0).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(1,1).d_.val());
}
TEST(AgradFwdFvarVarMatrix,add_scalar_vector) {
  using stan::agrad::vector_fvv;
  using stan::math::add;

  vector_fvv v(4);
  v << 1, 2, 3, 4;
   v(0).d_ = 1.0;
   v(1).d_ = 1.0;
   v(2).d_ = 1.0;
   v(3).d_ = 1.0;
  vector_fvv result;

  result = add(2.0,v);
  EXPECT_FLOAT_EQ(3.0,result(0).val_.val());
  EXPECT_FLOAT_EQ(4.0,result(1).val_.val());
  EXPECT_FLOAT_EQ(5.0,result(2).val_.val());
  EXPECT_FLOAT_EQ(6.0,result(3).val_.val());
  EXPECT_FLOAT_EQ(1.0,result(0).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(1).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(2).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(3).d_.val());

  result = add(v,2.0);
  EXPECT_FLOAT_EQ(3.0,result(0).val_.val());
  EXPECT_FLOAT_EQ(4.0,result(1).val_.val());
  EXPECT_FLOAT_EQ(5.0,result(2).val_.val());
  EXPECT_FLOAT_EQ(6.0,result(3).val_.val());
  EXPECT_FLOAT_EQ(1.0,result(0).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(1).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(2).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(3).d_.val());
}
TEST(AgradFwdFvarVarMatrix,add_scalar_rowvector) {
  using stan::agrad::row_vector_fvv;
  using stan::math::add;

  row_vector_fvv v(4);
  v << 1, 2, 3, 4;
   v(0).d_ = 1.0;
   v(1).d_ = 1.0;
   v(2).d_ = 1.0;
   v(3).d_ = 1.0;
  row_vector_fvv result;

  result = add(2.0,v);
  EXPECT_FLOAT_EQ(3.0,result(0).val_.val());
  EXPECT_FLOAT_EQ(4.0,result(1).val_.val());
  EXPECT_FLOAT_EQ(5.0,result(2).val_.val());
  EXPECT_FLOAT_EQ(6.0,result(3).val_.val());
  EXPECT_FLOAT_EQ(1.0,result(0).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(1).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(2).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(3).d_.val());

  result = add(v,2.0);
  EXPECT_FLOAT_EQ(3.0,result(0).val_.val());
  EXPECT_FLOAT_EQ(4.0,result(1).val_.val());
  EXPECT_FLOAT_EQ(5.0,result(2).val_.val());
  EXPECT_FLOAT_EQ(6.0,result(3).val_.val());
  EXPECT_FLOAT_EQ(1.0,result(0).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(1).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(2).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(3).d_.val());
}
TEST(AgradFwdFvarVarMatrix, add_vector_vector) {
  using stan::math::add;
  using stan::math::vector_d;
  using stan::agrad::vector_fvv;

  vector_d vd_1(5);
  vector_d vd_2(5);
  vector_fvv vv_1(5);
  vector_fvv vv_2(5);
  
  vd_1 << 1, 2, 3, 4, 5;
  vv_1 << 1, 2, 3, 4, 5;
   vv_1(0).d_ = 1.0;
   vv_1(1).d_ = 1.0;
   vv_1(2).d_ = 1.0;
   vv_1(3).d_ = 1.0;
   vv_1(4).d_ = 1.0;
  vd_2 << 2, 3, 4, 5, 6;
  vv_2 << 2, 3, 4, 5, 6;
   vv_2(0).d_ = 1.0;
   vv_2(1).d_ = 1.0;
   vv_2(2).d_ = 1.0;
   vv_2(3).d_ = 1.0;
   vv_2(4).d_ = 1.0;
  
  vector_d expected_output(5);
  expected_output << 3, 5, 7, 9, 11;
  
  vector_d output_d;
  output_d = add(vd_1, vd_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_d(0));
  EXPECT_FLOAT_EQ(expected_output(1), output_d(1));
  EXPECT_FLOAT_EQ(expected_output(2), output_d(2));
  EXPECT_FLOAT_EQ(expected_output(3), output_d(3));
  EXPECT_FLOAT_EQ(expected_output(4), output_d(4));  

  vector_fvv output_v = add(vv_1, vd_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_v(0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1), output_v(1).val_.val());
  EXPECT_FLOAT_EQ(expected_output(2), output_v(2).val_.val());
  EXPECT_FLOAT_EQ(expected_output(3), output_v(3).val_.val());
  EXPECT_FLOAT_EQ(expected_output(4), output_v(4).val_.val()); 
  EXPECT_FLOAT_EQ(1.0, output_v(0).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(1).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(2).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(3).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(4).d_.val()); 

  output_v = add(vd_1, vv_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_v(0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1), output_v(1).val_.val());
  EXPECT_FLOAT_EQ(expected_output(2), output_v(2).val_.val());
  EXPECT_FLOAT_EQ(expected_output(3), output_v(3).val_.val());
  EXPECT_FLOAT_EQ(expected_output(4), output_v(4).val_.val()); 
  EXPECT_FLOAT_EQ(1.0, output_v(0).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(1).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(2).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(3).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(4).d_.val());   

  output_v = add(vv_1, vv_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_v(0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1), output_v(1).val_.val());
  EXPECT_FLOAT_EQ(expected_output(2), output_v(2).val_.val());
  EXPECT_FLOAT_EQ(expected_output(3), output_v(3).val_.val());
  EXPECT_FLOAT_EQ(expected_output(4), output_v(4).val_.val()); 
  EXPECT_FLOAT_EQ(2.0, output_v(0).d_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(1).d_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(2).d_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(3).d_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(4).d_.val());  
}
TEST(AgradFwdFvarVarMatrix, add_vector_vector_exception) {
  using stan::math::add;
  using stan::math::vector_d;
  using stan::agrad::vector_fvv;

  vector_d d1(5), d2(1);
  vector_fvv v1(5), v2(1);
  
  EXPECT_THROW(add(d1, d2), std::domain_error);
  EXPECT_THROW(add(v1, d2), std::domain_error);
  EXPECT_THROW(add(d1, v2), std::domain_error);
  EXPECT_THROW(add(v1, v2), std::domain_error);
}
TEST(AgradFwdFvarVarMatrix, add_rowvector_rowvector) {
  using stan::math::add;
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_fvv;

  row_vector_d rvd_1(5), rvd_2(5);
  row_vector_fvv rvv_1(5), rvv_2(5);

  rvd_1 << 1, 2, 3, 4, 5;
  rvv_1 << 1, 2, 3, 4, 5;
   rvv_1(0).d_ = 1.0;
   rvv_1(1).d_ = 1.0;
   rvv_1(2).d_ = 1.0;
   rvv_1(3).d_ = 1.0;
   rvv_1(4).d_ = 1.0;
  rvd_2 << 2, 3, 4, 5, 6;
  rvv_2 << 2, 3, 4, 5, 6;
   rvv_2(0).d_ = 1.0;
   rvv_2(1).d_ = 1.0;
   rvv_2(2).d_ = 1.0;
   rvv_2(3).d_ = 1.0;
   rvv_2(4).d_ = 1.0;
  
  row_vector_d expected_output(5);
  expected_output << 3, 5, 7, 9, 11;
  
  row_vector_d output_d = add(rvd_1, rvd_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_d(0));
  EXPECT_FLOAT_EQ(expected_output(1), output_d(1));
  EXPECT_FLOAT_EQ(expected_output(2), output_d(2));
  EXPECT_FLOAT_EQ(expected_output(3), output_d(3));
  EXPECT_FLOAT_EQ(expected_output(4), output_d(4));  

  row_vector_fvv output_v = add(rvv_1, rvd_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_v(0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1), output_v(1).val_.val());
  EXPECT_FLOAT_EQ(expected_output(2), output_v(2).val_.val());
  EXPECT_FLOAT_EQ(expected_output(3), output_v(3).val_.val());
  EXPECT_FLOAT_EQ(expected_output(4), output_v(4).val_.val());  
  EXPECT_FLOAT_EQ(1.0, output_v(0).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(1).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(2).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(3).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(4).d_.val());

  output_v = add(rvd_1, rvv_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_v(0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1), output_v(1).val_.val());
  EXPECT_FLOAT_EQ(expected_output(2), output_v(2).val_.val());
  EXPECT_FLOAT_EQ(expected_output(3), output_v(3).val_.val());
  EXPECT_FLOAT_EQ(expected_output(4), output_v(4).val_.val());  
  EXPECT_FLOAT_EQ(1.0, output_v(0).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(1).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(2).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(3).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(4).d_.val());

  output_v = add(rvv_1, rvv_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_v(0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1), output_v(1).val_.val());
  EXPECT_FLOAT_EQ(expected_output(2), output_v(2).val_.val());
  EXPECT_FLOAT_EQ(expected_output(3), output_v(3).val_.val());
  EXPECT_FLOAT_EQ(expected_output(4), output_v(4).val_.val());  
  EXPECT_FLOAT_EQ(2.0, output_v(0).d_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(1).d_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(2).d_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(3).d_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(4).d_.val());
}
TEST(AgradFwdFvarVarMatrix, add_rowvector_rowvector_exception) {
  using stan::math::add;
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_fvv;

  row_vector_d d1(5), d2(2);
  row_vector_fvv v1(5), v2(2);

  row_vector_fvv output;
  EXPECT_THROW( add(d1, d2), std::domain_error);
  EXPECT_THROW( add(d1, v2), std::domain_error);
  EXPECT_THROW( add(v1, d2), std::domain_error);
  EXPECT_THROW( add(v1, v2), std::domain_error);
}
TEST(AgradFwdFvarVarMatrix, add_matrix_matrix) {
  using stan::math::add;
  using stan::math::matrix_d;
  using stan::agrad::matrix_fvv;

  matrix_d md_1(2,2), md_2(2,2);
  matrix_fvv mv_1(2,2), mv_2(2,2);

  md_1 << -10, 1, 10, 0;
  mv_1 << -10, 1, 10, 0;
   mv_1(0,0).d_ = 1.0;
   mv_1(0,1).d_ = 1.0;
   mv_1(1,0).d_ = 1.0;
   mv_1(1,1).d_ = 1.0;
  md_2 << 10, -10, 1, 2;
  mv_2 << 10, -10, 1, 2;
   mv_2(0,0).d_ = 1.0;
   mv_2(0,1).d_ = 1.0;
   mv_2(1,0).d_ = 1.0;
   mv_2(1,1).d_ = 1.0;
  
  matrix_d expected_output(2,2);
  expected_output << 0, -9, 11, 2;
  
  matrix_d output_d = add(md_1, md_2);
  EXPECT_FLOAT_EQ(expected_output(0,0), output_d(0,0));
  EXPECT_FLOAT_EQ(expected_output(0,1), output_d(0,1));
  EXPECT_FLOAT_EQ(expected_output(1,0), output_d(1,0));
  EXPECT_FLOAT_EQ(expected_output(1,1), output_d(1,1));

  matrix_fvv output_v = add(mv_1, md_2);
  EXPECT_FLOAT_EQ(expected_output(0,0), output_v(0,0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(0,1), output_v(0,1).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1,0), output_v(1,0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1,1), output_v(1,1).val_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(0,0).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(0,1).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(1,0).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(1,1).d_.val());

  output_v = add(md_1, mv_2);
  EXPECT_FLOAT_EQ(expected_output(0,0), output_v(0,0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(0,1), output_v(0,1).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1,0), output_v(1,0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1,1), output_v(1,1).val_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(0,0).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(0,1).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(1,0).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(1,1).d_.val());

  output_v = add(mv_1, mv_2);
  EXPECT_FLOAT_EQ(expected_output(0,0), output_v(0,0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(0,1), output_v(0,1).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1,0), output_v(1,0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1,1), output_v(1,1).val_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(0,0).d_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(0,1).d_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(1,0).d_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(1,1).d_.val());
}
TEST(AgradFwdFvarVarMatrix, add_matrix_matrix_exception) {
  using stan::math::add;
  using stan::math::matrix_d;
  using stan::agrad::matrix_fvv;
  
  matrix_d d1(2,2), d2(1,2);
  matrix_fvv v1(2,2), v2(1,2);

  EXPECT_THROW(add(d1, d2), std::domain_error);
  EXPECT_THROW(add(d1, v2), std::domain_error);
  EXPECT_THROW(add(v1, d2), std::domain_error);
  EXPECT_THROW(add(v1, v2), std::domain_error);
}
TEST(AgradFwdFvarFvarMatrix,add_scalar_matrix) {
  using stan::agrad::matrix_ffv;
  using stan::math::add;

  fvar<fvar<double> > a,b,c,d;
  a.val_.val_ = 1.0;
  b.val_.val_ = 2.0;
  c.val_.val_ = 3.0;
  d.val_.val_ = 4.0;
  a.d_.val_ = 1.0;
  b.d_.val_ = 1.0;
  c.d_.val_ = 1.0;
  d.d_.val_ = 1.0;

  matrix_ffv v(2,2);
  v << a,b,c,d;
  matrix_ffv result;

  result = add(2.0,v);
  EXPECT_FLOAT_EQ(3.0,result(0,0).val_.val());
  EXPECT_FLOAT_EQ(4.0,result(0,1).val_.val());
  EXPECT_FLOAT_EQ(5.0,result(1,0).val_.val());
  EXPECT_FLOAT_EQ(6.0,result(1,1).val_.val());
  EXPECT_FLOAT_EQ(1.0,result(0,0).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(0,1).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(1,0).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(1,1).d_.val());

  result = add(v,2.0);
  EXPECT_FLOAT_EQ(3.0,result(0,0).val_.val());
  EXPECT_FLOAT_EQ(4.0,result(0,1).val_.val());
  EXPECT_FLOAT_EQ(5.0,result(1,0).val_.val());
  EXPECT_FLOAT_EQ(6.0,result(1,1).val_.val());
  EXPECT_FLOAT_EQ(1.0,result(0,0).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(0,1).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(1,0).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(1,1).d_.val());
}
TEST(AgradFwdFvarFvarMatrix,add_scalar_vector) {
  using stan::agrad::vector_ffv;
  using stan::math::add;

  fvar<fvar<double> > a,b,c,d;
  a.val_.val_ = 1.0;
  b.val_.val_ = 2.0;
  c.val_.val_ = 3.0;
  d.val_.val_ = 4.0;
  a.d_.val_ = 1.0;
  b.d_.val_ = 1.0;
  c.d_.val_ = 1.0;
  d.d_.val_ = 1.0;

  vector_ffv v(4);
  v << a,b,c,d;
  vector_ffv result;

  result = add(2.0,v);
  EXPECT_FLOAT_EQ(3.0,result(0).val_.val());
  EXPECT_FLOAT_EQ(4.0,result(1).val_.val());
  EXPECT_FLOAT_EQ(5.0,result(2).val_.val());
  EXPECT_FLOAT_EQ(6.0,result(3).val_.val());
  EXPECT_FLOAT_EQ(1.0,result(0).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(1).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(2).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(3).d_.val());

  result = add(v,2.0);
  EXPECT_FLOAT_EQ(3.0,result(0).val_.val());
  EXPECT_FLOAT_EQ(4.0,result(1).val_.val());
  EXPECT_FLOAT_EQ(5.0,result(2).val_.val());
  EXPECT_FLOAT_EQ(6.0,result(3).val_.val());
  EXPECT_FLOAT_EQ(1.0,result(0).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(1).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(2).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(3).d_.val());
}
TEST(AgradFwdFvarFvarMatrix,add_scalar_rowvector) {
  using stan::agrad::row_vector_ffv;
  using stan::math::add;

  fvar<fvar<double> > a,b,c,d;
  a.val_.val_ = 1.0;
  b.val_.val_ = 2.0;
  c.val_.val_ = 3.0;
  d.val_.val_ = 4.0;
  a.d_.val_ = 1.0;
  b.d_.val_ = 1.0;
  c.d_.val_ = 1.0;
  d.d_.val_ = 1.0;

  row_vector_ffv v(4);
  v << a,b,c,d;
  row_vector_ffv result;

  result = add(2.0,v);
  EXPECT_FLOAT_EQ(3.0,result(0).val_.val());
  EXPECT_FLOAT_EQ(4.0,result(1).val_.val());
  EXPECT_FLOAT_EQ(5.0,result(2).val_.val());
  EXPECT_FLOAT_EQ(6.0,result(3).val_.val());
  EXPECT_FLOAT_EQ(1.0,result(0).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(1).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(2).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(3).d_.val());

  result = add(v,2.0);
  EXPECT_FLOAT_EQ(3.0,result(0).val_.val());
  EXPECT_FLOAT_EQ(4.0,result(1).val_.val());
  EXPECT_FLOAT_EQ(5.0,result(2).val_.val());
  EXPECT_FLOAT_EQ(6.0,result(3).val_.val());
  EXPECT_FLOAT_EQ(1.0,result(0).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(1).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(2).d_.val());
  EXPECT_FLOAT_EQ(1.0,result(3).d_.val());
}
TEST(AgradFwdFvarFvarMatrix, add_vector_vector) {
  using stan::math::add;
  using stan::math::vector_d;
  using stan::agrad::vector_ffv;

  vector_d vd_1(5);
  vector_d vd_2(5);
  vector_ffv vv_1(5);
  vector_ffv vv_2(5);
  
  fvar<fvar<double> > a,b,c,d,e,f;
  a.val_.val_ = 1.0;
  b.val_.val_ = 2.0;
  c.val_.val_ = 3.0;
  d.val_.val_ = 4.0;
  e.val_.val_ = 5.0;
  f.val_.val_ = 6.0;
  a.d_.val_ = 1.0;
  b.d_.val_ = 1.0;
  c.d_.val_ = 1.0;
  d.d_.val_ = 1.0;
  e.d_.val_ = 1.0;
  f.d_.val_ = 1.0;

  vd_1 << 1, 2, 3, 4, 5;
  vv_1 << a,b,c,d,e;
  vd_2 << 2, 3, 4, 5, 6;
  vv_2 << b,c,d,e,f;
  
  vector_d expected_output(5);
  expected_output << 3, 5, 7, 9, 11;
  
  vector_d output_d;
  output_d = add(vd_1, vd_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_d(0));
  EXPECT_FLOAT_EQ(expected_output(1), output_d(1));
  EXPECT_FLOAT_EQ(expected_output(2), output_d(2));
  EXPECT_FLOAT_EQ(expected_output(3), output_d(3));
  EXPECT_FLOAT_EQ(expected_output(4), output_d(4));  

  vector_ffv output_v = add(vv_1, vd_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_v(0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1), output_v(1).val_.val());
  EXPECT_FLOAT_EQ(expected_output(2), output_v(2).val_.val());
  EXPECT_FLOAT_EQ(expected_output(3), output_v(3).val_.val());
  EXPECT_FLOAT_EQ(expected_output(4), output_v(4).val_.val()); 
  EXPECT_FLOAT_EQ(1.0, output_v(0).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(1).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(2).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(3).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(4).d_.val()); 

  output_v = add(vd_1, vv_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_v(0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1), output_v(1).val_.val());
  EXPECT_FLOAT_EQ(expected_output(2), output_v(2).val_.val());
  EXPECT_FLOAT_EQ(expected_output(3), output_v(3).val_.val());
  EXPECT_FLOAT_EQ(expected_output(4), output_v(4).val_.val()); 
  EXPECT_FLOAT_EQ(1.0, output_v(0).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(1).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(2).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(3).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(4).d_.val());   

  output_v = add(vv_1, vv_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_v(0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1), output_v(1).val_.val());
  EXPECT_FLOAT_EQ(expected_output(2), output_v(2).val_.val());
  EXPECT_FLOAT_EQ(expected_output(3), output_v(3).val_.val());
  EXPECT_FLOAT_EQ(expected_output(4), output_v(4).val_.val()); 
  EXPECT_FLOAT_EQ(2.0, output_v(0).d_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(1).d_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(2).d_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(3).d_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(4).d_.val());  
}
TEST(AgradFwdFvarFvarMatrix, add_vector_vector_exception) {
  using stan::math::add;
  using stan::math::vector_d;
  using stan::agrad::vector_ffv;

  vector_d d1(5), d2(1);
  vector_ffv v1(5), v2(1);
  
  EXPECT_THROW(add(d1, d2), std::domain_error);
  EXPECT_THROW(add(v1, d2), std::domain_error);
  EXPECT_THROW(add(d1, v2), std::domain_error);
  EXPECT_THROW(add(v1, v2), std::domain_error);
}
TEST(AgradFwdFvarFvarMatrix, add_rowvector_rowvector) {
  using stan::math::add;
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_ffv;

  row_vector_d rvd_1(5), rvd_2(5);
  row_vector_ffv rvv_1(5), rvv_2(5);

  fvar<fvar<double> > a,b,c,d,e,f;
  a.val_.val_ = 1.0;
  b.val_.val_ = 2.0;
  c.val_.val_ = 3.0;
  d.val_.val_ = 4.0;
  e.val_.val_ = 5.0;
  f.val_.val_ = 6.0;
  a.d_.val_ = 1.0;
  b.d_.val_ = 1.0;
  c.d_.val_ = 1.0;
  d.d_.val_ = 1.0;
  e.d_.val_ = 1.0;
  f.d_.val_ = 1.0;

  rvd_1 << 1, 2, 3, 4, 5;
  rvv_1 << a,b,c,d,e;
  rvd_2 << 2, 3, 4, 5, 6;
  rvv_2 << b,c,d,e,f;
  
  row_vector_d expected_output(5);
  expected_output << 3, 5, 7, 9, 11;
  
  row_vector_d output_d = add(rvd_1, rvd_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_d(0));
  EXPECT_FLOAT_EQ(expected_output(1), output_d(1));
  EXPECT_FLOAT_EQ(expected_output(2), output_d(2));
  EXPECT_FLOAT_EQ(expected_output(3), output_d(3));
  EXPECT_FLOAT_EQ(expected_output(4), output_d(4));  

  row_vector_ffv output_v = add(rvv_1, rvd_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_v(0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1), output_v(1).val_.val());
  EXPECT_FLOAT_EQ(expected_output(2), output_v(2).val_.val());
  EXPECT_FLOAT_EQ(expected_output(3), output_v(3).val_.val());
  EXPECT_FLOAT_EQ(expected_output(4), output_v(4).val_.val());  
  EXPECT_FLOAT_EQ(1.0, output_v(0).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(1).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(2).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(3).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(4).d_.val());

  output_v = add(rvd_1, rvv_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_v(0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1), output_v(1).val_.val());
  EXPECT_FLOAT_EQ(expected_output(2), output_v(2).val_.val());
  EXPECT_FLOAT_EQ(expected_output(3), output_v(3).val_.val());
  EXPECT_FLOAT_EQ(expected_output(4), output_v(4).val_.val());  
  EXPECT_FLOAT_EQ(1.0, output_v(0).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(1).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(2).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(3).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(4).d_.val());

  output_v = add(rvv_1, rvv_2);
  EXPECT_FLOAT_EQ(expected_output(0), output_v(0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1), output_v(1).val_.val());
  EXPECT_FLOAT_EQ(expected_output(2), output_v(2).val_.val());
  EXPECT_FLOAT_EQ(expected_output(3), output_v(3).val_.val());
  EXPECT_FLOAT_EQ(expected_output(4), output_v(4).val_.val());  
  EXPECT_FLOAT_EQ(2.0, output_v(0).d_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(1).d_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(2).d_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(3).d_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(4).d_.val());
}
TEST(AgradFwdFvarFvarMatrix, add_rowvector_rowvector_exception) {
  using stan::math::add;
  using stan::math::row_vector_d;
  using stan::agrad::row_vector_ffv;

  row_vector_d d1(5), d2(2);
  row_vector_ffv v1(5), v2(2);

  row_vector_ffv output;
  EXPECT_THROW( add(d1, d2), std::domain_error);
  EXPECT_THROW( add(d1, v2), std::domain_error);
  EXPECT_THROW( add(v1, d2), std::domain_error);
  EXPECT_THROW( add(v1, v2), std::domain_error);
}
TEST(AgradFwdFvarFvarMatrix, add_matrix_matrix) {
  using stan::math::add;
  using stan::math::matrix_d;
  using stan::agrad::matrix_ffv;

  matrix_d md_1(2,2), md_2(2,2);
  matrix_ffv mv_1(2,2), mv_2(2,2);

  fvar<fvar<double> > a,b,c,d,e;
  a.val_.val_ = -10.0;
  b.val_.val_ = 1.0;
  c.val_.val_ = 10.0;
  d.val_.val_ = 0.0;
  e.val_.val_ = 2.0;
  a.d_.val_ = 1.0;
  b.d_.val_ = 1.0;
  c.d_.val_ = 1.0;
  d.d_.val_ = 1.0;
  e.d_.val_ = 1.0;

  md_1 << -10, 1, 10, 0;
  mv_1 << a,b,c,d;
  md_2 << 10, -10, 1, 2;
  mv_2 << c,a,b,e;
  
  matrix_d expected_output(2,2);
  expected_output << 0, -9, 11, 2;
  
  matrix_d output_d = add(md_1, md_2);
  EXPECT_FLOAT_EQ(expected_output(0,0), output_d(0,0));
  EXPECT_FLOAT_EQ(expected_output(0,1), output_d(0,1));
  EXPECT_FLOAT_EQ(expected_output(1,0), output_d(1,0));
  EXPECT_FLOAT_EQ(expected_output(1,1), output_d(1,1));

  matrix_ffv output_v = add(mv_1, md_2);
  EXPECT_FLOAT_EQ(expected_output(0,0), output_v(0,0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(0,1), output_v(0,1).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1,0), output_v(1,0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1,1), output_v(1,1).val_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(0,0).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(0,1).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(1,0).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(1,1).d_.val());

  output_v = add(md_1, mv_2);
  EXPECT_FLOAT_EQ(expected_output(0,0), output_v(0,0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(0,1), output_v(0,1).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1,0), output_v(1,0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1,1), output_v(1,1).val_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(0,0).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(0,1).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(1,0).d_.val());
  EXPECT_FLOAT_EQ(1.0, output_v(1,1).d_.val());

  output_v = add(mv_1, mv_2);
  EXPECT_FLOAT_EQ(expected_output(0,0), output_v(0,0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(0,1), output_v(0,1).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1,0), output_v(1,0).val_.val());
  EXPECT_FLOAT_EQ(expected_output(1,1), output_v(1,1).val_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(0,0).d_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(0,1).d_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(1,0).d_.val());
  EXPECT_FLOAT_EQ(2.0, output_v(1,1).d_.val());
}
TEST(AgradFwdFvarFvarMatrix, add_matrix_matrix_exception) {
  using stan::math::add;
  using stan::math::matrix_d;
  using stan::agrad::matrix_ffv;
  
  matrix_d d1(2,2), d2(1,2);
  matrix_ffv v1(2,2), v2(1,2);

  EXPECT_THROW(add(d1, d2), std::domain_error);
  EXPECT_THROW(add(d1, v2), std::domain_error);
  EXPECT_THROW(add(v1, d2), std::domain_error);
  EXPECT_THROW(add(v1, v2), std::domain_error);
}
