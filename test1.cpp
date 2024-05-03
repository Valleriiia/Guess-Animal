#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Animal {
    string name; 
    unordered_set<string> characteristics; 

    Animal(const string& name, const unordered_set<string>& characteristics)
        : name(name), characteristics(characteristics) {}
};

unordered_map<string, Animal> animals = {
    {"Акула", Animal("Акула", {"хижак", "водний"})},
    {"Дельфін", Animal("Дельфін", {"всеїдна", "водний"})},
    {"Морж", Animal("Морж", {"травоїдна", "водний"})},
    {"Кит", Animal("Кит", {"травоїдна", "водний"})},
    {"Орел", Animal("Орел", {"хижак", "літає"})},
    {"Сокіл", Animal("Сокіл", {"хижак", "літає"})},
    {"Ластівка", Animal("Ластівка", {"всеїдна", "літає"})},
    {"Папуга", Animal("Папуга", {"травоїдна", "літає"})},
    {"Кіт", Animal("Кіт", {"хижак", "домашня"})},
    {"Собака", Animal("Собака", {"хижак", "домашня"})},
    {"Кролик", Animal("Кролик", {"травоїдна", "домашня"})},
    {"Хом'як", Animal("Хом'як", {"травоїдна", "домашня"})},
    {"Лев", Animal("Лев", {"хижак", "наземний"})},
    {"Тигр", Animal("Тигр", {"хижак", "наземний"})},
    {"Вовк", Animal("Вовк", {"хижак", "наземний"})},
    {"Лисиця", Animal("Лисиця", {"хижак", "наземний"})},
    {"Корова", Animal("Корова", {"травоїдна", "наземний"})},
    {"Кінь", Animal("Кінь", {"травоїдна", "наземний"})},
    {"Олень", Animal("Олень", {"травоїдна", "наземний"})},
    {"Зебра", Animal("Зебра", {"травоїдна", "наземний"})}
};

unordered_set<string> question_keywords = {
    "хижак", "літає", "водний", "домашня", "травоїдна", "всеїдна", "наземний"
};

void play_user_guesses() {
    srand(time(nullptr));
    auto chosen_animal_iter = animals.begin();
    std::advance(chosen_animal_iter, rand() % animals.size());
    const Animal& chosen_animal = chosen_animal_iter->second;

    string user_input;
    cout << "Комп'ютер загадав тварину. Спробуйте вгадати, яку тварину загадав комп'ютер." << endl;

    while (true) {
        cout << "\nЩо ви хочете зробити? (1 - задати запитання, 2 - зробити припущення): ";
        getline(cin, user_input);

        if (user_input == "1") {
 
            cout << "\nЗадайте своє запитання: ";
            getline(cin, user_input);

            bool is_valid_question = false;
            string key_word;

            for (const auto& keyword : question_keywords) {
                if (user_input.find(keyword) != string::npos) {
                    is_valid_question = true;
                    key_word = keyword;
                    break;
                }
            }

            if (is_valid_question) {
                bool answer = chosen_animal.characteristics.count(key_word) > 0;

                cout << (answer ? "Так" : "Ні") << endl;
            } else {
                cout << "Невідоме питання. Спробуйте запитати про хижість, політ, водне середовище чи інші характеристики." << endl;
            }
        } else if (user_input == "2") {

            cout << "\nВведіть свою здогадку про назву тварини: ";
            getline(cin, user_input);

            if (user_input == chosen_animal.name) {
                cout << "Вітаю! Ви вгадали тварину! Це " << chosen_animal.name << "!" << endl;
                break;
            } else {
                cout << "Ні, це не " << user_input << ". Спробуйте ще раз." << endl;
            }
        } else {
            cout << "Невірний вибір. Введіть 1 для задавання запитання або 2 для припущення." << endl;
        }
    }
}

int main() {
    play_user_guesses();
    return 0;
}
