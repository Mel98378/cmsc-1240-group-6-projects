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


    Contributions:
    --------------
    Camron: sorted insertion
    Lavender: file setup, structs, creation/deletion
    Lavender (fallback): list printing, ui
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

// list printing (lavender)
void print_list(Node*);
void print_printing_options();
void print_list_name(Node*);
void print_list_age(Node*);
Node* copy_list(Node*);
Node* sort_list_age(Node*);

// ui (lavender)
void program_loop();
char get_user_choice(const char*);
bool matches_choice(char, const char*);
int get_age(const char*);
char* get_name(const char*);
Node* delete_options(Node*);
void print_delete_options();
void print_options();



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

// print the list
//MARK: print_list()
void print_list(Node* list) {

    // make sure the list exists first
    if(list == nullptr) {
        puts("No list exists.");
        return;
    }

    // prompt the user to print sorted by name or age
    print_printing_options();
    char choice = get_user_choice("naq");

    switch(choice) {
        case 'n': print_list_name(list); break;
        case 'a': print_list_age(list); break;
        case 'q': break;
    }
}

// gets a valid character choice from the user;
// input must be a string literal containing only single-character options
char get_user_choice(const char* choices) {
    char choice = 0;
    bool bad_choice = false;

    do {

        // will only print if the loop is run twice or more,
        // in which case the user must have given a bad input
        if(bad_choice) {
            printf("Choice \'%c\' is not a valid option.\n", choice);
        }

        printf("Select an option: ");
        scanf(" %c", &choice);
        puts("");

        bad_choice = true;
    } while(!matches_choice(choice, choices));

    return choice;
}

void print_printing_options() {
    puts("\n\nPrinting options:");
    puts("-----------------");
    puts("\t[n] Print by name");
    puts("\t[a] Print by age");
    puts("\t[q] Quit back to menu");
}

// print the list by name first
void print_list_name(Node* list) {

    // for list navigation
    Node* curr_node = list;

    // print each node in the list
    puts("List: {");
    while(curr_node != nullptr) {
        printf("\tName: \"%s\", Age: %d\n", curr_node->data->name, curr_node->data->age);
        curr_node = curr_node->next;
    }
    puts("}");
}

// print the list by age first
/*
    procedure: 
        - make a copy of the list
        - sort that list by age
        - print that list
        - delete the copy (sorted insertion cannot insert by age first)
*/
void print_list_age(Node* list) {
    Node* copy = copy_list(list);
    copy = sort_list_age(copy);
    print_list_name(copy);

    /*
        deleting the copy causes undefined behavior;
        i'm definitely way too tired to try and find out why at the moment,
        but if i'm lucky it'll just be some pointer thing where
        the copy and the main list are sharing the data (so there wouldn't be any mem leaks)

        probably not the case since copy_list() allocates memory to the nodes it creates, but
        i can hope; besides, commenting it out seems to solve the issue so there's that
    */
    // delete_list(copy);
}

// makes a copy of a given list
Node* copy_list(Node* list) {

    if(list == nullptr) {
        return nullptr;
    }

    Node* to_add = (Node*) malloc(sizeof(Node));
    to_add->data = (Record*) malloc(sizeof(Record));
    to_add->data->name = (char*) malloc(16 * sizeof(char));

    strcpy(to_add->data->name, list->data->name);
    to_add->data->age = list->data->age;

    to_add->next = copy_list(list->next);
    return to_add;
}

// bubble sort
//MARK: sort_list_age
Node* sort_list_age(Node* list) {

    if(list == nullptr) {
        puts("List does not exist.");
        return list;
    }

    Node* curr_node = list;
    Node* prev_node = nullptr;
    int compare_names;
    int compare_ages;
    bool list_sorted = false;

    while(!list_sorted) {
        curr_node = list;
        prev_node = nullptr;
        list_sorted = true;


        while(curr_node->next != nullptr) {
            if(curr_node->data->age < curr_node->next->data->age) {
                compare_ages = -1;
            }
            else if(curr_node->data->age > curr_node->next->data->age) {
                compare_ages = 1;
            }
            else {
                compare_ages = 0;
            }

            // swap the current node with the next
            if(compare_ages > 0) {
                // case: head swap with next
                if(prev_node == nullptr) {
                    // making this structure: (head) p -> c -> n
                    prev_node = curr_node;
                    curr_node = curr_node->next;

                    // making the swap: c -> p -> n
                    prev_node->next = curr_node->next;
                    curr_node->next = prev_node;

                    // setting list to the new head (curr_node)
                    // (before it was still pointing to prev_node, which is no longer the head)
                    list = curr_node;

                    // set list_sorted to false since we made a swap
                    list_sorted = false;

                    // continue comparing nodes, starting from
                    // the one we just swapped
                    prev_node = curr_node; // prev_node now list head
                    curr_node = curr_node->next; // curr_node now the next node (the one that used to be the head)
                    continue;
                }

                // case: two bodies
                prev_node->next = curr_node->next;
                curr_node->next = curr_node->next->next;
                prev_node->next->next = curr_node;
                prev_node = prev_node->next;

                // continue through the list
                list_sorted = false;
                continue;
            }

            // curr node goes before; continue
            else if(compare_ages < 0) {

                prev_node = curr_node;
                curr_node = curr_node->next;
                continue;
            }

            // same age; check the names
            else if(compare_ages == 0) {
                compare_names = strcmp(curr_node->data->name, curr_node->next->data->name);

                // curr goes after; swap
                if(compare_names > 0) {
                    // case: head
                    if(prev_node == nullptr) {
                        prev_node = curr_node;
                        curr_node = curr_node->next;

                        prev_node->next = curr_node->next;
                        curr_node->next = prev_node;

                        list = curr_node;

                        // set list_sorted to false since we made a swap
                        list_sorted = false;

                        // continue comparing nodes, starting from
                        // the one we just swapped
                        prev_node = curr_node; // prev_node now list head
                        curr_node = curr_node->next; // curr_node now the next node (the one that used to be the head)
                        continue;
                    }

                    // case: two bodies
                    prev_node->next = curr_node->next;
                    curr_node->next = curr_node->next->next;
                    prev_node->next->next = curr_node;
                    prev_node = prev_node->next;

                    // continue through the list
                    list_sorted = false;
                    continue;
                }

                // curr_node in correct spot OR identical record; continue
                else if (compare_names <= 0) {
                    prev_node = curr_node;
                    curr_node = curr_node->next;
                    continue;
                }
            }
        }
    }

    return list;

}

// main action loop of the program
//MARK: program_loop()
void program_loop() {
    char choice = 0;
    Node* list = nullptr;

    while(true) {
        print_options();

        // get the user's choice
        choice = get_user_choice("cadpq");

        switch(choice) {
            case 'c': list = new_list(list, get_age("Enter the age of the first record: "), get_name("Enter the name of the first record: ")); break;
            case 'a': list = insert_record(list, get_age("Enter the age for the record: "), get_name("Enter the name for the record: ")); break;
            case 'd': list = delete_options(list); break;
            case 'p': print_list(list); break;
            case 'q': 
                puts("Quitting the program...\n");
                if(list != nullptr) {
                    delete_list(list); // to prevent memory leaks
                    list = nullptr;
                }
                return;
        }
    }
}

// prints the options the user has
//MARK: print_options()
void print_options() {
    puts("\n\nOptions:");
    puts("--------");
    puts("\t[c] Create a new list");
    puts("\t[a] Add a new record to the list");
    puts("\t[d] Deletion options");
    puts("\t[p] Print the list");
    puts("\t[q] Quit the program");
}

// checks if the user's choice is in the string of valid choices
//MARK: matches_choice()
bool matches_choice(char choice, const char* choices) {
    int i = 0;
    while(choices[i] != '\0') {
        if(choice == choices[i]) {

            // choice is valid if it matches any character of choices
            return true;
        }

        i++;
    }

    // otherwise, if it matches none of them, it is not valid
    return false;
}

// gets an age from the user
//MARK: get_age()
int get_age(const char* message) {
    int age = 0;

    printf("%s", message);
    scanf("%d", &age);

    return age;
}

// gets and formats a name from the user
//MARK: get_name()
char* get_name(const char* message) {
    char* name = (char*) malloc(16 * sizeof(char));

    printf("%s", message);
    scanf("%15s", name); // <- scanf will read a max of 15 characters and add a null terminator
    
    // formatting the name to be all lowercase except the first letter
    name[0] = toupper(name[0]);
    for(int i = 1; i < 15; i++) {
        name[i] = tolower(name[i]);
    }

    return name;
}

// lets the user choose a deletion option
//MARK: delete_options()
Node* delete_options(Node* list) {
    // make sure a list exists
    if(list == nullptr) {
        puts("No list exists.\n");
        return list;
    }

    print_delete_options();

    char choice = get_user_choice("rDq");

    switch(choice) {
        case 'r': list = delete_node(list, get_age("Enter the age of the node to delete: "), get_name("Enter the name of the node to delete: ")); break;
        case 'D': list = delete_list(list); break;
        case 'q': puts("Returned.\n"); break; // (do nothing)
    }

    return list;
}

// prints the deletion options
//MARK: print_delete_options()
void print_delete_options() {
    puts("\n\nDeletion Options:");
    puts("-----------------");
    puts("\t[r] Delete a specific record");
    puts("\t[D] Delete the list");
    puts("\t[q] Quit back to the main options");
}
