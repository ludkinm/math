#include <stan/math/mix.hpp>
#include <gtest/gtest.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/math/distributions.hpp>

TEST(ProbDistributionsMultiNormal, fvar_var) {
  using Eigen::Dynamic;
  using Eigen::Matrix;
  using stan::math::fvar;
  using stan::math::var;
  using std::vector;

  Matrix<fvar<var>, Dynamic, 1> y(3, 1);
  y << 2.0, -2.0, 11.0;
  Matrix<fvar<var>, Dynamic, 1> mu(3, 1);
  mu << 1.0, -1.0, 3.0;
  Matrix<fvar<var>, Dynamic, Dynamic> Sigma(3, 3);
  Sigma << 9.0, -3.0, 0.0, -3.0, 4.0, 0.0, 0.0, 0.0, 5.0;
  for (int i = 0; i < 3; i++) {
    y(i).d_ = 1.0;
    mu(i).d_ = 1.0;
    for (int j = 0; j < 3; j++)
      Sigma(i, j).d_ = 1.0;
  }

  fvar<var> res = stan::math::multi_normal_log(y, mu, Sigma);
  EXPECT_FLOAT_EQ(-11.73908, res.val_.val());
  EXPECT_FLOAT_EQ(0.54899865, res.d_.val());
}

TEST(ProbDistributionsMultiNormal, fvar_fvar_var) {
  using Eigen::Dynamic;
  using Eigen::Matrix;
  using stan::math::fvar;
  using stan::math::var;
  using std::vector;

  Matrix<fvar<fvar<var> >, Dynamic, 1> y(3, 1);
  y << 2.0, -2.0, 11.0;
  Matrix<fvar<fvar<var> >, Dynamic, 1> mu(3, 1);
  mu << 1.0, -1.0, 3.0;
  Matrix<fvar<fvar<var> >, Dynamic, Dynamic> Sigma(3, 3);
  Sigma << 9.0, -3.0, 0.0, -3.0, 4.0, 0.0, 0.0, 0.0, 5.0;
  for (int i = 0; i < 3; i++) {
    y(i).d_ = 1.0;
    mu(i).d_ = 1.0;
    for (int j = 0; j < 3; j++)
      Sigma(i, j).d_ = 1.0;
  }

  fvar<fvar<var> > res = stan::math::multi_normal_log(y, mu, Sigma);
  EXPECT_FLOAT_EQ(-11.73908, res.val_.val_.val());
  EXPECT_FLOAT_EQ(0.54899865, res.d_.val_.val());
}
