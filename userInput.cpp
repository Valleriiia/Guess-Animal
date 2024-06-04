#include <locale>
#include <codecvt>
#include <algorithm>
#include "userInput.h"

bool userInput::getEngAnswer() {
    string answer;
    cin >> answer;
    if(answer == "yes" || answer == "y"){
        return true;
    } else if (answer == "no" || answer == "n"){
        return false;
    }else{
        cout << "Invalid response! Try again" << endl;
        return getEngAnswer();
    }
}

bool userInput::getUkrAnswer() {
    string answer;
    cin >> answer;
    if(answer == "так" || answer == "та" || answer == "т"){
        return true;
    } else if (answer == "ні" || answer == "н"){
        return false;
    }else{
        cout << "Неправельне введення! Спробуйте ще раз" << endl;
        return getUkrAnswer();
    }
}

string userInput::inputAnimal(Language lang) {
    string newAnimal;
    cin.ignore();
    getline(cin, newAnimal);
    removeNonAlphabetic(newAnimal);
    stringToLower(newAnimal);
    if (newAnimal.length() <= 2) {
        cout << ((lang == ukr) ? "Помилка введення! Спробуйте ще раз" : "Invalid input! Try again") << endl;
        newAnimal = inputAnimal(lang);
    }
    if (lang == eng) {
        if (!(newAnimal.substr(0, 2) == "a " || newAnimal.substr(0, 3) == "an ")) {
            char first = newAnimal[0];
            newAnimal = ((first == 'a' || first == 'e' || first == 'u' || first == 'i' || first == 'o') ? "an " : "a ") + newAnimal;
        }
        if(isspace(newAnimal[2])) {
            newAnimal[3] = toupper(newAnimal[3]);
        } else {
            newAnimal[2] = toupper(newAnimal[2]);
        }
    } else {
        wstring animal = wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(newAnimal);
        animal[0] = towupper(animal[0]);
        newAnimal = wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(animal);
    }
    return newAnimal;
}

string userInput::inputQuestion() {
    string question;
    getline(cin, question);
    removeNonAlphabetic(question);
    stringToLower(question);
    wstring wquestion = wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(question);
    wquestion[0] = towupper(wquestion[0]);
    question = wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(wquestion);
    question = question + "?";
    return question;
}

void userInput::removeNonAlphabetic(string &str) {
    size_t i = 0;
    while (i < str.length()/2 && (isspace(str[i]) || isspace(str[str.length() - i-1]))) {
        if (isspace(str[i])) {
            str.erase(i, 1);
        }
        if (isspace(str[str.length()-i-1])) {
            str.erase(str.length()-i-1);
        }
    }
    wstring wstr = wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(str);
    for (size_t i = 0; i < wstr.length(); i++) {
        if (!iswalpha(wstr[i]) && !iswspace(wstr[i]) && wstr[i] != L'\'') {
            wstr.erase(i, 1);
            i--;
        }
    }
    str = wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(wstr);
}

void userInput::stringToLower(string &str) {
    wstring wstr = wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(str);
    transform(wstr.begin(), wstr.end(), wstr.begin(), towlower);
    str = wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(wstr);
}