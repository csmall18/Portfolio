#include <iostream>
using namespace std;

/*
* Updated so that board is updated with character 11/22/2019
* tie() function seems to be fully functional 11/22/2019
*/
//GLOBAL VARIABLES
int turn_player = 1;
char move_options[9] = {'1','2','3','4','5','6','7','8','9'}; // for each spot on the grid
char spots_taken[9] = {'-','-','-','-','-','-','-','-','-'}; // initialized to zeros, will have either 1s or 2s
int spot;
//bool valid_input = false;
int res;
bool winner = false;
int curr_player;
int num_turns = 0;

void grid () {
    cout << "     |     |     " << endl;
    cout << "  " << move_options[0] << "  |  " << move_options[1] << "  |  " << move_options[2] << endl;
    cout << "     |     |     " << endl;
    cout << "-----------------" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << move_options[3] << "  |  " << move_options[4] << "  |  " << move_options[5] << endl;
    cout << "     |     |     " << endl;
    cout << "-----------------" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << move_options[6] << "  |  " << move_options[7] << "  |  " << move_options[8] << endl;
    cout << "     |     |     " << endl;
    cout << endl;
}

int whose_turn() {
    if (turn_player % 2 == 1) {
        res = turn_player % 2;
    }
    if (turn_player % 2 == 0) {
        res = turn_player % 2 + 2; // plus two to get it to equal 2
    }
    cout << "Player " << res << ", make your move." << endl;
    cin >> spot;
    if (!(cin && spot >= 1 && spot <= 9)) {
        cout << "Your input is not valid. Try again." << endl;
        cin.clear();
        cin.ignore();
        cin >> spot;
    }
    if ((cin && spot >= 1 && spot <= 9)) { // if int that is in the range of 1-9
        curr_player = res; // update current player's turn
        ++turn_player; // for modding alternation (turn calculation)
        return res;
    }

}

void update_board() {
    if (curr_player == 1 && spots_taken[spot - 1] == '-')  { // unoccupied spots indicated with '-'
        move_options[spot - 1] = 'X'; // player 1
    }

    if (curr_player == 2 && spots_taken[spot - 1] == '-') {
        move_options[spot - 1] = 'O'; // player 2
    }
}

bool tie () { // check for ties
    if (num_turns == 9 && !winner) // if there's no winner after 9 turns
        return true;
    else
        return false;
}

bool win_condition () {
    // For Player 1
    if ((move_options[0] == 'X') && (move_options[1] == 'X') && (move_options[2] == 'X')) { // horizontal wins
        winner = true;
        return winner;
    }
    if ((move_options[3] == 'X') && (move_options[4] == 'X') && (move_options[5] == 'X')) {
        winner = true;
        return winner;
    }
    if ((move_options[6] == 'X') && (move_options[7] == 'X') && (move_options[8] == 'X')) {
        winner = true;
        return winner;
    }
    if ((move_options[0] == 'X') && (move_options[3] == 'X') && (move_options[6] == 'X')) { // vertical wins
        winner = true;
        return winner;
    }
    if ((move_options[1] == 'X') && (move_options[4] == 'X') && (move_options[7] == 'X')) {
        winner = true;
        return winner;
    }
    if ((move_options[2] == 'X') && (move_options[5] == 'X') && (move_options[8] == 'X')) {
        winner = true;
        return winner;
    }
    if ((move_options[0] == 'X') && (move_options[4] == 'X') && (move_options[8] == 'X')) { // diagonal wins
        winner = true;
        return winner;
    }
    if ((move_options[2] == 'X') && (move_options[4] == 'X') && (move_options[6] == 'X')) {
        winner = true;
        return winner;
    }

    // For Player 2
    if ((move_options[0] == 'O') && (move_options[1] == 'O') && (move_options[2] == 'O')) { // horizontal wins
        winner = true;
        return winner;
    }
    if ((move_options[3] == 'O') && (move_options[4] == 'O') && (move_options[5] == 'O')) {
        winner = true;
        return winner;
    }
    if ((move_options[6] == 'O') && (move_options[7] == 'O') && (move_options[8] == 'O')) {
        winner = true;
        return winner;
    }
    if ((move_options[0] == 'O') && (move_options[3] == 'O') && (move_options[6] == 'O')) { // vertical wins
        winner = true;
        return winner;
    }
    if ((move_options[1] == 'O') && (move_options[4] == 'O') && (move_options[7] == 'O')) {
        winner = true;
        return winner;
    }
    if ((move_options[2] == 'O') && (move_options[5] == 'O') && (move_options[8] == 'O')) {
        winner = true;
        return winner;
    }
    if ((move_options[0] == 'O') && (move_options[4] == 'O') && (move_options[8] == 'O')) { // diagonal wins
        winner = true;
        return winner;
    }
    if ((move_options[2] == 'O') && (move_options[4] == 'O') && (move_options[6] == 'O')) {
        winner = true;
        return winner;
    }
    return winner;
}

void start_game () {
    while ((!winner && !tie())) { // while there's no winner or tie, continue game
        grid();
        whose_turn();
        ++num_turns;
        update_board();
        win_condition();
        tie();
    }
    if (winner) {
        grid();
        cout << "Player " << curr_player << " wins!!!" << endl;
    }
    if (tie()) {
        cout << "Draw!";
    }
}

int main() {
    cout << "Tic-Tac-Toe!" << endl;
    cout << "To pick a spot select a spot, input a number 1 - 9." << endl;
    cout << "The first row corresponds to values 1, 2, and 3 from left to right." << endl;
    cout << "The other rows follow the same pattern." << endl;
    cout << "Player 1 is X, and Player 2 is O." << endl;
    start_game();
    return 0;
}