/*
    Assignment 3: Linked Lists
    Authors: Group 6


    Code Layout:
    ------------
    - Main comment (this block)
    - `include` statements
    - Struct and function prototypes
    - `main()`
    - Struct and function implementations


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

    (lavender): while some of the functions declared below in the `prototypes`
                section are not implemented yet, you can create all of your
                code as if they were, since their parameter and return types
                should be the same as they are now (i don't reccomend changing
                them without consulting the group). this is especially important
                for teddy, who i've assigned to do ui; most of what you'll be 
                doing is printing options to the user, getting their input,
                and calling the related functions in order to enact what
                the user chose. if you need help, please reach out to me.

    (lavender): in my opinion, the hardest parts of this homework are the 
                sorted insertion and the printing by age (personally i could
                not really find any easy ways to do this; printing by name is
                relatively easy, since that is what the list is usually sorted
                by, but doing it by ascending age essentially requires you to
                re-sort the list, which can be difficult to write). 


    Contributions:
    --------------
    Camron: sorted insertion
    Evan: list printing
    Lavender: file setup, structs, and creation/deletion
    Teddy: user interface/input
*/



//                    -------- include statements --------
//MARK: includes
#include <cstdio>
#include <cstdlib>
#include <cstring>



//                        -------- prototypes --------
//MARK: prototypes
// Structs (lavender)
struct Node;
struct Record;

// list creation (lavender)
Node* new_list(Node*);

// list deletion (lavender)
Node* delete_list(Node*);
Node* delete_node(Node*, char*, int);

// record insertion (camron)
Node* insert_record(Node*, char*, int);

// list printing (evan)
void print_list(Node*);

// ui (teddy)
void program_loop();



//                           -------- main --------
//MARK: main()
int main() {

}



//                      -------- implementations --------
//MARK: structs
// linked list node
struct Node {
    Record* data;
    Node* next;
};

// record: container for information
/*
    contains a first name (char*),
    contains an age (int)
*/
struct Record {
    char* name;
    int age;
};

// create a new list, given name and age
//MARK: new_list()
Node* new_list(Node* list, int age, char* name) {

    // make sure the list isn't already defined
    if(list != nullptr) {
        puts("List already exists.");
        return list;
    }

    // otherwise, allocate memory for all pieces of data
    Node* new_list = (Node*) malloc(sizeof(Node));
    new_list->data = (Record*) malloc(sizeof(Record));
    new_list->data->name = (char*) malloc(16 * sizeof(char));
    
    // no need to allocate memory for new_list->next, since if it points to
    // a Node, it will already have itself allocated

    // initialize the first node's record with information
    new_list->data->name = name;
    new_list->data->age = age;

    return new_list;
}

// delete the entirety of a list
//MARK: delete_list()
Node* delete_list(Node* list) {

    // make sure there is a list to delete
    if(list == nullptr) {
        puts("No list exists.");
        return list;
    }

    // pointer to traverse the list
    Node* curr_node = list;
    Node* next = nullptr;

    while(curr_node != nullptr) {

        // keep track of the next node
        // (we need to free curr_node, but then we can't access the next node)
        next = curr_node->next;
        
        // free all the allocated data
        // (one `free` for each `malloc` we created each node with)
        free(curr_node->data->name);
        free(curr_node->data);
        free(curr_node);

        // make sure the pointers aren't pointing to any freed memory
        curr_node->data->name = nullptr;
        curr_node->data = nullptr;

        // set the current node to the next node and continue
        // (in the final iteration, `next` will be a nullptr and
        //  so `curr_node` will be set to nullptr, breaking the loop)
        curr_node = next;
    }

    // finally, now that all the nodes in the list
    // have been freed, we can reset the address in `list`,
    list = nullptr;

    // and return it
    return list;
}

// delete a specific node from the list
/*
    must pass the exact age and name of the record to delete
*/
//MARK: delete_node()
Node* delete_node(Node* list, int age, char* name) {

    // make sure the list exists first
    if(list == nullptr) {
        puts("No list exists.");
        return list;
    }

    // node pointers to traverse the list
    Node* curr_node = list;
    Node* prev_node = nullptr;

    // loop through the nodes, looking for the exact match
    while(curr_node != nullptr) {

        // found a matching node
        if(curr_node->data->age == age && curr_node->data->name == name) {

            // 2 cases: node to delete is the head, or it is a body (or tail)

            // case 1: node is head
            if(prev_node == nullptr) {
                // set prev_node to the current node (to free the memory),
                // and set curr_node to the next node (to return as the new list head)
                prev_node = curr_node;
                curr_node = curr_node->next;

                // free the memory
                free(prev_node->data->name);
                free(prev_node->data);
                free(prev_node);

                // set the freed pointers to nullptr
                prev_node->data->name = nullptr;
                prev_node->data = nullptr;
                prev_node = nullptr;

                // since `list` was the previous node, it should also
                // be set to nullptr 
                list = nullptr;

                // finally, return the new list head
                return curr_node;
            }

            // case 2: node is body (or tail)
            // (no need for `else` since we return in the if case)

            // remove the node to delete by setting its previous->next to its own next
            prev_node->next = curr_node->next;

            // then free all the allocated memory from the node
            free(curr_node->data->name);
            free(curr_node->data);
            free(curr_node);

            // set the freed pointers to nullptr
            curr_node->data->name = nullptr;
            curr_node->data = nullptr;
            curr_node = nullptr;

            // return the list head
            return list;
        }

        // curr_node is not the node we want to delete; keep searching
        prev_node = curr_node;
        curr_node = curr_node->next;
    }

    // if we made it here, then none of the nodes match the name and age
    printf("Node with name %s and age %d not found.\n", name, age);
    return list;
}