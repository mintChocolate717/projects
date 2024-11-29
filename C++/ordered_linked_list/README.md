# Sorted Linked List Implementation

This directory contains the implementation of a **sorted linked list** in C++ that stores unique values in increasing order. The list dynamically adjusts to user input, demonstrating various insertion cases, length calculations, and efficient memory management using smart pointers.

---

## Features
- **Dynamic Sorted Linked List**: Maintains unique elements in sorted order (head, middle, or tail insertion).
- **Efficient Memory Management**: Uses `shared_ptr` to manage nodes, ensuring automatic memory cleanup.
- **Interactive User Input**:
  - Accepts integers from the user and inserts them into the list.
  - Prints the list after each insertion.
  - Ends gracefully when the user inputs `0`.
- **Key Functionalities**:
  - Insert elements into the correct position (head, middle, or tail).
  - Check for the existence of a value.
  - Print the current state of the list.
  - Compute the list's length.

---

## Directory Structure
```
/sorted_linked_list
|-- CMakeLists.txt       # Build configuration for the project
|-- linked_list.cpp      # Source code implementing the sorted linked list
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
   git clone https://github.com/yourusername/linked-list-project.git
   cd linked-list-project/sorted_linked_list
   ```

2. **Build the Project**:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

3. **Run the Program**:
   ```bash
   ./linked_list
   ```

---

## Example Usage
When you run the program, it will prompt you to enter integers. The program inserts each integer into the linked list, keeping the list sorted. The list is printed after each insertion. Enter `0` to terminate the program.

### **Example Session**
```plaintext
Enter a value: 3
List => 3:1

Enter a value: 1
List => 1:1, 3:1

Enter a value: 5
List => 1:1, 3:1, 5:1

Enter a value: 3
List => 1:1, 3:2, 5:1

Enter a value: 0

!!! User inputs zero (0), program terminating...
```

---

## Key Design and Functionality Highlights
1. **Insertion Logic**:
   - **Head Insertion**: Handles cases where the new value is smaller than the current head.
   - **Middle Insertion**: Inserts values between nodes to maintain order.
   - **Tail Insertion**: Appends values larger than the current tail.
   - **Duplicate Handling**: Increments the count of the node if the value already exists.

2. **Smart Pointers**:
   - Leverages `shared_ptr` to ensure proper memory management and avoid manual `delete` operations.

3. **Recursive and Iterative Methods**:
   - Recursive functions for length calculation and value existence checks.
   - Iterative approach for efficient list traversal during insertion.

---

## Future Enhancements
- Add support for additional data types (e.g., templating the list for generic types).
- Implement removal functionality for specific elements.
- Optimize recursive functions for very large lists.