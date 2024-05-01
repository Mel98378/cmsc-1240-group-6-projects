#include <uni.cpp>
#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;

/*** get_menu_choice Function ***/
char get_menu_choice(const char* valid_choices) {
    char input;
    do {
        cout << "Enter your choice (" << valid_choices << "): ";
        cin >> input;
        // Check if input is in the valid choices string
    } while (strchr(valid_choices, input) == NULL);  // Keep asking until a valid choice is made
    return input;
}

/*** get_user_name Function ***/
char* get_user_name() {
    char* name = new char[16]; // Allocate memory for 16 characters (15 + null terminator)
    cout << "Enter your name (max 15 characters): ";
    cin.getline(name, 16); // Reads up to 15 characters or until newline
    return name;
}

/*** wait_until_key Function ***/
void wait_until_key() {
#ifdef __APPLE__
    std::cout << "Press any key to continue...";
    system("read -n 1 -s"); // macOS-specific system call
#elif _WIN32
    std::cout << "Press any key to continue...";
    system("pause>nul"); // Windows-specific system call
#endif
}






