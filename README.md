# Physics 427 Homework 3

__Due 11:59pm Monday 9/18/2023__

## 1. Adaptive Simpson's Rule

In a C++ header file `problem1.h`, implement the adaptive Simpson's rule for a definite integral that was discussed in class. Your function should look like:

``` c++
template <typename F>
std::tuple<bool, double> adaptive_simpson(const F& f, double a, double b, double tolerance);
```

Similar to the last homework, we are returning a `bool` together with our solution to indicate whether the iteration converged, or whether there is some issue encountered along the way (e.g. hitting NaN). Implement this using an adaptive trapezoidal rule as discussed in class. Stop the iteration when $|\varepsilon_n/S'_n| < \mathrm{tolerance}$.

Since you are implementing the Simpson's rule using the trapezoidal rule, it may be a good idea to implement a function to assist with that:

``` c++
template <typename F>
double trapezoidal_next(const F& f, double a, double b, double dx, double Sn);
```

It takes the same given function $f$, the same interval $[a, b]$, the current level of $\Delta x$, and the current trapezoidal estimate $S_n$. It should return the next refined estimate $S_{n+1}$ by evaluating the function $f$ at additional points and using the already known estimate $S_n$. This helper function can help tremendously when you use it to implement the Simpson's rule. If you can find a way to implement Simpson's rule without using this helper function, feel free to do that too. As long as the function `adaptive_simpson` works correctly, you will get the full points for this problem.

I have included a simple test file `test1.cpp` to help you debug your code. As usual, feel free to design more test cases to check the convergence and behavior of your integration function. When you are done, add and commit your `problem1.h` to the repo.

## 2. Gauss Quadrature

In a C++ header file `problem2.h`, implement the $N = 10$ Gauss quadrature formula discussed in class. Your function should look like:

``` c++
template <typename F>
double gauss_quadrature_10(const F& f, double a, double b);
```

Notice that the function signature is significantly simpler than the adaptive Simpson's rule. This is because we don't need to carry out any iteration at all, and the final result has a fixed (very high) precision.

I have included a simple test file `test2.cpp` to help you debug your code, which uses the same test cases as `test1.cpp`. Similar to `test1.cpp`, it always prints out your integration result and the target result. Compare for yourself how Gauss quadrature stacks up with the iterative refinement method you implemented above. Finally, when you are done, add and commit your `problem2.h` to the repo.

## 3. Period of a Physical Pendulum

In this problem, we apply the integration functions you developed above to solve a physics problem. The equation of motion of a pendulum is:

$$
\frac{d^2\theta}{dt^2} + \frac{g}{L}\sin\theta = 0
$$

You are probably familiar with this equation in the small angle approximation: $\sin\theta\approx \theta$. In that case, the solution to the differential equation is $\theta(t) = A\sin(\omega t)$ where $\omega = \sqrt{g/L}$ is the angular frequency of the simple pendulum. The period of this pendulum is $T_0 = 2\pi\sqrt{L/g}$.

Without small angle approximation, the equation is still relatively easy to solve. Multiply the equation by $d\theta/dt$, you can rewrite the first term as $(1/2)d(\dot{\theta})^2/dt$, where $\dot{\theta} = d\theta/dt$. The equation becomes a total derivative:

$$
\frac{d}{dt}\left[\frac{1}{2}\dot{\theta}^2 - \frac{g}{L}\cos\theta\right] = 0
$$

You can integrate on both sides to get:

$$
\frac{1}{2}\dot{\theta}^2 - \frac{g}{L}\cos\theta = C
$$

Notice that when $\dot{\theta} = 0$, the pendulum should be at its maximum angle, therefore $C$ must be related to $\theta_\mathrm{max}$. The equation can then be written as:

$$
\dot{\theta} = \sqrt{\frac{2g}{L}(\cos\theta - \cos\theta_\mathrm{max})}
$$

We can calculate the time it takes for the pendulum to swing from $\theta = 0$ to $\theta = \theta_\mathrm{max}$:

$$
t_{1/4} = \sqrt{\frac{L}{2g}}\int_0^{\theta_\mathrm{max}}\frac{d\theta}{\sqrt{\cos\theta - \cos\theta_\mathrm{max}}}
$$

The full period is simply 4 times this quantity, $T = 4t_{1/4}$. Unfortunately, this integral does not have a closed form. It is known as an _elliptic integral_. This integral is also not very well-behaved, in the sense that when $\theta = \theta_\mathrm{max}$, the denominator goes to zero, which is a problem if you want to use the adaptive Simpson's method that needs to evaluate the function at end points.

The integral can be converted to a more well-behaved one by the following substitution: define $k = \sin(\theta_\mathrm{max}/2)$, and $k\sin\phi = \sin(\theta/2)$. We can then write:

$$
d\theta = \frac{2k\cos\phi}{\cos(\theta/2)}d\phi
$$

Plugging this back into the above integral and realizing that $\cos\theta = 1 - 2\sin^2(\theta/2)$, we get:

$$
t_{1/4} = \sqrt{\frac{L}{g}}\int_0^{\pi/2}\frac{d\phi}{\sqrt{1 - k^2\sin^2\phi}}
$$

The integral now is well-behaved at end points, and it's called the complete elliptic integral of the first kind.

Your task is to write a program to evaluate the full period $T$ with this integral, using one of the functions you implemented above (choose your favorite one). Do this for a few different $\theta_\mathrm{max}\in [0.01\pi, 0.1\pi, \pi/6, \pi/3, \pi/2]$. Print out the answer in the following format:

``` sh
th_max = 0.01pi: T/T0 = [...]
th_max = 0.1pi:  T/T0 = [...]
th_max = pi/6:   T/T0 = [...]
th_max = pi/3:   T/T0 = [...]
th_max = pi/2:   T/T0 = [...]
```

$T_0$ is defined to be the period of the simple pendulum, $T_0 = 2\pi\sqrt{L/g}$. You can access the value of $\pi$ using `M_PI`, which is defined in the header `<cmath>`. You should see that the result is extremely close to 1 when $\theta_\mathrm{max}$ is small, but with larger $\theta_\mathrm{max}$, the period gets progressively larger than 1. Write your program in `problem3.cpp`, then add and commit it to the repo. Include the output of this program in a separate text file `problem3.txt` and commit to the repo too.
