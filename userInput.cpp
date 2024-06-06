#include <locale>
#include <codecvt>
#include <algorithm>
#include "userInput.h"

// Функція для користувацького введення відповіді англійською
bool userInput::getEngAnswer() {
    // Введення відповіді користувачем
    string answer;
    cin >> answer;

    // Переводить відповідь у нижній регістр
    stringToLower(answer);

    // Перевіряє відповідь
    if(answer == "yes" || answer == "y"){
        return true;
    } else if (answer == "no" || answer == "n"){
        return false;
    }else{
        // Якщо введення не коректне, дає користувачу спробувати відповісти ще раз
        cout << "Invalid response! Try again" << endl;
        return getEngAnswer();
    }
}

// Функція для користувацького введення відповіді українською
bool userInput::getUkrAnswer() {
    // Введення відповіді користувачем
    string answer;
    cin >> answer;

    // Переводить відповідь у нижній регістр
    stringToLower(answer);
    
    // Перевіряє відповідь
    if(answer == "так" || answer == "та" || answer == "т"){
        return true;
    } else if (answer == "ні" || answer == "н"){
        return false;
    }else{
        // Якщо введення не коректне, дає користувачу спробувати відповісти ще раз
        cout << "Неправельне введення! Спробуйте ще раз" << endl;
        return getUkrAnswer();
    }
}

// Функція для введення та перевірки введення тварини
string userInput::inputAnimal(Language lang) {
    // Введення тварини користувачем
    string newAnimal;
    getline(cin, newAnimal);

    // Приберає нелітерні символи з введеного рядка
    removeNonAlphabetic(newAnimal);

    // Переводить введенні дані у нижній регістр
    stringToLower(newAnimal);

    // Перевіряє довжину введених даних
    if (newAnimal.length() <= 2) {
        cout << ((lang == ukr) ? "Помилка введення! Спробуйте ще раз" : "Invalid input! Try again") << endl;
        cin.clear();
        newAnimal = inputAnimal(lang);
    }

    // Редагує введені данні в залежності від мови
    if (lang == eng) {
        // Додає a або an на початок
        if (!(newAnimal.substr(0, 2) == "a " || newAnimal.substr(0, 3) == "an ")) {
            char first = newAnimal[0];
            newAnimal = ((first == 'a' || first == 'e' || first == 'u' || first == 'i' || first == 'o') ? "an " : "a ") + newAnimal;
        }

        // Змінює першу літеру другого слова на верхній регістр
        if(isspace(newAnimal[2])) {
            newAnimal[3] = toupper(newAnimal[3]);
        } else {
            newAnimal[2] = toupper(newAnimal[2]);
        }
    } else {
        // Змінює першу букву на верхній регістр
        wstring animal = wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(newAnimal);
        animal[0] = towupper(animal[0]);
        newAnimal = wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(animal);
    }

    // Повертає відформатоване введення
    return newAnimal;
}

// Функція для введення та перевірки введення питаннь
string userInput::inputQuestion() {
    // Введення питання користувачем
    string question;
    getline(cin, question);

    // Приберає нелітерні символи з введеного рядка
    removeNonAlphabetic(question);

    // Переводить введенні дані у нижній регістр
    stringToLower(question);

    // Змінює першу букву на верхній регістр
    wstring wquestion = wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(question);
    wquestion[0] = towupper(wquestion[0]);
    question = wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(wquestion);

    // Додає ? в кінець питання
    question = question + "?";

    // Повертає відформатоване питання
    return question;
}

// Функція для видалення нелітерних символів з рядка
void userInput::removeNonAlphabetic(string &str) {
    // Видаляє початкові та кінцеві пробіли з рядка
    size_t i = 0;
    while (i < str.length()/2 && (isspace(str[i]) || isspace(str[str.length() - i-1]))) {
        if (isspace(str[i])) {
            str.erase(i, 1);
        }
        if (isspace(str[str.length()-i-1])) {
            str.erase(str.length()-i-1);
        }
    }
    // Видаляє всі символи, які не є буквами, пробілами або '
    wstring wstr = wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(str);
    for (size_t i = 0; i < wstr.length(); i++) {
        if (!iswalpha(wstr[i]) && !iswspace(wstr[i]) && wstr[i] != L'\'') {
            wstr.erase(i, 1);
            i--;
        }
    }
    str = wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(wstr);
}

// Функція для переводення рядка у нижній регістр
void userInput::stringToLower(string &str) {
    wstring wstr = wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(str);
    transform(wstr.begin(), wstr.end(), wstr.begin(), towlower);
    str = wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(wstr);
}