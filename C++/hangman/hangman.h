#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cctype>
#pragma once

using namespace std;
int inc = 0;
class hangman {
private:
    string wrd;
    const char* wrd_ptr;
    bool valid;
    bool match;
    char guess;
    vector<int> indexes;
    char alpha[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m',
                      'n','o','p','q','r','s','t','u','v','w','x','y','z'}; // may potentially need

public:
    vector<char> bank;
    string WordToGuess() {
        cout << "Please enter the word that you want for the game." << endl;
        cin >> wrd;
        return wrd;
    }

    const char* stringToCharArray(string wrd) {
        wrd_ptr = wrd.c_str();
        return wrd_ptr;
    }

    string getWord() {
        return this->wrd;
    }

    const char* getWordPtr() { // returns ptr to word char array
        return this->wrd_ptr;
    }

    char getGuess() {
        return this->guess;
    }

    void PrintBank() {
        for (int i = 0;i < bank.size();++i) {
            cout << bank[i];
        }
        cout << endl;
    }

    void word_bank() { // allows user to see correct letters they've guessed
        for (int i = 0;i < wrd.length();++i) {
            bank.push_back('*');
            //cout << bank[i];
        }
        cout << endl;
    }

    void UpdateBank(const char l) {
        for (int i = 0;i < wrd.size();++i) {
            if (l == wrd_ptr[i])
                bank[i] = l;
        }
        for (int i = 0; i < indexes.size();++i)
            indexes.pop_back(); // reset index vector
    }

    bool valid_guess() {
        valid = false;
        cout << "Please input the letter you wish to guess in lower case." << endl;
        cin >> guess;
        while (!cin) {
            cout << "Your input is not a letter. Try again." << endl; // keep looping until input is integer
            cin.clear();
            cin.ignore();
            cin >> guess;
        }
        if (cin) {
            valid = true;
            return valid;
        }
    }

    bool check_guess(char g) { // check if letter is in word
            match = false;
            for (int i = 0; i < wrd.size(); ++i)
                for (int i = 0; i < wrd.size(); ++i) {
                    if (wrd_ptr[i] == g) {
                        match = true;
                        indexes.push_back(i); // store all indexes where matching letters are
                    }
                }

            if (match == false) {
                cout << "Your guess is incorrect." << endl;
                return match;
            } else if (match == true) {
                cout << "Your guess is correct!" << endl;
                return match;
            }
    }

    void SetupHangMan() {
        switch (inc) {
            case 0:
            cout << endl;
            cout << "     _______" << endl;
            cout << "    |       |" << endl;
            cout << "    |" << endl;
            cout << "    |" << endl;
            cout << "    |" << endl;
            cout << "    |" << endl;
            cout << "    |" << endl;
            cout << "    |" << endl;
            cout << "    |" << endl;
            cout << "    |" << endl;
            cout << "---- ----" << endl;
            break;
            case 1:
                cout << endl;
                cout << "     _______" << endl;
                cout << "    |       |" << endl;
                cout << "    |       O" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "---- ----" << endl;
                break;
            case 2:
                cout << endl;
                cout << "     _______" << endl;
                cout << "    |       |" << endl;
                cout << "    |       O" << endl;
                cout << "    |       |" << endl;
                cout << "    |       |" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "---- ----" << endl;
                break;
            case 3:
                cout << endl;
                cout << "     _______" << endl;
                cout << "    |       |" << endl;
                cout << "    |       O" << endl;
                cout << "    |     \\ |" << endl;
                cout << "    |       |" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "---- ----" << endl;
                break;
            case 4:
                cout << endl;
                cout << "     _______" << endl;
                cout << "    |       |" << endl;
                cout << "    |       O" << endl;
                cout << "    |     \\ | /" << endl;
                cout << "    |       |" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "---- ----" << endl;
                break;
            case 5:
                cout << endl;
                cout << "     _______" << endl;
                cout << "    |       |" << endl;
                cout << "    |       O" << endl;
                cout << "    |     \\ | /" << endl;
                cout << "    |       |" << endl;
                cout << "    |      /" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "---- ----" << endl;
                break;
            case 6:
                cout << endl;
                cout << "     _______" << endl;
                cout << "    |       |" << endl;
                cout << "    |       O" << endl;
                cout << "    |     \\ | /" << endl;
                cout << "    |       |" << endl;
                cout << "    |      / \\" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "    |" << endl;
                cout << "---- ----" << endl;
                break;
        }
        inc = (inc+1)%7;
    }
};
