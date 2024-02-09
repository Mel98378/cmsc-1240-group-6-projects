/*
    title: 5 function calculator
    authors: group 6

    program requirements:
        - provide a menu of functions
        - allow the user to choose a function or exit
        - allow users to input values to functions
        - compute each function correctly
        - return to the menu after each function

    list of functions: 
        - addition
        - subtraction
        - multiplication
        - division
        - binary logarithm (log base 2)
*/

/*
    contributions
    ---------------------
    lavender: main(), print_greeting(), program_loop(), print_options(),
              choice_from_input(), is_valid_option(), print_choice_error(),
              binary_log()
    
*/

#include <iostream>
#include <string>
#include <regex>
#include <cmath>
using namespace std;

void binary_log() {
    cout << "\nYou chose Log base 2. " << endl;
    
    string in = "";
    double input = 0;
    regex correct("[0-9]+\.?[0-9]*");
    do {
        cout << "Choose a number to take the binary log of: ";
        cin >> in;

        if(!regex_match(in, correct) || in == "0") {
            cout << "Please choose a positive real number. " << endl;
            continue;
        }

        input = stod(in);

    } while (input <= 0);

    cout << "The binary log of " << input << " is " << log2(input) << ".";
}

void division() {
}

void multiplication() {
}

void subtraction() {
}

void addition() {
}

void print_choice_error(string choice) {
    cout << "Option [" << choice << "] was not found." << endl
         << "Select an option: ";
}

// regex matching for acceptable inputs
bool is_valid_option(string input) {
    regex reg("[0-9]+");
    return regex_match(input, reg);
}

int choice_from_input(string input) {
    int choice = -1;

    while(true) {
        cin >> input;

        if(!is_valid_option(input)) {
            print_choice_error(input);
            continue;
        }
        else choice = stoi(input);

        if(choice < 0 || choice > 5) {
            print_choice_error(input);
            continue;
        }
        else return choice;
    }
}

void print_options() {
    cout << "\n\n----------------" << endl
         << "Available options: " << endl
         << "\t[0]: Addition" << endl
         << "\t[1]: Subtraction" << endl
         << "\t[2]: Multiplication" << endl
         << "\t[3]: Division" << endl
         << "\t[4]: Binary Logarithm" << endl
         << "\t[5]: Quit the program" << endl
         << "Select an option: ";
}

void program_loop() {
    string input;
    int choice = -1;

    while(true) {
        print_options();
        choice = choice_from_input(input);

        switch (choice) {
            case 0: addition(); break;
            case 1: subtraction(); break;
            case 2: multiplication(); break;
            case 3: division(); break;
            case 4: binary_log(); break;
            case 5: cout << "Exiting the program."; return;
            default: cout << "Something has gone wrong." << endl; return;
        }
    }
}

void print_greeting() {
    cout << "\nThis is a calculator with five functions." << endl;
}

int main() {
    print_greeting();
    program_loop();
}
