#include <gtest/gtest.h>

#include "backend/model.h"

using namespace s21;

TEST(calc_test, pow_acos_tan_test) {
  Model model;
  std::string src = "4^o(x/4)/t(2*x)";
  double x_text = 1.2;
  double result = model.calculate(src, x_text);
  double real_result = -6.31492;
  EXPECT_TRUE(fabs(result) - fabs(real_result) <= 0.0000001);
}

TEST(calc_test, unar_test) {
  Model model;
  std::string src = "-2+(3-6)-(-3+4)+2^3^2";
  double x_text = 0.0;
  double result = model.calculate(src, x_text);
  double real_result = 506;
  EXPECT_TRUE(fabs(result) - fabs(real_result) <= 0.0000001);
}

TEST(calc_test, mod_test) {
  Model model;
  std::string src = "102m100";
  std::string src2 = "102m0";
  double result = model.calculate(src, 0);
  double real_result = 2;
  EXPECT_TRUE(fabs(result) - fabs(real_result) <= 0.0000001);
  EXPECT_THROW(model.calculate(src2, 0), std::invalid_argument);
}

TEST(calc_test, log_test) {
  Model model;
  std::string src = "l(x)+0.3/3";
  double x_text = -2;
  double x_text_2 = 12;
  EXPECT_THROW(model.calculate(src, x_text), std::invalid_argument);
  double result = model.calculate(src, x_text_2);
  double real_result = 2.584907;
  EXPECT_TRUE(fabs(result) - fabs(real_result) <= 0.0000001);
}

TEST(calc_test, cos_mod_test) {
  Model model;
  std::string src = "c(10m2.2)";
  double result = model.calculate(src, 0);
  double real_result = 0.362358;
  EXPECT_TRUE(fabs(result) - fabs(real_result) <= 0.0000001);
}

TEST(calc_test, sqrt_test) {
  Model model;
  std::string src = "q(x)";
  double x_text = -2;
  double x_text_2 = 20;
  EXPECT_THROW(model.calculate(src, x_text), std::invalid_argument);
  double result = model.calculate(src, x_text_2);
  double real_result = 4.47213595;
  EXPECT_TRUE(fabs(result) - fabs(real_result) <= 0.0000001);
}

TEST(calc_test, ln_test) {
  Model model;
  std::string src = "q(n(x))";
  double x_text = -2;
  double x_text_2 = 20;
  EXPECT_THROW(model.calculate(src, x_text), std::invalid_argument);
  double result = model.calculate(src, x_text_2);
  double real_result = 1.73081838;
  EXPECT_TRUE(fabs(result) - fabs(real_result) <= 0.0000001);
}

TEST(calc_test, atan_sin_test) {
  Model model;
  std::string src = "a(10)+s(10)";
  double result = model.calculate(src, 0);
  double real_result = 1.644775;
  EXPECT_TRUE(fabs(result) - fabs(real_result) <= 0.00001);
}

TEST(calc_test, asin_test) {
  Model model;
  std::string src = "i(1)";
  std::string src2 = "i(-2)";
  double result = model.calculate(src, 0);
  double real_result = 1.5707963;
  EXPECT_TRUE(fabs(result) - fabs(real_result) <= 0.0000001);
  EXPECT_THROW(model.calculate(src2, 0), std::invalid_argument);
}

TEST(calc_test, acos_test) {
  Model model;
  std::string src = "o(0.3)";
  std::string src2 = "o(-2)";
  double result = model.calculate(src, 0);
  double real_result = 1.266104;
  EXPECT_TRUE(fabs(result) - fabs(real_result) <= 0.0000001);
  EXPECT_THROW(model.calculate(src2, 0), std::invalid_argument);
}

TEST(calc_test, e_test) {
  Model model;
  std::string src = "2e+3-e-2";
  double result = model.calculate(src, 0);
  double real_result = 1999.99;
  EXPECT_TRUE(fabs(result) - fabs(real_result) <= 0.0000001);
}

TEST(calc_test, bracets_test) {
  Model model;
  std::string src = ")++2(";
  std::string src2 = "(2+3";
  EXPECT_THROW(model.calculate(src, 0), std::logic_error);
  EXPECT_THROW(model.calculate(src2, 0), std::logic_error);
}
