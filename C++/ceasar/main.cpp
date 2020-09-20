#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>
#include <fstream>
#include "cipher.h"

// UPDATE FOR USER CLASS OBJECTS 8/4/2020

/*
Try to add a read file functionality - 10/19/2019 - Completed - 10/22/2019
Try to add a decrypt function - 10/22/2019
No bugs found as of 10/22/2019
Edge case: what if user input file name is not found in directory?
    Answer: Just doesn't print anything.
Edge case: What if user inputs 0 or negative number for shift value?
    Answer: Copies the original message just lowercases everything (for 0 input).
            For negative numbers it works except if you shift 'a' by -1 --> ' '
*/

using namespace std;

// GLOBAL VARIABLES
cipher enc; // create class object to access public member functions
int shft; // shift variable
string filename;

string lower_case(string txt) { // change word into lowercase
    transform(txt.begin(), txt.end(), txt.begin(),
    [](unsigned char c){ return tolower(c); });
    return txt;
}

void valid_shift() {
    cout << "Please enter the number that you'd like to shift by." << endl; // figure out how to hide user input
    cin >> shft; // pass to shft variable
    while (!cin) {
        cout << "Your input is not an integer." << endl; // keep looping until input is integer
        cin.clear();
        cin.ignore();
        cin >> shft;
    }
    if (cin) {
        enc.set_shift_value(shft); // pass value to shift member
        //cout << "Shift Value: " << enc.get_shift_value() << endl;
    }
}

void print_file_text(string fname) {
    //cout << "Original Message: " << endl;
    filename = fname; // pass to global variable for use in display_encryption()/main
    string line;
    fstream file;
    file.open(fname.c_str()); // open file of with same name as string
    while (getline(file, line)) { //grab every line in text file
        cout << line << endl;
    }
    file.close();
}

void encryption() {
    //cout << "\nEncrypted Message: " << endl;
    ofstream cipher;
    cipher.open ("cipher.txt");
    string line;
    fstream file;
    file.open(filename.c_str());
    string c_line;
    while (getline(file, line)) {
        line = lower_case(line); // lower case the line so characters are searchable in alphabet
        c_line = enc.encrypt_file_txt(line); // encrypt line
        //cout << c_line << endl; // print encoded line
        cipher << c_line << endl;
    }
    file.close();
    cout << "\nEncryption Complete.";
}

int main() {
    cout << "Please enter the name of the file you are trying to encrypt." << endl;
    cin >> filename;

    valid_shift(); // Makes sure input is an integer
    //print_file_text(filename); // Original message
    encryption(); // encrypted message
    return 0;
}