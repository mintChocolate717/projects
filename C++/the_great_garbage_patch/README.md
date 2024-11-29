# (Work In Progress) The Great Garbage Patch: Ocean Ecosystem Simulation

This directory contains the implementation of a **time-dependent simulation** to model the impact of ocean trash on marine ecosystems. The simulation showcases interactions between turtles, trash, and ships, providing insights into the dynamics of pollution and cleanup strategies.

---

## Features - Work In Progress
- **Cellular Automaton Framework**: Simulates the movement and interaction of entities (turtles, trash, ships) within a 2D ocean grid.
- **Entity-Specific Behavior**:
  - **Turtles**: Move randomly and die upon encountering trash.
  - **Trash**: Drifts minimally to simulate ocean currents.
  - **Ships**: Remove trash when encountered.
- **Optimized Grid Representation**: Uses a flattened 1D vector for efficient memory usage.
- **Real-Time Visualization**: ASCII-based display updates dynamically to represent the current state of the ocean.

---

## Directory Structure - Work In Progress
```
/simulation
|-- ocean.cpp            # Core implementation of the ocean simulation
|-- ocean.h              # Header file defining the Ocean class and utilities
|-- README.md            # Documentation for the simulation project
|-- examples/
    |-- example_input.txt # Example configuration for initial entity placement
|-- output/
    |-- simulation_log.txt # Log of simulation steps
```

---

## How to Run - Work In Progress
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/ocean-simulation.git
   cd ocean-simulation/simulation
   ```
2. **Compile the Program**:
   ```bash
   g++ -o ocean_sim ocean.cpp
   ```
3. **Run the Simulation**:
   ```bash
   ./ocean_sim
   ```

---

## Example Output - Work In Progress
The simulation dynamically updates the terminal with a real-time ASCII grid. Below is an example snapshot of the ocean ecosystem:

```
  0 1 2 3 4
0 o x | o x
1 | o x | o
2 x | o x |
3 o x | o x
4 | o x | o

Turtles: 5
Trash: 10
Ships: 2
```

---

## Future Work - Work In Progress
Potential enhancements include:
- Adding realistic entity behaviors such as turtle breeding and directed ship movement.
- Incorporating environmental factors like ocean currents to simulate trash accumulation zones.
- Exporting simulation data for visualization in scientific tools.

---