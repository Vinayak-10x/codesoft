#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));                        // random seed
    int secret = rand() % 100 + 1;        // number between 1-100
    int guess, attempts = 0;

    cout << "=== Number Guessing Game ===\n";
    cout << "Guess the number (1-100)\n\n";

    while (true) {
        cout << "Enter guess: ";
        cin >> guess;
        attempts++;

        if (guess < secret)
            cout << "Too LOW!\n";
        else if (guess > secret)
            cout << "Too HIGH!\n";
        else {
            cout << "\nCorrect! The number was " << secret << "!\n";
            cout << "You got it in " << attempts << " attempts.\n";
            break;
        }
    }

    return 0;
}