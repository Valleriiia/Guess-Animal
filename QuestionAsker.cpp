#include "QuestionAsker.h"
#include <cstring>

void QuestionAsker::ask(const string& animal, const unordered_map<string, unordered_set<string>>& animals, const unordered_map<string, unordered_set<string>>& keywords, Language lang) {
    string question;
    if (lang == ukr) {
        cout << "\nЗадайте своє запитання: ";
    } else {
        cout << "\nAsk your question: ";
    }
    getline(cin, question);

    for (const auto& [key, keys] : keywords) {
        for (const auto& _key : keys) {
            if (strstr(question.c_str(), _key.c_str()) != nullptr) {
                if (animals.at(animal).count(key) > 0) {
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
    if (lang == ukr) {
        cout << "\nНезрозуміле запитання. Спробуйте знову." << endl;
    } else {
        cout << "\nSorry, I don't understand the question. Please try again." << endl;
    }
}