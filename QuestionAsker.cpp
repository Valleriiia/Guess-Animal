#include "QuestionAsker.h"
#include <cstring>

// Обробляє питання користувача
void QuestionAsker::ask(const string& animal, const unordered_map<string, unordered_set<string>>& animals, const unordered_map<string, unordered_set<string>>& keywords, Language lang) {
    string question;

    // Просить користувача ввести питання
    if (lang == ukr) {
        cout << "\nПоставте своє запитання: ";
    } else {
        cout << "\nAsk your question: ";
    }
    getline(cin, question);

    // Перебирає ключові слова та перевіряє, чи містить запитання будь-яке з них
    for (const auto& [key, keys] : keywords) {
        for (const auto& _key : keys) {
            if (strstr(question.c_str(), _key.c_str()) != nullptr) {
                // Перевіряє, чи пов’язана тварина з ключовим словом
                if (animals.at(animal).count(key) > 0) {
                    // Виводить відповідь на питання
                    if (lang == ukr) {
                        cout << "\nТак." << endl;
                    } else {
                        cout << "\nYes." << endl;
                    }
                } else {
                    if (lang == ukr) {
                        cout << "\nНі." << endl;
                    } else {
                        cout << "\nNo." << endl;
                    }
                }
                return;
            }
        }
    }

    // Якщо ключове слово не знайдено, виводить повідомлення про те, що не розуміє питання
    if (lang == ukr) {
        cout << "\nНезрозуміле запитання. Спробуйте знову." << endl;
    } else {
        cout << "\nSorry, I don't understand the question. Please try again." << endl;
    }
}