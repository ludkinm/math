#ifndef STAN_MATH_OPENCL_KERNEL_GENERATOR_UNARY_FUNCTION_HPP
#define STAN_MATH_OPENCL_KERNEL_GENERATOR_UNARY_FUNCTION_HPP
#ifdef STAN_OPENCL

#include <stan/math/opencl/matrix_cl_view.hpp>
#include <stan/math/opencl/err/check_matching_dims.hpp>
#include <stan/math/prim/meta.hpp>
#include <stan/math/opencl/kernel_generator/type_str.hpp>
#include <stan/math/opencl/kernel_generator/name_generator.hpp>
#include <stan/math/opencl/kernel_generator/operation_cl.hpp>
#include <stan/math/opencl/kernel_generator/as_operation_cl.hpp>
#include <stan/math/opencl/kernel_generator/is_valid_expression.hpp>
#include <string>
#include <type_traits>
#include <set>
#include <utility>

namespace stan {
namespace math {

/**
 * Represents a unary function in kernel generator expressions.
 * @tparam Derived derived type
 * @tparam T type of argument
 */
template <typename Derived, typename T>
class unary_function
    : public operation_cl<
          Derived, typename std::remove_reference_t<T>::ReturnScalar, T> {
 public:
  using ReturnScalar = typename std::remove_reference_t<T>::ReturnScalar;
  static_assert(std::is_floating_point<ReturnScalar>::value,
                "unary_function: argument must be expression with floating "
                "point return type!");
  using base = operation_cl<Derived, ReturnScalar, T>;
  using base::var_name;

  /**
   * Constructor
   * @param a argument expression
   * @param fun function
   */
  unary_function(T&& a, const std::string& fun)
      : base(std::forward<T>(a)), fun_(fun) {}

  /**
   * generates kernel code for this expression.
   * @param i row index variable name
   * @param j column index variable name
   * @param var_name_arg variable name of the nested expression
   * @return part of kernel with code for this expression
   */
  inline kernel_parts generate(const std::string& i, const std::string& j,
                               const std::string& var_name_arg) const {
    kernel_parts res{};
    res.body = type_str<ReturnScalar>() + " " + var_name + " = " + fun_ + "("
               + var_name_arg + ");\n";
    return res;
  }

  /**
   * View of a matrix that would be the result of evaluating this expression.
   * @return view
   */
  inline matrix_cl_view view() const {
    return std::get<0>(base::arguments_).view();
  }

 protected:
  std::string fun_;
};

/**
 * generates a class and function for an unary function.
 * @param fun function
 */
#define ADD_UNARY_FUNCTION(fun)                                                \
  template <typename T>                                                        \
  class fun##__ : public unary_function<fun##__<T>, T> {                       \
   public:                                                                     \
    explicit fun##__(T&& a)                                                    \
        : unary_function<fun##__<T>, T>(std::forward<T>(a), #fun) {}           \
    inline matrix_cl_view view() const { return matrix_cl_view::Entire; }      \
  };                                                                           \
                                                                               \
  template <typename T, typename Cond                                          \
                        = require_all_valid_expressions_and_none_scalar_t<T>>  \
  inline fun##__<as_operation_cl_t<T>> fun(T&& a) {                            \
    return fun##__<as_operation_cl_t<T>>(as_operation_cl(std::forward<T>(a))); \
  }

/**
 * generates a class and function for an unary function that passes trough
 * zeros.
 * @param fun function
 */
#define ADD_UNARY_FUNCTION_PASS_ZERO(fun)                                      \
  template <typename T>                                                        \
  class fun##__ : public unary_function<fun##__<T>, T> {                       \
   public:                                                                     \
    explicit fun##__(T&& a)                                                    \
        : unary_function<fun##__<T>, T>(std::forward<T>(a), #fun) {}           \
  };                                                                           \
                                                                               \
  template <typename T, typename Cond                                          \
                        = require_all_valid_expressions_and_none_scalar_t<T>>  \
  inline fun##__<as_operation_cl_t<T>> fun(T&& a) {                            \
    return fun##__<as_operation_cl_t<T>>(as_operation_cl(std::forward<T>(a))); \
  }

ADD_UNARY_FUNCTION(rsqrt)
ADD_UNARY_FUNCTION_PASS_ZERO(sqrt)
ADD_UNARY_FUNCTION_PASS_ZERO(cbrt)

ADD_UNARY_FUNCTION(exp)
ADD_UNARY_FUNCTION(exp2)
ADD_UNARY_FUNCTION_PASS_ZERO(expm1)

ADD_UNARY_FUNCTION(log)
ADD_UNARY_FUNCTION(log2)
ADD_UNARY_FUNCTION(log10)
ADD_UNARY_FUNCTION_PASS_ZERO(log1p)

ADD_UNARY_FUNCTION_PASS_ZERO(sin)
ADD_UNARY_FUNCTION_PASS_ZERO(sinh)
ADD_UNARY_FUNCTION(cos)
ADD_UNARY_FUNCTION(cosh)
ADD_UNARY_FUNCTION_PASS_ZERO(tan)
ADD_UNARY_FUNCTION_PASS_ZERO(tanh)
ADD_UNARY_FUNCTION_PASS_ZERO(asin)
ADD_UNARY_FUNCTION_PASS_ZERO(asinh)
ADD_UNARY_FUNCTION(acos)
ADD_UNARY_FUNCTION(acosh)
ADD_UNARY_FUNCTION_PASS_ZERO(atan)
ADD_UNARY_FUNCTION_PASS_ZERO(atanh)

ADD_UNARY_FUNCTION(tgamma)
ADD_UNARY_FUNCTION(lgamma)
ADD_UNARY_FUNCTION_PASS_ZERO(erf)
ADD_UNARY_FUNCTION(erfc)

ADD_UNARY_FUNCTION_PASS_ZERO(floor)
ADD_UNARY_FUNCTION_PASS_ZERO(round)
ADD_UNARY_FUNCTION_PASS_ZERO(ceil)

#undef ADD_UNARY_FUNCTION
#undef ADD_UNARY_FUNCTION_PASS_ZERO

}  // namespace math
}  // namespace stan
#endif
#endif
