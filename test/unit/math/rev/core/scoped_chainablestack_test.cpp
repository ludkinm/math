#include <stan/math/rev/core.hpp>
#include <test/unit/math/rev/core/gradable.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <memory>

struct AgradLocalScoped : public testing::Test {
  void SetUp() {
    // make sure memory's clean before starting each test
    stan::math::recover_memory();
  }
};

TEST_F(AgradLocalScoped, scoped_chainablestack_base) {
  using stan::math::ScopedChainableStack;
  using stan::math::nested_rev_autodiff;
  using stan::math::var;

  ScopedChainableStack scoped_stack;

  {
    nested_rev_autodiff nested;

    double cgrad_a = scoped_stack.execute([] {
      stan::math::start_nested();
      var a = 2.0;
      var b = 4.0;
      var c = a * a + b;
      c.grad();
      EXPECT_GT(stan::math::nested_size(), 0);
      return a.adj();
    });
    EXPECT_FLOAT_EQ(cgrad_a, 4.0);

    EXPECT_EQ(stan::math::nested_size(), 0);
  }

  // the nested autodiff stack went out of scope, but that did not
  // touch the scoped stack

  scoped_stack.execute([] { EXPECT_GT(stan::math::nested_size(), 0); });
}

TEST_F(AgradLocalScoped, scoped_chainablestack_simple) {
  using stan::math::ScopedChainableStack;
  using stan::math::nested_rev_autodiff;

  ScopedChainableStack scoped_stack;

  nested_rev_autodiff nested;

  scoped_stack.execute([] {
    gradable g_out = setup_simple();
    g_out.test();
  });

  EXPECT_EQ(stan::math::nested_size(), 0);
}

TEST_F(AgradLocalScoped, scoped_chainablestack_holder) {
  using stan::math::ScopedChainableStack;
  using stan::math::nested_rev_autodiff;

  ScopedChainableStack scoped_stack;

  nested_rev_autodiff nested;

  std::unique_ptr<gradable> holder = scoped_stack.execute(
      [] { return std::make_unique<gradable>(gradable(setup_simple())); });

  EXPECT_EQ(stan::math::nested_size(), 0);

  scoped_stack.execute([&] { holder->test(); });

  EXPECT_FLOAT_EQ(holder->adj(), 1.0);

  nested.set_zero_all_adjoints();

  EXPECT_FLOAT_EQ(holder->adj(), 1.0);

  scoped_stack.execute([] { stan::math::set_zero_all_adjoints(); });

  EXPECT_FLOAT_EQ(holder->adj(), 0.0);
}

TEST_F(AgradLocalScoped, scoped_chainablestack_nesting) {
  using stan::math::ScopedChainableStack;
  using stan::math::nested_rev_autodiff;
  using stan::math::var;

  ScopedChainableStack scoped_stack;
  ScopedChainableStack nested_scoped_stack;

  EXPECT_NO_THROW(scoped_stack.execute([&] {
    double cgrad_a = nested_scoped_stack.execute([] {
      var a = 2.0;
      var b = 4.0;
      var c = a * a + b;
      c.grad();
      return a.adj();
    });
    return cgrad_a;
  }));

  EXPECT_THROW(scoped_stack.execute([&] {
    double cgrad_a = scoped_stack.execute([] {
      var a = 2.0;
      var b = 4.0;
      var c = a * a + b;
      c.grad();
      return a.adj();
    });
    return cgrad_a;
  }),
               std::logic_error);
}
