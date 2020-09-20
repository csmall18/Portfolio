// Created by cdsgu on 10/17/2019.
#ifndef CAESAR_CIPHER_H
#define CAESAR_CIPHER_H
#include <string>
using namespace std;

class user {
public:
private:
    string email;
    string username;
    string password;
};

class cipher {
private:
    int shift;
    string curr_line;
    string enc_line;
    char lower_alpha[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m',
                            'n','o','p','q','r','s','t','u','v','w','x','y','z'};
public:
    void set_shift_value(int num) {
        shift = num;
    }
    //int get_shift_value () {return shift;} // for debugging
    void set_curr_line (string l) {
        curr_line = l;
    }

    string encrypt_file_txt(string line) { // possibly make private?
        curr_line = line; // make a copy of original message
        for (int i = 0; i < curr_line.length(); ++i) {
            for (int k = 0; k < 26;++k) {
                if (line[i] == lower_alpha[k])
                    curr_line[i] = lower_alpha[((k + shift)%26)];
            }
        }
        enc_line = curr_line; // assign to encoded message member
        return enc_line;
    }

};

#endif //CAESAR_CIPHER_H
