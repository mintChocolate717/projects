# Dynamic Pascal's Triangle Generator

This C++ project implements an efficient generator for Pascal's Triangle using dynamic memory allocation and a 1D array. Pascal's Triangle is commonly used in combinatorics to compute binomial coefficients, with each value calculated as:

$$\[
C(i, j) = C(i-1, j-1) + C(i-1, j)
\]$$

This implementation supports dynamically resizing the triangle to accommodate new rows as needed.

---

## Features
1. **Dynamic Storage Allocation**:
   - Stores Pascal's Triangle in a dynamically allocated 1D array for efficient memory usage.
   - Automatically resizes when accessing rows beyond the initially specified size.

2. **Efficient Triangle Construction**:
   - Uses the recurrence relation to compute coefficients row by row.
   - Includes special handling for edge cases (first and last elements in each row).

3. **Access and Visualization**:
   - Provides a `getvalue` method to retrieve any coefficient dynamically, expanding the triangle if necessary.
   - Features a `print` method to display the triangle with proper centering for clear visualization.

---

## Directory Structure
```
/pascal_triangle
|-- CMakeLists.txt       # Build configuration for the project
|-- pascal_triangle.cpp  # C++ implementation of Pascal's Triangle
|-- README.md            # Documentation for this project
```

---

## How to Build and Run
### **Prerequisites**
- A C++ compiler that supports C++17 or later.
- `CMake` installed on your system.

### **Steps to Build and Run**
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/pascal-triangle.git
   cd pascal_triangle
   ```

2. **Build the Project**:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

3. **Run the Program**:
   ```bash
   ./pascal_triangle
   ```

---

## Example Usage
The program generates and prints Pascal's Triangle, dynamically resizing as needed.

### **Sample Output**
#### **Initial Triangle (3 Rows)**
```plaintext
      1
    1   1
   1   2   1
```

#### **Accessing Coefficient [9, 2]**
The triangle automatically expands to include row 9:
```plaintext
Accessing coefficient [9, 2]: 36
Note: Triangle is zero-indexed.
```

#### **Expanded Triangle**
```plaintext
                          1
                       1    1
                    1    2    1
                 1    3    3    1
              1    4    6    4    1
           1    5   10   10    5    1
        1    6   15   20   15    6    1
     1    7   21   35   35   21    7    1
  1    8   28   56   70   56   28    8    1
1    9   36   84  126  126   84   36    9    1
```

---

## Key Highlights
1. **Dynamic Memory Management**:
   - Uses a 1D array to store coefficients efficiently.
   - Automatically resizes storage when accessing new rows.

2. **Combinatorics Application**:
   - Computes binomial coefficients using the classic recurrence relation.

3. **Ease of Use**:
   - Access coefficients using the `getvalue` method.
   - View the triangle using the `print` method.

---

## Future Enhancements
- Add support for fractional or modular arithmetic in coefficient calculations.
- Extend visualization for larger triangles with better formatting.
- Export triangle data to external formats like CSV or JSON for integration with other tools.