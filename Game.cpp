#include "Game.h"
#include "thinkingGame.h"
#include "GuessingGame.h"

void Game::setLanguage() {
    cout  << ((lang == ukr) ? "\nМова" : "\nLanguage") << endl << endl;
    cout << "1. English" << endl;
    cout << "2. Українська" << endl << endl;
    cout << ((lang == ukr) ? "Ваш вибір: " : "Your  choice: ");
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
        lang = Language::eng;
        break;

    case 2:
        lang = Language::ukr;
        break;
    
    default:
        cout << ((lang == ukr) ? "Неправельне введення! Спробуйте ще раз" : "Incorrect number! Try again") << endl;
        setLanguage();
    }
}

void Game::menu() {
    cout << ((lang == ukr) ? "\nГра \"Тварини\"" : "\nGame \"Animals\"") << endl << endl;
    cout << ((lang == ukr) ? "Меню:" : "Menu:") << endl;
    cout << ((lang == ukr) ? "1. Загадай тварину" : "1. Think about an animal") << endl;
    cout << ((lang == ukr) ? "2. Відгадай тварину" : "2. Guess the animal") << endl;
    cout << ((lang == ukr) ? "3. Мова (Language)" : "3. Language") << endl;
    cout << ((lang == ukr) ? "4. Правила" : "4. Rules") << endl;
    cout << ((lang == ukr) ? "5. Вихід" : "5. Exit") << endl;
    cout << ((lang == ukr) ? "Введіть номер з меню: " : "Enter the number from the menu: ");
    int choice;
    cin >> choice;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(32767, '\n');
        cout << ((lang == ukr) ? "Помилка введення! Спробуйте ще раз" : "Invalid input! Try again") << endl;
        return;
    }
    cin.ignore();
    thinkingGame tgame(lang);
    GuessingGame ggame(lang);
    switch (choice) {
        case 1:
            tgame.play();
            break;

        case 2:
            ggame.play();
            break;

        case 3:
            setLanguage();
            break;

        case 4:
            files.setFilename((lang == ukr) ? "rules_ukr.txt" : "rules_eng.txt");
            files.readAndPrintText();
            break;
        
        case 5:
            exit(0);
        
        default:
            cout << ((lang == ukr) ? "Неправельне введення! Спробуйте ще раз" : "Invalid input. Try again.") << endl;
            return;
    }                                        
}