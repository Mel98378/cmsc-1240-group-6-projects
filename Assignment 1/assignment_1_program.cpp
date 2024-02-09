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
              choice_from_input(), is_valid_option(), print_choice_error()
    
*/

#include <iostream>
#include <string>
#include <regex>
#include <cmath>
using namespace std;

void binary_log() {
}

void division() {
}

void multiplication() {
    double num1, num2, result;
    
    cout << "You have selected multiplication please enter the first number" << endl;
    cin >> num1;
    cout << "Enter the second number" << endl;
    cin >> num2;
    result = num1 * num2;
    
    cout << num1 << " * " << num2 << " = " << result << endl;
}

void subtraction() {
    double num1, num2, result;
    
    cout << "You have selected subtraction please enter the first number" << endl;
    cin >> num1;
    cout << "Enter the second number" << endl;
    cin >> num2;
    result = num1 - num2;
    
    cout << num1 << " - " << num2 << " = " << result << endl;
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
    cout << "\n----------------" << endl
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

        // only valid input if input matches and if choice is in range
        choice = choice_from_input(input);

        switch (choice) {
            case 0: addition(); break;
            case 1: subtraction(); break;
            case 2: multiplication(); break;
            case 3: division(); break;
            case 4: binary_log(); break;
            case 5: return;
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
