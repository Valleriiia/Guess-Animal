#include "Guesser.h"

// Обробляє припущення користувача
bool Guesser::guess(const string& animal, Language lang) {
    // Просить користувача ввести своє припущення
    if (lang == ukr) {
        cout << "\nВаше припущення: ";
    } else {
        cout << "\nYour guess: ";
    }
    string guess;
    getline(cin, guess);

    // Переводить ввід користувача та зага дану тварину у нижній регістр
    userInput::stringToLower(guess);
    string animLow = animal;
    userInput::stringToLower(animLow);

    // Перевіряє чи припущення користувача збігається з загаданою твариною
    if (guess == animLow) {
        // Виводить відповідь
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