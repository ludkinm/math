#ifndef STAN_MATH_PRIM_SCAL_PROB_NEG_BINOMIAL_2_LCCDF_HPP
#define STAN_MATH_PRIM_SCAL_PROB_NEG_BINOMIAL_2_LCCDF_HPP

#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/scal/err/check_consistent_sizes.hpp>
#include <stan/math/prim/scal/err/check_not_nan.hpp>
#include <stan/math/prim/scal/err/check_positive_finite.hpp>
#include <stan/math/prim/scal/fun/size_zero.hpp>
#include <stan/math/prim/scal/prob/neg_binomial_ccdf_log.hpp>

namespace stan {
namespace math {

// Temporary neg_binomial_2_ccdf implementation that
// transforms the input parameters and calls neg_binomial_ccdf
template <typename T_n, typename T_location, typename T_precision>
inline auto neg_binomial_2_lccdf(const T_n& n, const T_location& mu,
                                 const T_precision& phi) {
  using T_partials = partials_return_t<T_n, T_location, T_precision>;
  using T_return = return_type_t<T_n, T_location, T_precision>;

  static const char* function = "neg_binomial_2_lccdf";
  check_positive_finite(function, "Location parameter", mu);
  check_positive_finite(function, "Precision parameter", phi);
  check_not_nan(function, "Random variable", n);
  check_consistent_sizes(function, "Random variable", n, "Location parameter",
                         mu, "Precision Parameter", phi);

  const scalar_seq_view<T_location> mu_vec(mu);
  const scalar_seq_view<T_precision> phi_vec(phi);
  const size_t size_beta = max_size(mu, phi);

  if (size_zero(n, mu, phi)) {
    return T_return(0.0);
  }

  VectorBuilder<true, return_type_t<T_location, T_precision>, T_location,
                T_precision>
      beta_vec(size_beta);
  for (size_t i = 0; i < size_beta; ++i) {
    beta_vec[i] = phi_vec[i] / mu_vec[i];
  }

  return neg_binomial_ccdf_log(n, phi, beta_vec.data());
}

}  // namespace math
}  // namespace stan
#endif
