#include "problem1.h"

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  double dx = 0.2;
  vector<double> xs = {0.0, dx, 2.0 * dx, 3.0 * dx, 4.0 * dx, 5.0 * dx};

  auto f = [](double x) { return sin(x); };

  vector<double> ys(xs.size());
  for (int i = 0; i < xs.size(); i++) {
    ys[i] = f(xs[i]);
  }

  // Check end points
  double eps = 1e-10;

  double x0 = 0.0;
  double f0_ref = 0.0;
  double f0 = interpolate(x0, xs, ys);
  if (abs(f0 - f0_ref) > eps) {
    cout << "FAILED: at x = " << x0 << ", interpolated f(x) = " << f0
         << ", expected " << f0_ref << endl;
  } else {
    cout << "PASSED: at x = " << x0 << ", interpolated f(x) = " << f0
         << ", expected " << f0_ref << endl;
  }

  double x1 = 1.0;
  double f1_ref = sin(xs.back());
  double f1 = interpolate(x1, xs, ys);
  if (abs(f1 - f1_ref) > eps) {
    cout << "FAILED: at x = " << x1 << ", interpolated f(x) = " << f1
         << ", expected " << f1_ref << endl;
  } else {
    cout << "PASSED: at x = " << x1 << ", interpolated f(x) = " << f1
         << ", expected " << f1_ref << endl;
  }

  // Check interior points
  double x2 = 0.5;
  double f2_ref = 0.5 * (sin(2.0 * dx) + sin(3.0 * dx));
  double f2 = interpolate(x2, xs, ys);

  if (abs(f2 - f2_ref) > eps) {
    cout << "FAILED: at x = " << x2 << ", interpolated f(x) = " << f2
         << ", expected " << f2_ref << endl;
  } else {
    cout << "PASSED: at x = " << x2 << ", interpolated f(x) = " << f2
         << ", expected " << f2_ref << endl;
  }

  double x3 = 0.77;
  double f3_ref = 0.15 * sin(3.0 * dx) + 0.85 * sin(4.0 * dx);
  double f3 = interpolate(x3, xs, ys);

  if (abs(f3 - f3_ref) > eps) {
    cout << "FAILED: at x = " << x3 << ", interpolated f(x) = " << f3
         << ", expected " << f3_ref << endl;
  } else {
    cout << "PASSED: at x = " << x3 << ", interpolated f(x) = " << f3
         << ", expected " << f3_ref << endl;
  }

  return 0;
}
