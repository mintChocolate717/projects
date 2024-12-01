/**
 * @author Jiwoong "Alex" Choi
 * @date 2024.11.27
 * @details For COE322 final project
 * EID: JC96768
 * TACC: love_bbq_69
 */
#include <iostream>
using std::cout, std::cin;

// for 2d grid representation
#include <vector>
using std::vector;

/// for visualization of ocean - cursor control in terminal window
#include <cstdio> 

/// for random number generation
#include <random>
// For seeding with time & sleep
#include <chrono>
//  for sleep to simulate grid update
#include <thread> 

#include <variant>
using std::variant, std::monostate;

#include <optional>
using std::optional;

/**
 * @brief random integer generator within defined range
 * @param min the lowest value that random number can be
 * @param max the highest value that random number can be
 * @return int a random integer between min and max
 * @details this function seeds with random_device and then uses static RNG to ensure randomness
 */
int random_int(int min, int max) {
    // seed the generator using random device:
    std::random_device random_device;
    /// @brief create the STATIC engine that's shared by all function invocations
    /// @details the engine has to be static for all function calls, otherwise the generator gets recreated every time, leading to a sequence of identical seed numbers
    static std::default_random_engine static_engine( random_device() );
    // apply distribution to the generator
    std::uniform_int_distribution<int> distribution(min, max);
    // finally return the random int
    return distribution(static_engine);
};

/**
 * @class Ocean
 * @brief 2d cellular representation of ocean with objects
 */
class Ocean {
    public:
        /// @var int turtles
        /// @brief Population of turtles in the simulation.
        int turtles{0};
        /// @var int trash
        /// @brief Amount of trash present in the simulation.
        int trashes{0};
        /// @var int ships
        /// @brief Number of ships involved in the simulation.
        int ships{0};
        /// @var vector<int> grid
        /// @brief Represents the 2D grid used in the simulation.
        /// @details this stores pointers to objects in the ocean
        std::vector<int> grid;
        /// @var int num_rows
        /// @brief Total number of rows in the 2D grid.
        int num_rows{0};
        /// @var int num_cols
        /// @brief Total number of columns in the 2D grid.
        int num_cols{0};
        /// @var int num_cells
        /// @brief Total number of cells in the 2D grid, calculated as num_rows * num_cols.
        int num_cells{0};
    
    public:
        /// @enum Occupy
        /// @brief textual description of what's in the cell instead of "magic numbers"
        enum class Occupy {
            empty = -1, ///< Represents an invalid state.
            turtle = 0, ///< Represents a turtle.
            trash = 1, ///< Represents a trash.
            ship = 2 ///< Represents a ship.
        };
        /**
        * @brief Constructor for Ocean grid object
        * @param m row size
        * @param n column size
        * @param _turtles turtle population
        * @param _trash trash population
        * @param _ships ship population
        * @return creates an ocean object with above parameters
        */
        Ocean(int rows, int cols, int _turtles, int _trash, int _ships) : num_rows(rows), num_cols(cols), turtles(_turtles), trashes(_trash), ships(_ships) {
            /// update number of cells
            num_cells = num_rows * num_cols;
            /// consequenlty, update the grid vector size:
            grid.resize(num_cells);
        };
        
        /**
        * @brief setter for a specific cell
        * @param i index of row, starting at 0
        * @param j index of column, starting at 0
        * @param value value to update that cell
        */
        void set_cell(int i, int j, Ocean::Occupy value) {
            grid.at(i * num_cols + j) = static_cast<int>(value);
        }
        /**
        * @brief getter for a specific cell
        * @param i index of row, starting at 0
        * @param j index of column, starting at 0
        * @return cell state in Occupy enum;
        */
        Ocean::Occupy get_cell(int i, int j) {
            return static_cast<Ocean::Occupy>(grid.at(i * num_cols + j));
        }

        /**
        * @brief creates corresponding ASCII character for each occupied state of the cell
        * @param cell cell's occupied state - empty, turtle, ship, or trash:
        * @return an ASCII character
        */
        char get_ascii(Occupy cell) {
            // use switch-case to identify corresponding ascii char:
            switch (cell) {
                /// empty cell
                case Occupy::empty: return ' ';
                /// turtle cell
                case Occupy::turtle: return 'o';
                /// trash cell
                case Occupy::trash: return 'x';
                /// ship cell
                case Occupy::ship: return '|';
            };
        }

        /**
         * @brief class that defines possible directions of an object in a cell
         */
        enum class Direction {
            Origin,    // No movement
            East,      // E
            North,     // N
            West,      // W
            South,     // S
            NorthEast, // NE
            NorthWest, // NW
            SouthEast, // SE
            SouthWest  // SW
        };

        /**
         * @brief updates coordinate to move the object to the desired position
         * @param x x coordinate
         * @param y y coordinate
         * @param direction the direction which the object will move to 
         * @param object the Occupy obejct in the cell
         */
        void move(int x, int y, Occupy object, Direction direction) {
            // Exit early if the direction is Origin (no movement)
            if (direction == Direction::Origin) { return; }
            
            // Initialize new x and y coordinates
            int new_x = x, new_y = y;

            // Determine the new coordinates based on the direction
            // NOTE: the (i, j) coordinates are (y, x) in our case, so be careful
            switch (direction) {
                case Direction::East: // East
                    new_x++;
                    break;
                case Direction::North: // North
                    new_y++;
                    break;
                case Direction::West: // West
                    new_x--;
                    break;
                case Direction::South: // South
                    new_y--;
                    break;
                case Direction::NorthEast: // North-East
                    new_y++;
                    new_x++;
                    break;
                case Direction::NorthWest: // North-West
                    new_x--;
                    new_y++;
                    break;
                case Direction::SouthEast: // South-East
                    new_x++;
                    new_y--;
                    break;
                case Direction::SouthWest: // South-West
                    new_x--;
                    new_y--;
                    break;
                default: break; // handles Origin case
            }
            // make the current cell empty
            set_cell(x, y, Occupy::empty);
            // Check for out-of-bounds movement: if new coordinate places the object outside of the grid, then let them disappear
            if (new_x < num_cols && new_x >= 0 && new_y < num_rows && new_y >= 0) {
                 // if within the bounds, update the cell of new coordinate
                 set_cell(new_x, new_y, object);
            }
        }

        /**
         * @brief generates movement for a turtle on the ocean grid
         * @details either stays idle, move left, move right, move up, or move down, all equal chances
         * @param x x position of the turtle
         * @param y y position of the turtle
         */
        void turtle_move (int x, int y) {
            // this randomly generated integer decides the move for the turtle
            int move = random_int(0, 4);
            // now determine the move:
            switch (move) {
            // case - doesn't move
            case 0: break;
            // case - move right
            case 1:
                // current cell becomes emtpy:
                set_cell(x, y, Occupy::empty);
                // right cell becomes turtle:
                set_cell(x + 1, y, Occupy::turtle);
                break;
            // case - move left
            case 2:
                // current cell becomes empty:
                set_cell(x, y, Occupy::empty);

            }
        }
        void trash_move () {}
        void ship_move () {}

        /**
        * @brief prints the entire ocean grid with ascii characters
        * @param cell cell's occupied state - empty, turtle, ship, or trash:
        * @return char ASCII character
        * @details the cursor always points back to same position, so the grid is written over the previous one instead of priting new one
        */
        void print_grid() {
            // first, send the cursor to the home position:
            printf( "%c[1;0H",(char)27);
            std::cout << '\n';
            
            // second, print the column indices first:
            std::cout << " ";
            for (int j = 0; j < num_cols; ++j) {
                //then print out indices, only the first digit
                std::cout << " " << j % 10;
            } 
            // move to next line:
            std::cout << '\n';
            
            // third, loop over the entire grid vector and print out in matrix form:
            for (int i = 0; i < num_rows; ++i) { // loop thru each row
                // print the row index at the front
                std::cout << i % 10 << ' ';
                /// loop thru each column
                for (int j = 0; j < num_cols; ++j) {
                    // 1. get each cell's Occupy/Object state
                    Ocean::Occupy cell_state = get_cell(i, j);
                    // 2. print the corresponding ASCII of that cell state:
                    std::cout << get_ascii(cell_state) << " ";
                }
                // move to the new line
                std::cout << '\n';
            }
            // finally print all the populations:
            std::cout << '\n';
            std::cout << "(dummy) Turtles: " << turtles << '\n';
            std::cout << "(dummy) Trash: " << trashes << '\n';
            std::cout << "(dummy) Ships: " << ships << '\n';
        }

    
        void set_dummy_grid() {
            // Fill the grid with some test values
            // Example: Alternate turtles (0), trash (1), and ships (2) in the grid
            for (int i = 0; i < num_cells; ++i) {
                int n = random_int(0, 10);
                if (n == 1) {
                    grid[i] = static_cast<int>(Occupy::turtle);
                } else if (n == 2) {
                    grid[i] = static_cast<int>(Occupy::trash);
                } else if (n == 3) {
                    grid[i] = static_cast<int>(Occupy::ship);
                } else {
                    grid[i] = static_cast<int>(Occupy::empty);
                }
            }
        }


        /**
         * @brief updates the grid
         */
        void update_grid() {};

        void simulate() {
            // update the grid:
            // update_grid()
            // print the grid:
            print_grid();
            // sleep for some time to simulate iteration:
            std::this_thread::sleep_for(std::chrono::seconds(1));
        };
    
};

/**
 * @brief operator overloading of std::cout so that we can directly print out the cell content
 */
std::ostream& operator<<(std::ostream& os, const Ocean::Occupy& occupy) {
    // print out corresponding string for Occupy state:
    switch (occupy) {
        case Ocean::Occupy::empty:
            os << "empty";
            break;
        case Ocean::Occupy::turtle:
            os << "turtle";
            break;
        case Ocean::Occupy::trash:
            os << "trash";
            break;
        case Ocean::Occupy::ship:
            os << "ship";
            break;
    }
    return os;
}

// for now, object-based grid is not necessary
#if 0
/**
 * @class Object
 * @brief represents an object within a single cell of ocean grid
 */
class Object{
    protected:
        /// @var int x
        /// @brief  x coordinate of an object within a 2d grid
        int x{0};
        /// @var int y
        /// @brief y coordinate of an object within a 2d grid
        int y{0};
    
    public:
        /// @brief constructor of an ocean object
        Object(int x_pos, int y_pos) : x(x_pos), y(y_pos) {};

        /// @brief default movement of an object
        virtual void move() = 0;

        /// @brief getter for x position
        int get_x() const {return x;}
        /// @brief getter for y position
        int get_y() const {return y;}
};

/**
 * @class Turtle -> parent class: Object
 * @brief represents an object Turtle floating around the ocean
 */
class Turtle : public Object {
    public:
        /// @brief constructor for a turtle
        Turtle(int x_pos, int y_pos) : Object(x_pos, y_pos) {};

        /// @brief applies movement to the turtle in the ocean
        void turtle_move() {

        };
};

/**
 * @class Trash -> parent class: Object
 * @brief represents an object Trash floating around the ocean
 */
class Trash : public Object {
    public:
        /// @brief constructor for a turtle
        Trash(int x_pos, int y_pos) : Object(x_pos, y_pos) {};

        /// @brief applies movement to the turtle in the ocean
        void trash_move() {

        };
};

/**
 * @class Ship -> parent class: Object
 * @brief represents an object Ship floating around the ocean
 */
class Ship : public Object {
    public:
        /// @brief constructor for a turtle
        Ship(int x_pos, int y_pos) : Object(x_pos, y_pos) {};

        /// @brief applies movement to the turtle in the ocean
        void ship_move() {

        };
};
#endif

int main() {
    Ocean ocean(10, 10, 0, 0, 0);
    std::vector<int> example = {
    // Row 0
    static_cast<int>(Ocean::Occupy::turtle), static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::trash),
    static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::ship), static_cast<int>(Ocean::Occupy::empty),
    static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::trash), static_cast<int>(Ocean::Occupy::turtle),
    static_cast<int>(Ocean::Occupy::empty),
    // Row 1
    static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::ship),
    static_cast<int>(Ocean::Occupy::trash), static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::turtle),
    static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::trash), static_cast<int>(Ocean::Occupy::ship),
    static_cast<int>(Ocean::Occupy::empty),
    // Row 2
    static_cast<int>(Ocean::Occupy::turtle), static_cast<int>(Ocean::Occupy::ship), static_cast<int>(Ocean::Occupy::empty),
    static_cast<int>(Ocean::Occupy::trash), static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::empty),
    static_cast<int>(Ocean::Occupy::turtle), static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::trash),
    static_cast<int>(Ocean::Occupy::ship),
    // Row 3
    static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::empty),
    static_cast<int>(Ocean::Occupy::ship), static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::trash),
    static_cast<int>(Ocean::Occupy::turtle), static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::trash),
    static_cast<int>(Ocean::Occupy::empty),
    // Row 4
    static_cast<int>(Ocean::Occupy::trash), static_cast<int>(Ocean::Occupy::turtle), static_cast<int>(Ocean::Occupy::empty),
    static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::trash), static_cast<int>(Ocean::Occupy::empty),
    static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::ship), static_cast<int>(Ocean::Occupy::turtle),
    static_cast<int>(Ocean::Occupy::empty),
    // Row 5
    static_cast<int>(Ocean::Occupy::turtle), static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::empty),
    static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::trash),
    static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::turtle), static_cast<int>(Ocean::Occupy::ship),
    static_cast<int>(Ocean::Occupy::empty),
    // Row 6
    static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::trash), static_cast<int>(Ocean::Occupy::turtle),
    static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::ship), static_cast<int>(Ocean::Occupy::turtle),
    static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::trash),
    static_cast<int>(Ocean::Occupy::empty),
    // Row 7
    static_cast<int>(Ocean::Occupy::trash), static_cast<int>(Ocean::Occupy::turtle), static_cast<int>(Ocean::Occupy::empty),
    static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::ship), static_cast<int>(Ocean::Occupy::trash),
    static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::turtle),
    static_cast<int>(Ocean::Occupy::empty),
    // Row 8
    static_cast<int>(Ocean::Occupy::ship), static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::turtle),
    static_cast<int>(Ocean::Occupy::trash), static_cast<int>(Ocean::Occupy::trash), static_cast<int>(Ocean::Occupy::empty),
    static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::ship), static_cast<int>(Ocean::Occupy::trash),
    static_cast<int>(Ocean::Occupy::empty),
    // Row 9
    static_cast<int>(Ocean::Occupy::turtle), static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::empty),
    static_cast<int>(Ocean::Occupy::ship), static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::trash),
    static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::empty), static_cast<int>(Ocean::Occupy::trash),
    static_cast<int>(Ocean::Occupy::turtle)
};
    ocean.grid = example; // Directly assign the grid
    ocean.print_grid();

    std::cout << "(2, 8): "<<ocean.get_cell(2, 8) << '\n';
    std::cout << "(1, 9): "<<ocean.get_cell(1, 9) << '\n';

    ocean.move(2, 8, Ocean::Occupy::ship, Ocean::Direction::NorthEast);
    
    std::cout <<"(2, 8): should be empty ->  " << ocean.get_cell(2, 8) << '\n';   
    std::cout << "(1, 9): should be ship -> "<<ocean.get_cell(1, 9) << '\n'; 

    #if 0
    // Simulate grid updates in a loop
    for (int t = 0; t < 20; ++t) { // Simulate 10 time steps
        // Print the grid (this will overwrite the previous grid)
        ocean.simulate();

        // Simulate a grid update
        // Example: Modify grid contents here
        ocean.set_dummy_grid(); // Resetting for now
    }
    #endif
}

