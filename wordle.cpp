#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <time.h>
#include <algorithm>
#include "colormod.h"

using namespace std;

int main() {

    //Opening and storing file into vector
    vector<string> words;
    ifstream infile; 
    infile.open("5_letter_words.txt", ios::in); 
    if (infile.is_open()) {
        string temp; 
        while (infile >> temp) {
            words.push_back(temp);
        }
    }

    //generate random word from list
    srand(time(0));
    int random = rand() % words.size();
    string goal = words[random];

    Color::Modifier green(Color::FG_GREEN);
    Color::Modifier def(Color::FG_DEFAULT);
    Color::Modifier red(Color::FG_RED);

    //now we begin our game loop
    bool has_guessed_word = false;
    int num_tries = 0; 
    string guess;
    vector<char> right_pos_letters; 
    vector<char> in_word_letters; 
    while (!has_guessed_word && num_tries != 6) {
        cout << "Guess #" << num_tries + 1 << ": ";
        cin >> guess; 

        if (guess.size() != 5) {
            cout << "The wordle is only 5 letters... dumbass" << endl;
            continue;
        } else if (!(find(words.begin(), words.end(), guess) != words.end())) {
            cout << "Not a valid 5 letter word (could just be not in database)" << endl;
            continue;
        } else {
            //first see if they got word right
            if (guess.compare(goal) == 0){
                cout << green << guess << def << endl;
                has_guessed_word = true;
                continue;
            }

            //now have to iterate over word
            for (int i = 0; i < 6; i++) {
                if (guess[i] == goal[i]) {
                    cout << green << guess[i];
                    right_pos_letters.push_back(guess[i]);
                } else if (goal.find(guess[i]) != string::npos && 
                    (!(find(right_pos_letters.begin(), right_pos_letters.end(), guess[i]) != right_pos_letters.end())) &&
                    !(find(in_word_letters.begin(), in_word_letters.end(), guess[i]) != in_word_letters.end())) {
                    cout << red << guess[i]; 
                    in_word_letters.push_back(guess[i]);
                }
                else cout << def << guess[i];
            }
            cout << def << endl;
            in_word_letters.clear();
            num_tries++;
        }
    }

    if (has_guessed_word) cout << "Congratulations!!!!!" << endl;
    else cout << "The corect word was: " << goal << endl;
    return 1; 
}