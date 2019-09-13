#ifndef STAN_MATH_PRIM_SCAL_PROB_GUMBEL_LOG_HPP
#define STAN_MATH_PRIM_SCAL_PROB_GUMBEL_LOG_HPP

#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/scal/prob/gumbel_lpdf.hpp>

namespace stan {
namespace math {

/**
 * @deprecated use <code>gumbel_lpdf</code>
 */
template <bool propto, typename T_y, typename T_loc, typename T_scale>
inline auto gumbel_log(const T_y& y, const T_loc& mu, const T_scale& beta) {
  return gumbel_lpdf<propto>(y, mu, beta);
}

/**
 * @deprecated use <code>gumbel_lpdf</code>
 */
template <typename T_y, typename T_loc, typename T_scale>
inline auto gumbel_log(const T_y& y, const T_loc& mu, const T_scale& beta) {
  return gumbel_lpdf(y, mu, beta);
}

}  // namespace math
}  // namespace stan
#endif
