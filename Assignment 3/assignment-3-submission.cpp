/*
    Assignment 3: Linked Lists
    Authors: Group 6

    Requirements:
    -------------
    Linked List Implementation
        - Implement a linked list to store records
        - Each record should contain two fields: name (string) and age (int)
        - ** Implement functions for creating a new linked list, adding a record,
          deleting a record, and printing the list **
    Sorted Insertion
        - Ensure that the list remains sorted alphabetically at all times
        - When adding a new record, insert it into the correct position in the 
          list based on the alphabetical order of names
    Deletion
        - Implement functionality to delete any or all records in the list
        - Provide options for deleting records by name or age
    Printing
        - Implement a function to print the list in order of insertion (sorted by name)
        - Implement a function to print the list in order of age, from youngest to oldest
    User Interface (UI)
        - Develop a simple command-line interface for users to interact with your program
        - Provide options for adding new records, deleting records, and printing the list
          by name or age


    Notes:
    ------
    (lavender): i would have like to split up the work more easily with
                header files, but unfortunately we have to submit a single
                source file 

    (lavender): for the sorting part, after some messing around i think that
                the best option is to keep the list sorted by name, and 
                basically reverse bubble sort the list if the user wants to
                print the list by age, keeping the main list still by age


    Contributions:
    --------------
    Camron: 
    Evan: 
    Lavender: file setup and specs, function prototypes,  
    Teddy: 
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

// Struct prototypes
/*
    information:
    ------------
    `Node` just your average linked list,
    must contain a `Record` and a pointer to
    the next node

    `Record` is the data that will be kept in 
    each node; contains a name (string) and an age (int)
*/
struct Node;
struct Record;

// List function prototypes
// (do not change return or parameter types unless necessary)
/*
    information:
    ------------
    for functions with `Node*` return type,
    return the head node of the list (or `nullptr`
    if there are no nodes in the list)

    if you encounter errors, print the error (ex. 
    node not found), print the error and return 
    the head of the list as usual

    `add_record()` and delete_record must handle getting
    input from the user for what to add/delete

    `delete_record()` must be able to delete by either
    name or age

    `print_list()` must be able to print by either 
    name or age
*/
Node* new_list();
Node* add_record(Node*, Record*);
Node* delete_record(Node*, Record*);
Node* delete_list(Node*);
void print_list(Node*);

// UI prototypes
void action_loop();

int main() {

}