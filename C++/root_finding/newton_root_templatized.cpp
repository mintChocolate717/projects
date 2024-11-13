/*
name: Alex Choi
last edited: October 30, 2024
*/

#include <iostream>
using std::cout;
using std::endl;

#include <functional>
using std::function;

#include <complex>
using std::complex;
using namespace std::complex_literals;

// templatized method for calculating f = x^2 - num
template <typename T>
T f(T x, T num) {
    return x * x - num;
};

// templatized method for calculating f' using finite difference, forward Euler:
template <typename T>
T fprime(T x, T num) {
    T dx = 1e-6;
    return (f(x + dx, num) - f(x, num)) / dx ; 
}

// templatized method for newton's root finding method for sqrt(2):
template <typename T>
T newton_root( function<T(T, T)> f, function<T(T, T)> fprime, T initial_guess, T num) {
  // OBJECTIVE: find the square root of two
  
  // start somewhere
  T current_x = initial_guess;
  
  // compute the function value
  T function_value = f(current_x, num);

  const int max_iterations = 1000;  // Safety limit for iterations
  const double tolerance = 1.e-10;   // Tolerance for convergence
  
  // while the function in the current value is too large keep looping
  for ( int i = 0; i < max_iterations; ++i) {
    // update current x
    current_x -= f(current_x, num) / fprime(current_x, num);
    // calcute new function value
    function_value = f(current_x, num);
    // check if the value of f(x) is below allowed tolerance:
    if ( std::abs(function_value) < tolerance ) { break; }
  }
  return current_x;
}


int main() {

    // Test with double
    double n1  = 2.0, n2 = 5.0;
    std::cout << "sqrt(double 2): " << newton_root<double>(f<double>, fprime<double>, 1.0, n1) << std::endl;
    std::cout << "sqrt(double 5): " << newton_root<double>(f<double>, fprime<double>, 1.0, n2) << std::endl;
    std::cout << std::endl;  // Extra empty line

    // Test with float
    float n3 = 7.f, n4 = 3.0f;
    std::cout << "sqrt(float 7): " << newton_root<float>(f<float>, fprime<float>, 1.0f, n3) << std::endl;
    std::cout << "sqrt(float 3): " << newton_root<float>(f<float>, fprime<float>, 1.0f, n4) << std::endl;
    std::cout << std::endl;  // Extra empty line

    // Test with complex<double>
    complex<double> n5(11.0, 0.0);
    complex<double> n6(1.0, 0.0);
    std::cout << "sqrt(complex<double> 11): " << newton_root<complex<double>>(f<complex<double>>, fprime<complex<double>>, complex<double>(0.5, 0.5), n5) << std::endl;
    std::cout << "sqrt(complex<double> 1): " << newton_root<complex<double>>(f<complex<double>>, fprime<complex<double>>, complex<double>(0.5, 0.5), n6) << std::endl;    
    std::cout << std::endl;  // Extra empty line

    return 0;
}

