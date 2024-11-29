# Free-Fall ODE Solver Using Runge-Kutta 4th Order Method

This Python project implements a numerical solution for a system of two ordinary differential equations (ODEs) that describe the motion of a free-falling object with air resistance. The program uses the **Runge-Kutta 4th Order (RK4) method** to compute position and velocity over time, factoring in drag and gravity.

---

## Features
- **Accurate Numerical Solution**:
  - Solves a system of ODEs for position $$\ x(t) \$$ and velocity $$\ v(t) \$$:
    1. $$\frac{\partial x}{\partial t} = v(t)$$
    2. $$\frac{\partial v}{\partial t} = g - \frac{c_d}{m} v^2$$
- **Customizable Parameters**:
  - Configurable inputs for initial conditions, time step size, gravitational constant, drag coefficient, and object mass.
- **Efficient and Flexible**:
  - Implements the RK4 method to estimate the trajectory and velocity at discrete time steps, providing high accuracy for stiff and non-linear systems.
- **Practical Output**:
  - Returns position and velocity as NumPy arrays for easy analysis or plotting.

---

## Directory Structure
```
/freefall_solver
|-- freefall_rk4.py       # Python implementation of the solver
|-- README.md             # Documentation for the project
|-- example_plots.py      # Script to demonstrate visualization of results
```

---

## How to Use

### **Prerequisites**
- Python 3.7 or higher.
- NumPy library installed (`pip install numpy`).

### **Steps to Run**
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/freefall-solver.git
   cd freefall_solver
   ```

2. **Import and Use the Solver**:
   Import the `solve_freefall_RK4` function in your Python script or interactive environment.

   ```python
   from freefall_rk4 import solve_freefall_RK4

   # Define parameters
   x0, v0 = 0.0, 0.0  # Initial position and velocity
   nt, dt = 100, 0.1  # Number of time steps and time step size
   g, cd, m = 9.8, 0.5, 70.0  # Gravitational constant, drag coefficient, mass

   # Solve the system
   x, v = solve_freefall_RK4(x0, v0, nt, dt, g, cd, m)

   # Print results
   print("Position:", x)
   print("Velocity:", v)
   ```

3. **Visualize the Results** (Optional):
   Use a visualization library (e.g., Matplotlib) to plot the trajectory and velocity over time.

   ```python
   import matplotlib.pyplot as plt
   time = [dt * i for i in range(nt + 1)]

   plt.plot(time, x, label="Position (x)")
   plt.plot(time, v, label="Velocity (v)")
   plt.xlabel("Time (s)")
   plt.ylabel("Value")
   plt.title("Free-Fall Trajectory and Velocity")
   plt.legend()
   plt.show()
   ```

---

## Example Output
For the given parameters:
- Initial position \( x(0) = 0 \),
- Initial velocity \( v(0) = 0 \),
- Gravitational constant \( g = 9.8 \),
- Drag coefficient \( c_d = 0.5 \),
- Mass \( m = 70.0 \),

The program produces arrays of positions and velocities over time.

### **Sample Plot**
A visualization of the position and velocity over time:

![Example Plot](example_plot.png)

---

## Key Highlights
1. **Runge-Kutta 4th Order Method**:
   - Provides a highly accurate numerical solution by iteratively refining estimates of position and velocity.
2. **Efficient and Modular Design**:
   - Uses compact functions for derivative calculation and RK4 iteration.
3. **Customizability**:
   - Flexible input parameters make it adaptable to various physical scenarios.

---

## Future Enhancements
- Add support for different drag models (e.g., linear drag).
- Extend functionality to include user-defined forces.
- Integrate with plotting utilities for automated result visualization.