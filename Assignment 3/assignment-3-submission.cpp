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
    (lavender): for the sorting part, after some messing around i think that
                the best option is to keep the list sorted by name, and
                basically reverse bubble sort the list if the user wants to
                print the list by age, keeping the main list still by age

    (lavender): for user input, there are a few things to keep in mind;
                the main thing is that for names, make sure that the name
                is no longer than 15 characters + 1 null terminator long, 
                and make sure that all ith characters between names are the
                same case (i suggest having the first letter uppercase and 
                the rest lowercase)


    Contributions:
    --------------
    Camron: sorted insertion
    Evan: list printing
    Lavender: file setup, structs, creation/deletion
    Teddy: user interface
*/



//                    -------- include statements --------
//MARK: includes
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>



//                        -------- prototypes --------
//MARK: prototypes
// Structs (lavender)
struct Node;
struct Record;

// list creation (lavender)
Node* new_list(Node*, int, char*);

// list deletion (lavender)
Node* delete_list(Node*);
Node* delete_node(Node*, int, char*);

// record insertion (camron)
Node* insert_record(Node*, int, char*);

// list printing (evan)
void print_list(Node*);

// ui (teddy)
void program_loop();


//                           -------- main --------
//MARK: main()
int main() {
    program_loop();
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
    new_list->next = nullptr;

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

//MARK: insert_record()
Node* insert_record(Node* list, int age, char* name) {
    
    // New node for the record to be inserted
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = (Record*) malloc(sizeof(Record));
    new_node->data->name = (char*) malloc(16 * sizeof(char));
    new_node->next = nullptr;
    
    // Initilaize
    new_node->data->name = name;
    new_node->data->age = age;
    
    // If list is empty or if the new record should be inserted at the beginning
    if (list == nullptr || strcmp(name, list->data->name) < 0) {
        new_node->next = list;
        return new_node;
    }
    
    // Goes through list to find correct placement
    Node* current = list;
    while (current->next != nullptr && strcmp(name, current->next->data->name) > 0) {
        current = current->next;
    }
    
    // Insert the new record
    new_node->next = current->next;
    current->next = new_node;
    
    return list;
}
//*** teddy ***//
// User Interface implementation
void program_loop() {
    Node* list = nullptr; // Start with no list
    char option;
    char name[16];
    int age;

    while (true) {
        // Display options to the user
        puts("\nMenu:");
        puts("1. Add Record");
        puts("2. Delete Record");
        puts("3. Print List");
        puts("4. Exit");
        printf("Select an option: ");
        scanf(" %c", &option); // Read user input

        switch (option) {
            case '1': // Add a new record
                printf("Enter name: ");
                scanf("%15s", name); // Limit input to 15 characters for safety
                printf("Enter age: ");
                scanf("%d", &age);
                list = insert_record(list, age, name);
                puts("Record added.");
                break;

            case '2': // Delete a record
                printf("Enter name of the record to delete: ");
                scanf("%15s", name);
                printf("Enter age of the record to delete: ");
                scanf("%d", &age);
                list = delete_node(list, age, name);
                puts("Record deleted (if found).");
                break;

            case '3': // Print all records
                print_list(list);
                break;

            case '4': // Exit the program
                list = delete_list(list); // Clean up all nodes
                puts("Exiting program.");
                return; // Exit the program loop

            default:
                puts("Invalid option. Please try again.");
        }
    }
}

// Function to print all records in the list
void print_list(Node* list) {
    Node* current = list;
    if (current == nullptr) {
        puts("List is empty.");
    } else {
        puts("List of Records:");
        while (current != nullptr) {
            printf("Name: %s, Age: %d\n", current->data->name, current->data->age);
            current = current->next;
        }
    }
}
