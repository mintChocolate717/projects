/**
 * @author Jiwoong "Alex" Choi
 * @date 2024.12.06
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

#include <tuple>
using std::tuple;

#include <optional>
using std::optional, std::nullopt;

#include <map>
using std::map;

#include <algorithm>


/**
 * ***********************************************************************************************************************************************************************
 * SECTION - Random Number Generators
 * @section RandomNumberGenerators Random Number Generators
 * This section contains functions for generating random integers and floats.
 * ***********************************************************************************************************************************************************************
 */
/**
 * @brief random integer generator within defined range
 * @param min the lowest value that random number can be, default 0
 * @param max the highest value that random number can be, default 1
 * @return int a random integer between min and max, inclusive [min, max]
 * @details this function seeds with random_device and then uses static RNG to ensure randomness
 */
int random_int(int min = 0, int max = 1) {
    // seed the generator using random device (static reduces computation time and overhead)
    static std::random_device random_device;
    /// @brief create the STATIC engine that's shared by all function invocations
    /// @details the engine has to be static for all function calls, otherwise the generator gets recreated every time, leading to a sequence of identical seed numbers
    static std::default_random_engine static_engine( random_device() );
    // apply distribution to the generator
    std::uniform_int_distribution<int> distribution(min, max);
    // finally return the random int
    return distribution(static_engine);
};

/**
 * @brief random float generator within defined range
 * @param min the lowest value that random number can be, default 0.0
 * @param max the highest value that random number can be, default 1.0
 * @return float a random float between min (inclusive) and max(exclusive), [min, max)
 * @details this function seeds with random_device and then uses static RNG to ensure randomness
 */
float random_float(float min = 0.f, float max = 1.f) {
    // seed the generator using random device (static reduces computation time and overhead)
    static std::random_device random_device;
    /// @brief create the STATIC engine that's shared by all function invocations
    /// @details the engine has to be static for all function calls, otherwise the generator gets recreated every time, leading to a sequence of identical seed numbers
    static std::default_random_engine static_engine( random_device() );
    // apply distribution to the generator
    std::uniform_real_distribution<float> distribution(min, max);
    // finally return the random float
    return distribution(static_engine);
};

/**
 * ***********************************************************************************************************************************************************************
 * SECTION - class Ocean
 * @section OceanClass class Ocean
 * This section contains memebrs for Ocean class
 * ***********************************************************************************************************************************************************************
 */
/**
 * @class Ocean
 * @brief 2d cellular representation of ocean with objects
 */
class Ocean {
    protected: // @todo later change to private/protected
        /// @var int num_turtles
        /// @brief Population of turtles in the simulation.
        int num_turtle{0};
        
        /// @var int num_trashes
        /// @brief Amount of trash present in the simulation.
        int num_trash{0};
        
        /// @var int num_ships
        /// @brief Number of ships involved in the simulation.
        int num_ship{0};
        
        /// @var int population
        /// @brief hash map storing the Number of each demographics involved in the simulation.
        std::map<int, int> population = {
            {0, num_turtle},
            {1, num_trash},
            {2, num_ship}
        };

    
    public:
        /// @enum Occupy
        /// @brief textual description of what's in the cell instead of "magic numbers"
        enum class Occupy {
            Empty = -1, ///< Represents an invalid state.
            Turtle = 0, ///< Represents a turtle.
            Trash = 1, ///< Represents a trash.
            Ship = 2 ///< Represents a ship.
        };

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

        /**
        * @brief Constructor for Ocean grid object
        * @param m row size
        * @param n column size
        * @param _turtles turtle population
        * @param _trash trash population
        * @param _ships ship population
        * @return creates an ocean object with above parameters
        */
        Ocean(int rows, int cols, int _turtles, int _trash, int _ships) : num_rows(rows), num_cols(cols), num_turtle(_turtles), num_trash(_trash), num_ship(_ships) {
            /// update number of cells
            this->num_cells = num_rows * num_cols;
            /// consequenlty, update the grid vector size:
            this->grid.resize(num_cells);
        };
        /**
        * @brief Copy Constructor of Ocean Object
        * @param m row size
        * @param n column size
        * @param _turtles turtle population
        * @param _trash trash population
        * @param _ships ship population
        * @return creates a copied ocean object with above parameters
        */
        Ocean(const Ocean& other) : grid(other.grid), num_rows(other.num_rows), num_cols(other.num_cols), num_turtle(other.num_turtle), num_trash(other.num_trash), num_ship(other.num_ship), num_cells(other.num_cells) {}
        
        /**
        * @brief setter for a specific cell
        * @param ocean the current object Ocean that this method is acting upon
        * @param i index of row, starting at 0
        * @param j index of column, starting at 0
        * @param value value to update that cell
        */
        void set_cell(int i, int j, Ocean::Occupy value) {
            this->grid.at(i * num_cols + j) = static_cast<int>(value);
        }
        /**
        * @brief getter for a specific cell
        * @param ocean the current object Ocean that this method is acting upon
        * @param i index of row, starting at 0
        * @param j index of column, starting at 0
        * @return cell state in Occupy enum;
        */
        Ocean::Occupy get_cell(int i, int j) {
            return static_cast<Ocean::Occupy>(this->grid.at(i * num_cols + j));
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
                case Occupy::Empty: return ' ';
                /// turtle cell
                case Occupy::Turtle: return 'o';
                /// trash cell
                case Occupy::Trash: return 'x';
                /// ship cell
                case Occupy::Ship: return '|';
                default:
                    return '?'; // place holder for possible unknown state
            };
        }

        /**
         * ***********************************************************************************************************************************************************************
         * SUB_SECTION - Movement Logics
         * @subsection ObjectMovement movement logics/definitions
         * This section contains functions, enum classes that define movement & collision logic for objects
         * ***********************************************************************************************************************************************************************
         */
        public:
        //protected:
            /**
             * @brief class that defines possible directions of an object in a cell
             * @details numbers for eaiser code writing
             */
            enum class Direction {
                Idle = 0,    // No movement
                East = 1,      // E
                North = 2,     // N
                West = 3,      // W
                South = 4,     // S
                NorthEast = 5, // NE
                NorthWest = 6, // NW
                SouthEast = 7, // SE
                SouthWest = 8  // SW
            };
            
            /**
             * @brief class that defins possible optoins of collision outcome between two objects
             * @details all of these are written interms of a current object that is moving into a new cell space:
             */
            enum class CollisionResult {
                Move = 1, // moving object successfully moves into new space because there's nothing in new space
                Die = 2, // movign object dies from collision (e.g. turtle dies after colliding with trash)
                Block = 0, // moving object encounters same type of object (trash vs trash) or non-threatening object (ship vs turtle) and stays idle
            };

            /**
             * @brief logic/outcome matrix for collision between two objects.
             * @details Key: {Moving Object, Existing Object} and Value: Action for Moving Object
             */
            std::map<std::pair<Ocean::Occupy, Ocean::Occupy>, Ocean::CollisionResult> collision_logics = {
                // Turtle encounters an empty space -> It can move.
                { {Ocean::Occupy::Turtle, Ocean::Occupy::Empty},   Ocean::CollisionResult::Move },
                // Turtle encounters trash -> It dies.
                { {Ocean::Occupy::Turtle, Ocean::Occupy::Trash},   Ocean::CollisionResult::Die },
                // Turtle encounters a ship -> Movement is blocked.
                { {Ocean::Occupy::Turtle, Ocean::Occupy::Ship},    Ocean::CollisionResult::Block },
                // Turtle encounters another turtle -> Movement is blocked.
                { {Ocean::Occupy::Turtle, Ocean::Occupy::Turtle},  Ocean::CollisionResult::Block },

                // Trash encounters an empty space -> It can move.
                { {Ocean::Occupy::Trash,  Ocean::Occupy::Empty},   Ocean::CollisionResult::Move },
                // Trash encounters a turtle -> Movement is blocked.
                { {Ocean::Occupy::Trash,  Ocean::Occupy::Turtle},  Ocean::CollisionResult::Move },
                // Trash encounters another trash -> Movement is blocked.
                { {Ocean::Occupy::Trash,  Ocean::Occupy::Trash},   Ocean::CollisionResult::Block },
                // Trash encounters a ship -> Movement is blocked.
                { {Ocean::Occupy::Trash,  Ocean::Occupy::Ship},    Ocean::CollisionResult::Die },

                // Ship encounters an empty space -> It can move.
                { {Ocean::Occupy::Ship,   Ocean::Occupy::Empty},   Ocean::CollisionResult::Move },
                // Ship encounters trash -> It survives and remains functional.
                { {Ocean::Occupy::Ship,   Ocean::Occupy::Trash},   Ocean::CollisionResult::Move },
                // Ship encounters another ship -> Movement is blocked.
                { {Ocean::Occupy::Ship,   Ocean::Occupy::Ship},    Ocean::CollisionResult::Block },
                // Ship encounters a turtle -> Movement is blocked.
                { {Ocean::Occupy::Ship,   Ocean::Occupy::Turtle},  Ocean::CollisionResult::Block}
            };

            /**
             * @brief performs collision logic between two objects and updates the cell
             * @param i row index of 
             * @param j column index
             * @param direction the direction which the object will move to 
             * @param moving_obj the object that is trying to move to new (i, j) coordinate
             * @param arg_grid grid to work with. can be grid or temp_grid
             * @return tuple of {i, j, moving_obj, new_i, new_j, colliding_obj}
             */
            std::tuple<int, int, Occupy, int, int, Occupy> collision(int i, int j, int new_i, int new_j, Occupy moving_obj, const std::vector<int>& arg_grid) {
                // get the object existing at the new location that will "crash" with moving_obj
                Occupy existing_obj = static_cast<Occupy>(arg_grid[new_i * num_cols + new_j]);

                CollisionResult collision_outcome = collision_logics[{moving_obj, existing_obj}];

                // start performing collision logics:
                switch (collision_outcome) {
                    // Case 1 - moving_obj can proceed to moving into new cell:
                    case CollisionResult::Move:
                        // current cell becomes empty:
                        // this->set_cell(i, j, Occupy::Empty);
                        // new cell becomes the moving_obj:
                        // this->set_cell(new_i, new_j, moving_obj);
                        return{i, j, Occupy::Empty, new_i, new_j, moving_obj};
                    
                    // Case 2 - moving_obj dies:
                    case CollisionResult::Die:
                        // current cell becomes empty:
                        // this->set_cell(i, j, Occupy::Empty);
                        // new cell remains the same
                        //break;
                        return{i, j, Occupy::Empty, new_i, new_j, existing_obj};

                    // Case 2 - moving_obj's move is Blocked:
                        // new_cell and old_cell all remain the same:
                        // break;
                        return{i, j, moving_obj, new_i, new_j, existing_obj};
                    
                    default:
                        break;
                }
            };


            /**
             * @brief updates coordinate to move the object to the desired position
             * @param i row index
             * @param j column index
             * @param direction the direction which the object will move to 
             * @param object the Occupy obejct in the cell
             */
            std::tuple<int, int, Occupy, int, int, Occupy> move(int i, int j, Occupy object, Direction direction) {
                // Exit early if the direction is Origin (no movement) or if object is empty
                if (direction == Direction::Idle or object == Occupy::Empty) { return; }
                // Initialize new x and y coordinates
                int new_i = i, new_j = j;
                
                // Determine the new coordinates based on the direction
                // BE CAREFUL: the (i, j) coordinates are (-y, x) in our case, so be careful
                // @details for example, "moving East" in our printed grid is increasing j index
                switch (direction) {
                    case Direction::East: // East
                        new_j++;
                        break;
                    case Direction::North: // North
                        new_i--;
                        break;
                    case Direction::West: // West
                        new_j--;
                        break;
                    case Direction::South: // South
                        new_i++;
                        break;
                    case Direction::NorthEast: // North-East
                        new_i--; 
                        new_j++;
                        break;
                    case Direction::NorthWest: // North-West
                        new_i--;
                        new_j--;
                        break;
                    case Direction::SouthEast: // South-East
                        new_i++;
                        new_j++;
                        break;
                    case Direction::SouthWest: // South-West
                        new_i++;
                        new_j--;
                        break;
                    default: break; // handles Origin case
                }
                // Check for out-of-bounds movement: if the new position is invalid, return early
                if (new_i < 0 or new_i >= num_rows or new_j < 0 or new_j >= num_cols) {
                    return {i, j, object, i, j, object};
                }

                // If within bounds, finish the moving logic with collision logic:
                return this->collision(i, j, new_i, new_j, object, grid);
            };
        
        public:
        //protected:
            /**
             * @brief generates random direction based on the user-defined probability for object staying idle
             * @param idle_chance the probability that object stays idle
             * @return random integer that corresponds to one of the moves in class Direction based on user-set parameters of probability
             */
            Ocean::Direction random_direction(float idle_chance = (1. / 9.f)) {
                // in total we have 9 moves total, with 1 move being idle and rest of 8 moves being active
                // based on the given idle_chance, we return corresponding move with pre-defined probabilities
                float random_num = random_float(0.0, 1.); // 100% percentage pdf
                
                // simulate idle_chance probability:
                if (random_num < idle_chance) {
                    // if probability satisfies, return Idle:
                    return Ocean::Direction::Idle;
                } else {
                    // rest of the probability, return one of the active moves:
                    return static_cast<Ocean::Direction>(random_int(1, 8));
                }
            }

            /**
             * @brief generates movement for a turtle on the ocean grid
             * @details all moves have equal chance of being executed from enum class Direction
             * @param i row index
             * @param j column index
             */
            std::tuple<int, int, Occupy, int, int, Occupy> turtle_move (int i, int j) {
                // use random_direction () function with default prob of 1 / 9.
                //this->move(i, j, Occupy::Turtle, this->random_direction());
                return this->move(i, j, Occupy::Turtle, this->random_direction());
            };
            
            /**
             * @brief generates movement for a trash on the ocean grid
             * @details 50% chance of staying idle and 50% of moving in any random direction
             * @param i row index
             * @param j column index
             */
            std::tuple<int, int, Occupy, int, int, Occupy> trash_move (int i, int j) {
                // use random_direction () function with idle prob of 50%.
                //this->move(i, j, Occupy::Trash, this->random_direction(0.5f));
                return this->move(i, j, Occupy::Trash, this->random_direction(0.5f));

            };
            /**
             * @brief generates movement for a ship on the ocean grid
             * @details 20% chance of staying idle and 80% of moving in any random direction
             * @param i row index
             * @param j column index
             */        
            std::tuple<int, int, Occupy, int, int, Occupy> ship_move (int i, int j) {
                // use random_direction () function with idle prob of 20%.
                //this->move(i, j, Occupy::Ship, this->random_direction(0.2f));
                return this->move(i, j, Occupy::Ship, this->random_direction(0.2f));
            };

        
        public:
            /**
            * @brief prints the entire ocean grid with ascii characters
            * @param cell cell's occupied state - empty, turtle, ship, or trash:
            * @return char ASCII character
            * @details the cursor always points back to same position, so the grid is written over the previous one instead of priting new one
            */
            void print_grid() {
                // first, send the cursor to the home position:
                //printf( "%c[1;0H",(char)27); /// TODO: change later
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
                std::cout << "(dummy) Turtles: " << num_turtle << '\n';
                std::cout << "(dummy) Trash: " << num_trash << '\n';
                std::cout << "(dummy) Ships: " << num_ship << '\n';
            }

            void set_dummy_grid() {
                // Fill the grid with some test values
                // Example: Alternate turtles (0), trash (1), and ships (2) in the grid
                for (int i = 0; i < num_cells; ++i) {
                    int n = random_int(0, 10);
                    if (n == 1) {
                        grid[i] = static_cast<int>(Occupy::Turtle);
                    } else if (n == 2) {
                        grid[i] = static_cast<int>(Occupy::Trash);
                    } else if (n == 3) {
                        grid[i] = static_cast<int>(Occupy::Ship);
                    } else {
                        grid[i] = static_cast<int>(Occupy::Empty);
                    }
                }
            }

            /**
             * @brief updates the grid using data independent method
             * @details First, initializes temp_grid to all zeros. 
             *          Second, performs all updates on temp_grid while using data from grid to avoid data dependency.
             *          Basically, we read from grid and write to temp_grid
             */
            void update_grid() {
                // intialize the grid_copy
                std::vector<int> temp_grid(num_cells, 0);
                
                // Iterate over this temp_ocean:
                // iterate over rows:
                for (int i = 0; i < num_rows; ++i) {
                    // iterate over columns:
                    for (int j = 0; j < num_cols; ++j) {
                        // retrieve cell state from the temp_grid (again, grid that's not getting updated)
                        Occupy curr_obj = static_cast<Occupy>(this->get_cell(i, j));
                        // skip empty cells
                        if (curr_obj == Occupy::Empty) { continue; }
                        // placeholder for later:
                        auto result = std::make_tuple(i, j, curr_obj, i, j, curr_obj);
                        // perform movement based on the object type
                        switch(curr_obj) {
                            // when Turtle
                            case Occupy::Turtle:
                                result =  this->turtle_move(i, j);
                                break;
                            // when Trash
                            case Occupy::Trash:
                                result = this->trash_move(i, j);
                                break;
                            // when  Ship
                            case Occupy::Ship:
                                result = this->ship_move(i, j);
                                break;
                            // default:
                            default: break;
                        }

                        // unpack tuple values:
                        /** @details Defitinions for tuple values below:
                         * old_i, old_j : row, col indices for object at current position
                         * old_obj   : object that is at current position possibly trying to move to new position, if possible
                         * new_i, new_j : row, col indices for object at a position that moving_obj is possibly trying to move to
                         * new_obj: object that is at the "new" coordinate that will "collide" with incoming moving_obj
                         */
                        auto [old_i, old_j, old_obj, new_i, new_j, new_obj] = result;
                        
                        // update old cell, ths is always safe and true to do
                        if (old_obj != Occupy::Empty) { // only do this if moving_obj is not empty
                            temp_grid[old_i * num_cols + old_j] = static_cast<int>(old_obj);
                        }

                        // compute the linearized index for (new_i, new_j):
                        int new_index = new_i * num_cols + new_j;

                        /**
                         * @subsection this is where we start to handle collision that's happening at temp_grid as we update.
                         * @details here, we check if the new cell is occupied or not. if occupied, we handle colllision using logics defined above
                         */
                        // check if new cell is already occupied:
                        // if it's NOT occupied, just set it to the colliding_obj
                        if (static_cast<Occupy>(temp_grid[new_index]) == Occupy::Empty) {
                            temp_grid[new_index] = static_cast<int>(new_obj);
                        } else { // if occupied, handle the collision
                            // get the object that will occupy the new cell:
                            Occupy surviving_obj = std::get<5>(this->collision(new_i, new_j, new_i, new_j, new_obj, temp_grid));
                            // set the surviving_obj to the temp_grid:
                            temp_grid[new_index] = static_cast<int>(surviving_obj);
                        }

                    }
                }
                // make substitution:
                this->grid = std::move(temp_grid);
            };

            void update() {
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
        case Ocean::Occupy::Empty:
            os << "empty";
            break;
        case Ocean::Occupy::Turtle:
            os << "turtle";
            break;
        case Ocean::Occupy::Trash:
            os << "trash";
            break;
        case Ocean::Occupy::Ship:
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
    Ocean ocean(4, 4, 0, 0, 0);
    std::vector<int> example = {
        // Row 0
        0, -1, 1, -1,
        // Row 1
        -1, -1, 2, 1,
        // Row 2
        0, 2, -1, 1,
        // Row 3
        -1, -1, -1, 2
    };
    ocean.grid = example;

    ocean.print_grid();

    return 0;
}

