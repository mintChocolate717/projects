# Newton's Root-Finding Method Implementation

This directory contains a **templatized implementation of Newton's root-finding method** in C++. The program approximates the square roots of real and complex numbers using function templates to support various data types.

---

## Features
- **Templatized Root-Finding**:
  - Generalized implementation of Newton's method for `double`, `float`, and `complex<double>` types.
- **Finite Difference Derivative**:
  - Approximates the derivative of \( f(x) = x^2 - num \) using forward Euler with a small step size.
- **Configurable Parameters**:
  - Adjustable tolerance for convergence and maximum iterations for robust root-finding.
- **Demonstration of Flexibility**:
  - Computes square roots of real and complex numbers in various scenarios.

---

## Directory Structure
```
/newton_root_method
|-- CMakeLists.txt         # Build configuration for the project
|-- newton_root.cpp        # Source code implementing the Newton's method
|-- README.md              # Documentation for this project
```

---

## How to Build and Run
### **Prerequisites**
- A C++ compiler that supports C++17 or later.
- `CMake` installed on your system.

### **Steps to Build and Run**
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/newton-root-method.git
   cd newton-root-method/newton_root_method
   ```

2. **Build the Project**:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

3. **Run the Program**:
   ```bash
   ./newton_root
   ```

---

## Example Usage
When you run the program, it calculates square roots for different numeric types (`double`, `float`, and `complex<double>`). Below is an example session output:

### **Sample Output**
```plaintext
sqrt(double 2): 1.41421
sqrt(double 5): 2.23607

sqrt(float 7): 2.64575
sqrt(float 3): 1.73205

sqrt(complex<double> 11): (3.31662,0)
sqrt(complex<double> 1): (1,0)
```

---

## Key Design and Functionality Highlights
1. **Templatized Functions**:
   - \( f(x) = x^2 - num \): Calculates the function value for a given input `x` and target `num`.
   - \( f'(x) \): Approximates the derivative of \( f(x) \) using forward Euler finite difference.

2. **Newton-Raphson Method**:
   - Iteratively refines the root approximation until the function value is within the specified tolerance or the maximum number of iterations is reached.

3. **Complex Number Support**:
   - Uses `complex<double>` to handle square root approximations of complex numbers.

---

## Future Enhancements
- Extend support for additional mathematical functions beyond square roots.
- Add user-defined options for tolerance, maximum iterations, and initial guesses at runtime.
- Optimize finite difference calculations for improved accuracy and efficiency.