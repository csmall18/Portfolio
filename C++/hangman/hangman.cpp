#include "hangman.h"
#include <iostream>

using namespace std;

/*
Issues to fix:
- Guessing same incorrect letter twice counts twice as wrong (or leave as a punishment)
- Guessing incorrect word does not result in punishment (fixed)
*/

hangman game;
int ctr;
int k = 0;
char letters_guessed[6] = {'-','-','-','-','-','-'};
char gs;
bool valid = false;
bool match = false;
bool ag = false;
string wrd = game.WordToGuess();
char * lg = letters_guessed;
bool resp = false;

bool CheckIfGuessed(char let) {
    bool guessed =  false;
    for (int i = 0;i < 6;++i) {
        if (letters_guessed[i] == let) {
            guessed = true;
            cout << "You already guessed " << let << ". Try another letter." << endl;
            for (int i = 0;i < 6;++i)
                cout << lg[i] << " ";
            cout << endl;
            return guessed;
        }
    }
    return guessed; // user has not guessed letter
}

bool CheckIfWon() {
    bool win[wrd.length()];
    for (int i = 0; i < wrd.length();++i)
        win[i] = game.bank[i] == game.getWordPtr()[i]; // should all be 1s if win condition is met
    
    bool w = win[0];
    for(int i = 1;i < wrd.length();++i)
        w = w && win[i]; // w should remain true if all of win is true;
    if (w) {
        cout << "You win!" << endl;
        return true;
    }
    else {
        w = false;
        return w;
    }
}

bool CheckIfLost() {
    if (letters_guessed[5] != '-' || ctr == 6) { // if guessed letters is filled you lose
        cout << "You lost..." << endl;
        cout << "The word was: " << game.getWord() << endl;
        return true;
    }
    else
        return false;
}

bool make_guess() {
    char letter;
    cout << "Would you like to guess a word? [y/n]" << endl;
    cin >> letter;
    while (!cin.fail() && letter!='y' && letter!='n') {
        cout << "Your input is not valid. Try again." << endl; // keep looping until input is integer
        cin.clear();
        cin.ignore();
        cin >> letter;
    }
    if (letter == 'y') {
        resp = true;
        return resp;
    }

    if (letter == 'n') {
        resp = false;
        return resp;
    }
}

bool CheckWordGuess() {
    if (resp) {
        string wordguess;
        cout << "What is your guess for the word?" << endl;
        cin >> wordguess;
        if (game.getWord().compare(wordguess) == 0) {
            cout << "You are correct!!!" << endl; // compare both words
            cout << game.getWord() << " was the mystery word!" << endl;
            return true;
        }
        if (game.getWord().compare(wordguess) != 0) {
            cout << "You are incorrect..." << endl;
            game.SetupHangMan(); //incorrect word guess is punished
            game.PrintBank();
            ctr++; // count down to loss
            return false;
        }
    }
}

void hangman_game() {
while (!CheckIfWon()) {
    
    while (!valid) {
        valid = game.valid_guess(); // keep checking if guess is valid
        if (valid) {
            gs = game.getGuess();
            ag = CheckIfGuessed(gs); // keep checking if already guessed
        }
        if (!ag)
            break;
    }
    if (valid)
        match = game.check_guess(gs); // check if guess is right or wrong

    if (!match) {
        if (valid) {
            letters_guessed[k] = gs;
            ++k;
            game.SetupHangMan(); // updated hanged man
            ctr++; // count down to loss
            valid = false; // reset valid
        }
        cout << "Incorrect guesses: [";
        for (int i = 0;i < sizeof(letters_guessed);++i) {
            if (i < 5) 
                cout << lg[i] <<",";
            else
                cout << lg[i] << "]" << endl;
        }
        cout << "Mystery Word: ";
        game.PrintBank();
    }
    else if (match) {
        game.UpdateBank(gs); // insert letter in letter bank
        cout << "Mystery Word: ";
        game.PrintBank(); // show new letter bank
        valid = false; // reset valid

        cout << "Incorrect guesses: [";
        for (int i = 0;i < sizeof(letters_guessed);++i) {
            if (i < 5) 
                cout << lg[i] <<",";
            else
                cout << lg[i] << "]" << endl;
        }
    }

    if (make_guess()) { //if word guess is correct, end game
        if (CheckWordGuess())
            break;
    }

    if (CheckIfLost()) { //if they run out of guess or get  word correct
        break;
    }

}

}

int main() {
    game.stringToCharArray(wrd); // convert string to char array
    game.SetupHangMan();
    game.word_bank(); // make letter bank
    game.PrintBank(); // ^ all setup for game
    hangman_game(); //start game
    return 0;
}