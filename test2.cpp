#include "problem3.h"
#include <iostream>
#include <iomanip>

int main() {
  // Error tolerance for these tests
  double eps = 1e-9;

  // Test function 1
  auto f1 = [](double x) { return std::pow(x, 5) - 4.0 * x*x*x + 2.0; };

  // Run adaptive integration
  auto result1 = gauss_quadrature_10(f1, 1.0, 2.0);

  // Check result
  double I1 = -2.5;
  if (std::abs(result1 - I1) < eps) {
    std::cout << "Test Case 1: PASS, ";
  } else {
    std::cout << "Test Case 1: FAIL, ";
  }
  std::cout << "integral is " << std::setprecision(12)
              << result1 << ", expected to be around " << I1
              << std::endl;

  // Test function 2
  auto f2 = [](double x) { return std::sin(x) + std::exp(0.1*x)*x*x*x/(x*x - 1.0); };

  // Run adaptive integration
  auto result2 = gauss_quadrature_10(f2, 2.0, 3.0);

  // Check result
  double I2 = 4.42293024935;
  if (std::abs(result2 - I2) < eps) {
    std::cout << "Test Case 2: PASS, ";
  } else {
    std::cout << "Test Case 2: FAIL, ";
  }
  std::cout << "integral is " << std::setprecision(12)
              << result2 << ", expected to be around " << I2
              << std::endl;

  // Test function 3
  auto f3 = [](double x) { return x*x*x*x*std::log(x + std::sqrt(x*x + 1.0)); };

  // Run adaptive integration
  auto result3 = gauss_quadrature_10(f3, 0.0, 2.0);

  // Check result
  double I3 = 8.15336411984;
  if (std::abs(result3 - I3) < eps) {
    std::cout << "Test Case 3: PASS, ";
  } else {
    std::cout << "Test Case 3: FAIL, ";
  }
  std::cout << "integral is " << std::setprecision(12)
            << result3 << ", expected to be around " << I3
            << std::endl;

  return 0;
}
