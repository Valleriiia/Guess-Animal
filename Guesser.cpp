#include "Guesser.h"

bool Guesser::guess(const string& animal, Language lang) {
    if (lang == ukr) {
        cout << "\nВаше припущення: ";
    } else {
        cout << "\nYour guess: ";
    }
    string guess;
    getline(cin, guess);

    userInput::stringToLower(guess);
    string animLow = animal;
    userInput::stringToLower(animLow);

    if (guess == animLow) {
        if (lang == ukr) {
            cout << "\nВітаю! Ви вгадали тварину: " << animal << "!" << endl;
        } else {
            cout << "\nCongratulations! You guessed the animal: " << animal << "!" << endl;
        }
        return true; 
    } else {
        if (lang == ukr) {
            cout << "\nНеправильно." << endl;
        } else {
            cout << "\nIncorrect." << endl;
        }
        return false; 
    }
}