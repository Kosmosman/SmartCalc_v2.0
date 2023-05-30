#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

#include "../Model/parcer.h"

struct CalculatorTest {
  s21::Parcer correct_one{"1+2+3-4*5/(3.3^2)"};
  s21::Parcer correct_two{"5^3/2*sin(11-2)+5/2.8"};
  s21::Parcer correct_three{"log(2^3)-2*(1+3*(2-0.05)-2)"};
  s21::Parcer correct_four{"sin(10-7.2^3)*ln(12)*2/3.2/5.2*3+2"};
  s21::Parcer correct_five{
      "log(10^2/3)^3^2*5+2.4*(1-2^7)/ln(12.223)-12.64^acos(-0.041)"};
  s21::Parcer correct_six{"ln(log(3456)^0.2/3)*22^0.2/6+112.34-11*5.2"};

  double answer_one{4.16345270891};
  double answer_two{27.5431196133};
  double answer_three{-8.79691001301};
  double answer_four{2.82733260398};
  double answer_five{38.8363096333};
  double answer_six{54.8784012618};

  std::vector<std::string> incorrect_collection{
      "sin-",   "(-)",  "cos-45", "ln",     "-5-",          "log(*)",
      "1+2+3+", "*2+2", "4**2",   "sincos", "2342tey35twr", "1321.23413.4",
      ")",      "-(",   "0/",     "(sin)"};
};

TEST(Validator, CorrectTest1) {
  CalculatorTest one;
  EXPECT_NEAR(one.correct_one.Answer(), one.answer_one, 0.0000001);
}

TEST(Validator, CorrectTest2) {
  CalculatorTest one;
  EXPECT_NEAR(one.correct_two.Answer(), one.answer_two, 0.0000001);
}

TEST(Validator, CorrectTest3) {
  CalculatorTest one;
  EXPECT_NEAR(one.correct_three.Answer(), one.answer_three, 0.0000001);
}

TEST(Validator, CorrectTest4) {
  CalculatorTest one;
  EXPECT_NEAR(one.correct_four.Answer(), one.answer_four, 0.0000001);
}

TEST(Validator, CorrectTest5) {
  CalculatorTest one;
  EXPECT_NEAR(one.correct_five.Answer(), one.answer_five, 0.0000001);
}

TEST(Validator, CorrectTest6) {
  CalculatorTest one;
  EXPECT_NEAR(one.correct_six.Answer(), one.answer_six, 0.0000001);
}

TEST(Validator, EmptyString) {
  std::string emp;
  EXPECT_FALSE(s21::Parcer{emp}.IsValideExpression());
}

TEST(Validator, IncorrectTestCollection) {
  CalculatorTest one;
  s21::Parcer p;
  for (auto it : one.incorrect_collection)
    EXPECT_FALSE(p(it, "0").IsValideExpression());
}

TEST(Calculator, UnaryMinus) {
  s21::Parcer one{"-2"};
  EXPECT_NEAR(one.Answer(), -2.0, 0.0000001);
}

TEST(Calculator, UnaryPlus) {
  s21::Parcer one{"+2"};
  EXPECT_NEAR(one.Answer(), 2.0, 0.0000001);
}

TEST(Calculator, PlusTest) {
  s21::Parcer one{"4.2+3.5"};
  EXPECT_NEAR(one.Answer(), 7.7, 0.0000001);
}

TEST(Calculator, MinusTest) {
  s21::Parcer one{"0.1-22"};
  EXPECT_NEAR(one.Answer(), -21.9, 0.0000001);
}

TEST(Calculator, MultiplicationTest) {
  s21::Parcer one{"3*5"};
  EXPECT_NEAR(one.Answer(), 15, 0.0000001);
}

TEST(Calculator, DivisionTest) {
  s21::Parcer one{"7/3"};
  EXPECT_NEAR(one.Answer(), 2.3333333, 0.0000001);
}

TEST(Calculator, ModTest) {
  s21::Parcer one{"84.2%17.9"};
  EXPECT_NEAR(one.Answer(), 12.6, 0.0000001);
}

TEST(Calculator, PowTest) {
  s21::Parcer one{"2^2^3"};
  EXPECT_NEAR(one.Answer(), 256, 0.0000001);
}

TEST(Calculator, SinTest) {
  s21::Parcer one{"sin(10-2.4)"};
  EXPECT_NEAR(one.Answer(), std::sin(10 - 2.4), 0.0000001);
}

TEST(Calculator, CosTest) {
  s21::Parcer one{"cos(1.343546)"};
  EXPECT_NEAR(one.Answer(), std::cos(1.343546), 0.0000001);
}

TEST(Calculator, TanTest) {
  s21::Parcer one{"tan(-345.1254)"};
  EXPECT_NEAR(one.Answer(), std::tan(-345.1254), 0.0000001);
}

TEST(Calculator, CorrectAsinTest) {
  s21::Parcer one{"asin(0.234)"};
  EXPECT_NEAR(one.Answer(), std::asin(0.234), 0.0000001);
}

TEST(Calculator, IncorrectAsinTest) {
  s21::Parcer one{"asin(3.51)"};
  EXPECT_TRUE(std::isnan(one.Answer()));
}

TEST(Calculator, CorrectAcosTest) {
  s21::Parcer one{"acos(-0.349)"};
  EXPECT_NEAR(one.Answer(), std::acos(-0.349), 0.0000001);
}

TEST(Calculator, IncorrectAcosTest) {
  s21::Parcer one{"acos(-10.23)"};
  EXPECT_TRUE(std::isnan(one.Answer()));
}

TEST(Calculator, AtanTest) {
  s21::Parcer one{"atan(2.3)"};
  EXPECT_NEAR(one.Answer(), std::atan(2.3), 0.0000001);
}

TEST(Calculator, CorrectSqrtTest) {
  s21::Parcer one{"sqrt(10)"};
  EXPECT_NEAR(one.Answer(), std::sqrt(10), 0.0000001);
}

TEST(Calculator, IncorrectSqrtTest) {
  s21::Parcer one{"sqrt(-2)"};
  EXPECT_TRUE(std::isnan(one.Answer()));
}

TEST(Calculator, CorrectLnTest) {
  s21::Parcer one{"ln(90)"};
  EXPECT_NEAR(one.Answer(), std::log(90), 0.0000001);
}

TEST(Calculator, IncorrectLnTest) {
  s21::Parcer one{"ln(-5)"};
  EXPECT_TRUE(std::isnan(one.Answer()));
}

TEST(Calculator, InfLnTest) {
  s21::Parcer one{"ln(0)"};
  EXPECT_TRUE(std::isinf(one.Answer()));
}

TEST(Calculator, CorrectLogTest) {
  s21::Parcer one{"log(4)"};
  EXPECT_NEAR(one.Answer(), std::log10(4), 0.0000001);
}

TEST(Calculator, IncorrectLogTest) {
  s21::Parcer one{"log(-1.2)"};
  EXPECT_TRUE(std::isnan(one.Answer()));
}

TEST(Calculator, ZeroDivision) {
  s21::Parcer one{"5/0-3+99"};
  EXPECT_TRUE(std::isnan(one.Answer()));
}

TEST(Calculator, ReplaceTest) {
  s21::Parcer one;
  one("5+x", "10");
  EXPECT_NEAR(one.Answer(), 15, 0.0000001);
}

TEST(Calculator, ReplaceTestTwo) {
  s21::Parcer one;
  one("x+5", "10");
  EXPECT_NEAR(one.Answer(), 15, 0.0000001);
}

TEST(Calculator, IncorrectReplaceTest) {
  s21::Parcer one;
  one("5+xx", "10");
  EXPECT_FALSE(one.IsValideExpression());
}

TEST(Calculator, DotTest) {
  s21::Parcer one;
  one("5+xx", "10");
  EXPECT_FALSE(one.IsValideExpression());
  auto res = one.CreateDots("10+x", {-10, 10}, {-10, 10});
  for (auto it : res.second) {
    std::cout << "Second = " << it << std::endl;
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
