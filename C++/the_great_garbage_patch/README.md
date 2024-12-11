# The Great Garbage Patch: Ocean Ecosystem Simulation

This directory contains the implementation of a **time-dependent simulation** to model the impact of ocean trash on marine ecosystems. The simulation showcases interactions between turtles, trash, and ships, providing insights into the dynamics of pollution and cleanup strategies.

---

## Features
- **Cellular Automaton Framework**: Simulates the movement and interaction of entities (turtles, trash, ships) within a 2D ocean grid.
- **Entity-Specific Behavior**:
  - **Turtles**: Move randomly, avoid obstacles, and die upon encountering trash or colliding with ships.
  - **Trash**: Drifts with a small probability, simulating ocean currents, and interacts destructively with ships.
  - **Ships**: Navigate the ocean, reducing trash populations and dynamically interacting with other entities.
- **Collision Handling**: Includes a well-defined collision matrix dictating entity outcomes during interactions.
- **Optimized Grid Representation**: Uses a flattened 1D vector for efficient memory usage.
- **Randomized Dynamics**: Movement behaviors are governed by user-configurable probabilities for idling versus active movement.
- **Real-Time Visualization**: ASCII-based display updates dynamically to represent the current state of the ocean.

---

## Directory Structure
```
/simulation
|-- ocean.cpp            # Core implementation of the ocean simulation
|-- README.md            # Documentation for the simulation project
|-- ocean.sh             # Bash Script for running the program
|-- CMakeLists.txt       # CMake configuration
|-- written_report.pdf   # Written report discussing the project
```

---

## How to Run
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/ocean-simulation.git
   cd ocean-simulation/simulation
   ```
2. **Run the Simulation**:
   ```bash
   ./ocean.sh
   ```

---

## Example Output
The simulation dynamically updates the terminal with a real-time ASCII grid. Below is an example snapshot of the ocean ecosystem:

```
  0 1 2 3 4
0 o x | o x
1 | o x | o
2 x | o x |
3 o x | o x
4 | o x | o

Turtles: 40
Trash: 40
Ships: 14
```

---

## Future Work
Potential enhancements include:
- Adding realistic entity behaviors such as turtle breeding, ship-directed movement towards trash, and turtle avoidance of trash.
- Incorporating environmental factors like ocean currents to simulate trash accumulation zones and dynamic obstacle placement.
- Improving visualization techniques, including exporting data for scientific tools or using graphical representations.
- Introducing performance optimizations for larger grid sizes or extended simulation durations.

---
