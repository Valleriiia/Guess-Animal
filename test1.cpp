#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

class QuestionAsker {
public:
    void ask(const string& animal, const unordered_map<string, unordered_set<string>>& animals, const unordered_map<string, unordered_set<string>>& keywords, int language) {
        string question;
        if (language == 2) {
            cout << "\nЗадайте своє запитання: ";
        } else {
            cout << "\nAsk your question: ";
        }
        getline(cin, question);

        for (const auto& [key, keys] : keywords) {
            for (const auto& _key : keys) {
                if (strstr(question.c_str(), _key.c_str()) != nullptr) {
                    if (animals.at(animal).count(key) > 0) {
                        if (language == 2) {
                            cout << "\nТак." << endl;
                        } else {
                            cout << "\nYes." << endl;
                        }
                    } else {
                        if (language == 2) {
                            cout << "\nНі." << endl;
                        } else {
                            cout << "\nNo." << endl;
                        }
                    }
                    return;
                }
            }
        }

        if (language == 2) {
            cout << "\nНезрозуміле запитання. Спробуйте знову." << endl;
        } else {
            cout << "\nSorry, I don't understand the question. Please try again." << endl;
        }
    }
};

class Guesser {
public:
    bool guess(const string& animal, int language) {
        if (language == 2) {
            cout << "\nВаше припущення: ";
        } else {
            cout << "\nYour guess: ";
        }
        string guess;
        getline(cin, guess);

        char guessArr[100];
        strcpy(guessArr, guess.c_str());
        for (size_t i = 0; i < strlen(guessArr); i++) {
            guessArr[i] = tolower(guessArr[i]);
        }

        char animalArr[100];
        strcpy(animalArr, animal.c_str());
        for (size_t i = 0; i < strlen(animalArr); i++) {
            animalArr[i] = tolower(animalArr[i]);
        }

        if (strcmp(guessArr, animalArr) == 0) {
            if (language == 2) {
                cout << "\nВітаю! Ви вгадали тварину: " << animal << "!" << endl;
            } else {
                cout << "\nCongratulations! You guessed the animal: " << animal << "!" << endl;
            }
            return true; 
        } else {
            if (language == 2) {
                cout << "\nНеправильно." << endl;
            } else {
                cout << "\nIncorrect." << endl;
            }
            return false; 
        }
    }
};

class AnimalGame {
private:
    unordered_map<string, unordered_set<string>> animals;
    unordered_map<string, unordered_set<string>> keywords;
    int language;

public:
    AnimalGame(int lang) : language(lang) {
        initAnimals();
        initKeywords();
    }

    void play() {
        srand(time(nullptr));
        auto iter = animals.begin();
        advance(iter, rand() % animals.size());
        const string& animal = iter->first;

        if (language == 2) {
            cout << "Комп'ютер загадав тварину. Спробуйте вгадати, яку саме." << endl;
        } else {
            cout << "The computer guessed the animal. Try to guess which animal the computer chose." << endl;
        }

        string input;
        while (true) {
            if (language == 2) {
                cout << "\nЩо ви хочете зробити? (1 - задати запитання, 2 - зробити припущення, 3 - завершити гру): ";
            } else {
                cout << "\nWhat do you want to do? (1 - ask a question, 2 - make a guess, 3 - end the game): ";
            }
            getline(cin, input);

            if (input == "1") {
                QuestionAsker asker;
                asker.ask(animal, animals, keywords, language);
            } else if (input == "2") {
                Guesser guesser;
                bool guessed_correctly = guesser.guess(animal, language);
                if (guessed_correctly) {
                    break; // Виходимо з циклу, якщо вгадано
                }
            } else if (input == "3") {
                if (language == 2) {
                    cout << "\nГра завершена. Дякую за участь!" << endl;
                } else {
                    cout << "\nThe game is over. Thank you for playing!" << endl;
                }
                return;
            } else {
                if (language == 2) {
                    cout << "Неправильний вибір. Введіть 1, щоб задати запитання, 2, щоб зробити припущення, або 3, щоб завершити гру." << endl;
                } else {
                    cout << "Invalid choice. Enter 1 to ask a question, 2 to make a guess, or 3 to end the game." << endl;
                }
            }
        }
    }

private:
    void initAnimals() {
        if (language == 2) {
            animals = {
                {"Тигр", {"хижак", "смугастий", "велика", "гострі зуби", "кігті", "швидка", "ссавець"}},

            };
        } else {
            animals = {
                {"Tiger", {"predator", "striped", "big", "sharp teeth", "claws", "fast", "mammal"}},

            };
        }
    }

    void initKeywords() {
        if (language == 2) {
            keywords = {
                {"хижак", {"хижак", "Хижак", "хижий", "Хижий", "хижа", "Хижа"}},

            };
        } else {
            keywords = {
                {"predator", {"predator", "Predator", "predatory", "Predatory"}},

            };
        }
    }
};


int main() {
    AnimalGame game(2);
    game.play();
    return 0;
}

