#ifndef STAN_MATH_PRIM_FUN_SQRT_HPP
#define STAN_MATH_PRIM_FUN_SQRT_HPP

#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/fun/Eigen.hpp>
#include <cmath>

namespace stan {
namespace math {

/**
 * Structure to wrap `sqrt()` so that it can be vectorized.
 *
 * @tparam T type of variable
 * @param x variable
 * @return Square root of x.
 */
struct sqrt_fun {
  template <typename T>
  static inline T fun(const T& x) {
    using std::sqrt;
    return sqrt(x);
  }
};

/**
 * Vectorized version of `sqrt()`.
 *
 * @tparam Container type of container
 * @param x container
 * @return Square root of each value in x.
 */
template <typename Container,
          require_not_container_st<std::is_arithmetic, Container>* = nullptr>
inline auto sqrt(const Container& x) {
  return apply_scalar_unary<sqrt_fun, Container>::apply(x);
}

/**
 * Version of `sqrt()` that accepts std::vectors, Eigen Matrix/Array objects
 *  or expressions, and containers of these.
 *
 * @tparam Container Type of x
 * @param x Container
 * @return Square root of each value in x.
 */
template <typename Container,
          require_container_st<std::is_arithmetic, Container>* = nullptr>
inline auto sqrt(const Container& x) {
  return apply_vector_unary<Container>::apply(
      x, [](const auto& v) { return v.array().sqrt(); });
}

}  // namespace math
}  // namespace stan

#endif
