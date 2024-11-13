/*
Name: Alex Choi
Last updated: October 2024

### Problem Description

This C++ code efficiently constructs Pascal's Triangle using a dynamically allocated 1D array in the storage class and a derived Pascal class. 
Pascal's Triangle, often used in combinatorial mathematics, lists coefficients for binomial expansions. Each coefficient is calculated using the recurrence relation:

    C(i, j) = C(i-1, j-1) + C(i-1, j)

where C(i, j) represents the binomial coefficient at row i and column j.

The code achieves the following:
1. Dynamic Storage Allocation: The storage class maintains a linearized vector to store coefficients, with functions to set and retrieve values.
2. Triangle Construction: The Pascal class builds Pascal's Triangle up to a specified number of rows and can extend the triangle on demand if rows are accessed that were not initially computed.
3. Printing: The triangle is displayed with each row centered for a clear visual representation.

### Code Overview

- storage Class: Manages a 1D vector of integers to store the coefficients of Pascal’s Triangle. Has methods to set, get, and dynamically extend storage as needed.
- Pascal Class: Inherits from storage, fills Pascal's Triangle, and provides a method to access coefficients outside the initially specified range. Includes a print function for displaying the triangle in a visually aligned format.

### Example Usage in main():

The main function creates an instance of Pascal with 3 rows, prints the initial triangle, then accesses a coefficient outside the initial range, prompting dynamic resizing and recalculating as needed. It then prints the expanded triangle.
*/

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include <iomanip>
using std::setw;

class storage {
protected:
    vector<int> data;
    int max_row;

public:
    // constructor: needs to allocate the vector
    storage(int size) : data(size, -1), max_row(size) {}
    // default size:1 this uses constructor delegation of above constructor
    storage() : storage(1) {}

    void set(int i, int j, int value) {
        // linearized index at the current row using i, j:
        int linear_index = i * (i + 1) / 2 + j;
        // check if it's out of range:
        if (linear_index >= data.size()) {
            extend_storage(i);
        }
        data.at(linear_index) = value;
    }
    // getter
    int get(int i, int j) {
        // linearized index at the current row using i, j:
        int linear_index = i * (i + 1) / 2 + j;
        if (linear_index < data.size()) {
            return data.at(linear_index);
        } else {
            std::cerr << "Index out of bounds: " << i << endl;
            return -1;  
        }
    }
    // method for extending the storage
    void extend_storage(int new_max) {
        // Ensure the storage can hold all the elements up to the new row
        int new_size = (new_max * (new_max + 1) / 2) + (new_max + 1);
        data.resize(new_size);
        max_row = new_max;
    }
};

class Pascal : public storage {
private:
    int n; // total number of rows to initially create
    int filled_rows; // track how many rows have been filled

public:
    // constructor of a 1D vector with capacity to contain all of coeffs using storage class's constructor
    Pascal(int n) : n(n), filled_rows(0), storage(n * (n + 1) / 2) {
        fill_triangle(n);
    }

    void fill_triangle(int rows) {
        // two nested loops to iterate over the triangle
        for (int i = filled_rows; i < rows; i++) { // start from the last filled row
            // for each row
            for (int j = 0; j <= i; j++) { // only up to i because each row has i+1
                // linearized index at the current row using i, j:
                //int linear_index = i * (i + 1) / 2 + j;
                // special cases: first or last elements are ones
                if ((j == 0) || (i == j)) {
                    set(i, j, 1);
                } else {
                    // linear index at the previous row
                    //int prev_row_linear_index = (i - 1) * i / 2;
                    // use the formula of recurrence:
                    //set(linear_index, get(prev_row_linear_index + j - 1) + get(prev_row_linear_index + j));
                    set(i, j, get(i - 1, j - 1) + get(i - 1, j));
                }
            }
            // update filled rows:
            filled_rows++;
        }
    }

    // getvalue function that calls get from storage class
    int getvalue(int i, int j) {
        // Check if the required row is filled
        if (i >= filled_rows) {
            fill_triangle(i + 1); // Fill up to the required row
        }
        // we just use linearized index and then inherit from storage class
        return get(i, j);
    }

    // Print method to display Pascal's Triangle centered
    // Print method to display Pascal's Triangle centered
    void print() {
        int width = (max_row * 2) / 3.5; // Width for each number; adjust as needed

        for (int i = 0; i < filled_rows; i++) {
            int spaces = (max_row - i - 1) * width / 2;
            // Ensure spaces are non-negative
            if (spaces < 0) {
                spaces = 0;
            }
            std::cout << std::string(spaces, ' '); // Centering spaces

            for (int j = 0; j <= i; j++) {
                std::cout << std::setw(width) << get(i, j); // Print each coefficient
            }
            std::cout << std::endl;
        }
    }

};

int main() {
    // this will serve as the test:
    // this will serve as the test:
    Pascal pt(3); //  original triangle
    std::cout << "Original Triangle: " << std::endl;
    pt.print();
    std::cout << "" << std::endl;
    
    // Accessing a coefficient outside of the initially filled triangle
    std::cout << "Accessing coefficient [9, 2]: " << pt.getvalue(9, 2) << std::endl; // Will fill triangle as needed
    std::cout << "Note: Triangle is zero-indexed." << std::endl;
    std::cout << "" << std::endl;
    
    std::cout << "Resized Triangle: " << std::endl;
    pt.print();
    return 0;

    
    return 0;
}

