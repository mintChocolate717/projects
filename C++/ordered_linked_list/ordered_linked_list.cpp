/*
Name: Alex Choi
Last Edited: October 20, 2024

### Problem Description

This C++ code implements a sorted linked list that stores unique values in increasing order. The list is constructed using `Node` and `List` classes with smart pointers (specifically `shared_ptr`) to manage memory efficiently.

Key features of this linked list implementation:
1. Node Class: Represents individual elements in the list. Each node contains:
   - A `datavalue` to store the integer value.
   - A `datacount` to track occurrences of the value.
   - A `next` pointer to the next node, allowing traversal through the list.

2. List Class: Manages the linked list and provides methods to:
   - Insert elements in sorted order (head, middle, or tail).
   - Check if a value exists in the list.
   - Print the list elements in order.
   - Calculate the length of the list.

The code includes multiple insertion cases:
- Head Insertion: If a value is smaller than the current head node, a new head is created.
- Middle Insertion: Inserts values in sorted order between existing nodes.
- Tail Insertion: Appends the value at the end if it is the largest.

### Example Usage in main()

The main function initializes an empty list and allows interactive user input. It accepts integers, inserting each into the list in sorted order and printing the list after each insertion. The program terminates when the user inputs zero.
*/

#include <vector>
using std::vector;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

//for smart pointers
#include <memory>
using std::shared_ptr;
using std::make_shared;

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> class Node <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
class Node {
  private:
    //
    int datavalue{0}, datacount{0};
    shared_ptr<Node> next{nullptr}; //A Null pointer indicates the tail of the list.
  
  public:
    //default constructor - nothing
    Node() {};
    //constructor, default value of nextptr is nullptr
    Node(int value, shared_ptr<Node> next = nullptr) : datavalue(value), datacount(1), next(next) {};

    //checks if there's a next node from the current one:
    bool has_next() {
      return next != nullptr;
    };

    //method for calcualting length of the list
    int length() {
      // check if there's a next node
      if (! has_next()) {
        return 1; // if not, just send the count of this node, 1
      } else {
        // if it's not the last node, count the curreont one and call next one:
        return 1 + next -> length();
      }
    };

    // method for inserting a node elemnt
    void insert(int value) {
      //check if the current node already has that value:
      if (value == datavalue) {
        // if yes, increase the count
        datacount++;
      // if the current node doesn't contain that value, check the next node:
      } else if (has_next()) {
        next -> insert(value);
      }

    };

    //checks if any of the node contains value:
    bool contains_value(int value) {
      // check if the current node has the value:
      if (datavalue == value) {
        return true; // then return true
      // then if current node doesn't have that value and is the last node, return false:
      } else if (next == nullptr) {
        return false;
      // if all else, apply it to the next node:
      } else {
        return next -> contains_value(value);
      }
    };

    void print() {
      //print out the current node:
      std::cout << datavalue << ":" << datacount;
      //print its tail
      if (has_next()) {
        std::cout << ", ";
        next -> print();
      }
    };

    int value() {
      return datavalue;
    };

    // Make sure this method returns a reference to allow modification in middle insertion
    shared_ptr<Node>& nextnode() {
      return next;
    }
    int count() {
      return datacount;
    };

};

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> class List <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
class List {
    private:
      //shared ptr that points to current Node object
      shared_ptr<Node> head{ nullptr };
    
    public:
      //constructor
      List() {};

      auto headnode() {
        return head;
      };

      // computes list length iteratively - efficient
      int length() {
        // CASE: only head node
        if (head == nullptr) {
          return 0;
        }
        //count variable
        int count = 1;
        auto current = head;
        // loop until the end node:
        while (current -> has_next()) {
          count++;
          current = current -> nextnode();
        }
        return count;
      };

      //method for inserting a new node at the front
      void insert(int value) {
        //CASE: when it's an empty list
        if (head == nullptr) {
          // initialize the first element using the constructor of Node class
          head = make_shared<Node> (value); // use default value for next ptr
          //exit
          return;
        }

        //CASE: HEAD DUPLICATE - when the head node's value equals the input value:
        else if (value == head -> value()) {
          head -> insert(value);
          //exit
          return;
        }

        //CASE: HEAD INSERTION - when the current value is smaller than the head node's value:
        else if (value < head -> value()) {
          // since we only had one Node before, that only node had ptr head.
            // now, inserting a new node before the existing one will cause the new node's next ptr
            // to be set to the current node's head ptr
            auto new_node = make_shared<Node> (value, head);
            //after that, the head ptr now points to the new node inserted at the head:
            head = new_node;
            //exit:
            return;
        }
        
        //CASE: MIDDLE INSERTION - inserting new node at the middle
        // set the current_ptr to head, meaning pointing at the first node:
        auto current_ptr = head; // we can't start at head -> nextnode() cause list might only have one node
        // loop through the entire list until the last node:
        while(current_ptr -> has_next()) {
          // first check if the value is equal to the next node ptr's value:
          if (value == current_ptr -> nextnode() -> value()) {
            current_ptr -> nextnode() -> insert(value);
            // exit
            return;
          }
          // check if the value is smaller than the next node ptr's value
          else if (value < current_ptr -> nextnode() -> value()) {
            // then place the new node with the value
            // new node's next ptr becomes current ptr's node's next ptr since we are inserting in the middle
            auto new_node = make_shared<Node> (value, current_ptr -> nextnode());
            // then the CURRENT ptr's node's next_ptr becomes newly created node's ptr:
            current_ptr -> nextnode() = new_node;
            // now, exit outta the loop to prevent unneessary computing:
            return;
          // otherwise: move to the next node
          } else { current_ptr = current_ptr -> nextnode(); }
        }

        //CASE: TAIL INSERTION - when the current value is the largest, inserting at the tail
        //note that we tested out head insertion, middle insertion with previous code
        // so tail insertion is only left now:
        auto new_tail_node = make_shared<Node> (value);
        current_ptr -> nextnode() = new_tail_node;
      };

      //checks if an item is in the list
      bool contains_value(int value) {
        //case when the list is empty, return false:
        if (head ==  nullptr) {
          return false;
        } else {
          // if the list is NOT empty, call Node class's method:
          return head -> contains_value(value);
        }
      };

      void print() {
        std::cout << "List";
        // if the list is not empty:
        if (head != nullptr) {
          std::cout << " => ";
          head -> print(); //use shared pointer to print Nodes
          std::cout << "\n";
        }
      };
      /*
      int length_iterative();
      */
};

int main() {
      /*
    //create a list
    List mylist;
    std::cout << "Empty list has length: " << mylist.length() << '\n';
    mylist.print();

    mylist.insert(3);
    std::cout << "After inserting 3 the length is: " << mylist.length() << '\n';
    mylist.print();
    
    if (mylist.contains_value(3))
        cout << "Indeed: contains 3" << '\n';
    else
        cout << "Hm. Should contain 3" << '\n';
    if (mylist.contains_value(4))
        cout << "Hm. Should not contain 4" << '\n';
    else
        cout << "Indeed: does not contain 4" << '\n'; cout << '\n';
    
    mylist.insert(3);
    cout << "Inserting the same item gives length: " << mylist.length() << '\n';
    mylist.print();

    if (mylist.contains_value(3)) {
        cout << "Indeed: contains 3" << '\n';
        auto headnode = mylist.headnode();
        cout << "head node has value " << headnode->value()
             << " and count " << headnode->count() << '\n';
    } else
        cout << "Hm. Should contain 3" << '\n';
    cout << '\n';
    
    mylist.insert(2);
    cout << "Inserting 2 goes at the head;\nnow the length is: " << mylist.length() << '\n';
    mylist.print();

    if (mylist.contains_value(2))
        cout << "Indeed: contains 2" << '\n';
    else
        cout << "Hm. Should contain 2" << '\n';
    if (mylist.contains_value(3))
        cout << "Indeed: contains 3" << '\n';
    else
        cout << "Hm. Should contain 3" << '\n';
    cout << '\n';

  
    mylist.insert(6);
    cout << "Inserting 6 goes at the tail;\nnow the length is: " << mylist.length() << '\n';
    mylist.print();
    if (mylist.contains_value(6))
        cout << "Indeed: contains 6" << '\n';
    else
        cout << "Hm. Should contain 6" << '\n';
    if (mylist.contains_value(3))
        cout << "Indeed: contains 3" << '\n';
    else
        cout << "Hm. Should contain 3" << '\n';
    cout << '\n';

    mylist.insert(4);
    cout << "Inserting 4 goes in the middle;\nnow the length is: " << mylist.length() << '\n';
    mylist.print();
    if (mylist.contains_value(4))
        cout << "Indeed: contains 4" << '\n';
    else
        cout << "Hm. Should contain 4" << '\n';
    if (mylist.contains_value(3))
        cout << "Indeed: contains 3" << '\n';
    else
        cout << "Hm. Should contain 3" << '\n';
    cout << '\n';

    cout << "List has length: " << mylist.length() << '\n';
    cout << '\n';

    {
        cout << "Another check.\n";
        List mylist;
        for (auto i : {15, 23, 11, 75, 11, 65, 3}) {
            cout << "insert: " << i << '\n';
            mylist.insert(i);
        }
        mylist.print();
    }
    */
  // make an empty list
  List mylist;
  // container for user input
  int user_input = -1;

  //start a while loop and end it when user gives input of zero:
  while (true) {
    // ask for user to input a number
    std::cout << "\nEnter a value: ";
    // store it
    std::cin >> user_input;

    // if user inputs zero, end the program
    if (user_input == 0) {
      std::cout << "\n!!! User inputs zero (0), program terminating..." << std::endl;
      break;
    }
    // anything else, proceed with regular program
    else {
      //insert a number into the linked list:
      mylist.insert(user_input);
      // after each number, print the list for as far as it has been constructed
      mylist.print();
    }
  }
  return 0;
}

