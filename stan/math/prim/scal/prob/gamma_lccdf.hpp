#ifndef STAN_MATH_PRIM_SCAL_PROB_GAMMA_LCCDF_HPP
#define STAN_MATH_PRIM_SCAL_PROB_GAMMA_LCCDF_HPP

#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/scal/err/check_consistent_sizes.hpp>
#include <stan/math/prim/scal/err/check_nonnegative.hpp>
#include <stan/math/prim/scal/err/check_not_nan.hpp>
#include <stan/math/prim/scal/err/check_positive_finite.hpp>
#include <stan/math/prim/scal/fun/size_zero.hpp>
#include <stan/math/prim/scal/fun/constants.hpp>
#include <stan/math/prim/scal/fun/value_of.hpp>
#include <stan/math/prim/scal/fun/gamma_q.hpp>
#include <stan/math/prim/scal/fun/digamma.hpp>
#include <stan/math/prim/scal/fun/tgamma.hpp>
#include <stan/math/prim/scal/fun/grad_reg_inc_gamma.hpp>
#include <cmath>
#include <limits>

namespace stan {
namespace math {

template <typename T_y, typename T_shape, typename T_inv_scale>
inline auto gamma_lccdf(const T_y& y, const T_shape& alpha,
                        const T_inv_scale& beta) {
  using T_partials = partials_return_t<T_y, T_shape, T_inv_scale>;
  T_partials P(0.0);

  using std::exp;
  using std::log;
  using std::pow;

  static const char* function = "gamma_lccdf";
  check_positive_finite(function, "Shape parameter", alpha);
  check_positive_finite(function, "Inverse scale parameter", beta);
  check_not_nan(function, "Random variable", y);
  check_nonnegative(function, "Random variable", y);
  check_consistent_sizes(function, "Random variable", y, "Shape parameter",
                         alpha, "Inverse scale parameter", beta);

  const scalar_seq_view<T_y> y_vec(y);
  const scalar_seq_view<T_shape> alpha_vec(alpha);
  const scalar_seq_view<T_inv_scale> beta_vec(beta);
  const size_t N = max_size(y, alpha, beta);
  operands_and_partials<T_y, T_shape, T_inv_scale> ops_partials(y, alpha, beta);
  if (size_zero(y, alpha, beta)) {
    return ops_partials.build(P);
  }

  // Explicit return for extreme values
  // The gradients are technically ill-defined, but treated as zero
  for (size_t i = 0; i < stan::length(y); i++) {
    if (value_of(y_vec[i]) == 0) {
      return ops_partials.build(P);
    }
  }

  VectorBuilder<!is_constant_all<T_shape>::value, T_partials, T_shape>
      gamma_vec(stan::length(alpha));
  VectorBuilder<!is_constant_all<T_shape>::value, T_partials, T_shape>
      digamma_vec(stan::length(alpha));

  if (!is_constant_all<T_shape>::value) {
    for (size_t i = 0; i < stan::length(alpha); i++) {
      const T_partials alpha_dbl = value_of(alpha_vec[i]);
      gamma_vec[i] = tgamma(alpha_dbl);
      digamma_vec[i] = digamma(alpha_dbl);
    }
  }

  for (size_t n = 0; n < N; n++) {
    // Explicit results for extreme values
    // The gradients are technically ill-defined, but treated as zero
    if (value_of(y_vec[n]) == std::numeric_limits<double>::infinity()) {
      return ops_partials.build(negative_infinity());
    }

    const T_partials y_dbl = value_of(y_vec[n]);
    const T_partials alpha_dbl = value_of(alpha_vec[n]);
    const T_partials beta_dbl = value_of(beta_vec[n]);

    const T_partials Pn = gamma_q(alpha_dbl, beta_dbl * y_dbl);

    P += log(Pn);

    if (!is_constant_all<T_y>::value) {
      ops_partials.edge1_.partials_[n] -= beta_dbl * exp(-beta_dbl * y_dbl)
                                          * pow(beta_dbl * y_dbl, alpha_dbl - 1)
                                          / tgamma(alpha_dbl) / Pn;
    }
    if (!is_constant_all<T_shape>::value) {
      ops_partials.edge2_.partials_[n]
          += grad_reg_inc_gamma(alpha_dbl, beta_dbl * y_dbl, gamma_vec[n],
                                digamma_vec[n])
             / Pn;
    }
    if (!is_constant_all<T_inv_scale>::value) {
      ops_partials.edge3_.partials_[n] -= y_dbl * exp(-beta_dbl * y_dbl)
                                          * pow(beta_dbl * y_dbl, alpha_dbl - 1)
                                          / tgamma(alpha_dbl) / Pn;
    }
  }
  return ops_partials.build(P);
}

}  // namespace math
}  // namespace stan

#endif
