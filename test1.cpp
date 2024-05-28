#include <iostream>
#include <fstream>
#include <regex>
#include <locale>
#include <codecvt>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <codecvt>
#include <locale>

using namespace std;

enum Language {ukr, eng};
typedef struct treeNode treeNode;

struct treeNode {
    string text;
    treeNode *yes, *no;
};

class fileManager {
private:
    string filename;
    fstream file;
    void read(treeNode* &root);
    void write(treeNode* root);
public:
    fileManager() {}
    fileManager(string name) {filename = name;}
    void setFilename(string name);
    void readAndPrintText();
    void readFromFile(treeNode* &root);
    void writeToFile(treeNode *root);
};

void fileManager::setFilename(string name) {
    filename = name;
}

void fileManager::readAndPrintText() {
    file.open(filename, ios::in);
    if (!file.is_open()) {
        cout << "File not found" << endl;
        exit(1);
    }
    string text;
    while (!file.eof()) {
        getline(file, text);
        cout << text << endl;
    }    
    cout << endl;
    file.close();
}

void fileManager::readFromFile(treeNode* &root) {
    file.open(filename, ios::in);
    if (!file.is_open()) {
        cout << "File not found" << endl;
        exit(1);
    }
    read(root);
    file.close();
}

void fileManager::read(treeNode* &root) {
    string input;
    getline(file, input);
    if (input[0] == '#') {
        root = NULL;
        return;
    }
    root = new treeNode();
    root->text = input;
    input.clear();
    read(root->yes);
    read(root->no);
}

void fileManager::writeToFile(treeNode *root) {
    file.open(filename, ios::out | ios::trunc);
    if (!file.is_open()) {
        cout << "File not found" << endl;
        exit(1);
    }
    write(root);
    file.close();
}

void fileManager::write(treeNode *root) {
    if (root == NULL) {
        file << "#" << endl;
        return;
    }
    file <<  root->text << endl;
    write(root->yes);
    write(root->no);
}

class Game {
protected:
    enum Language lang;
    fileManager files;
public:
    Game() {lang = ukr;}
    void setLanguage();
    void menu();
};

void Game::setLanguage() {
    cout  << ((lang == ukr) ? "\nМова" : "\nLanguage") << endl << endl;
    cout << "1. English" << endl;
    cout << "2. Українська" << endl << endl;
    cout << ((lang == ukr) ? "Ваш вибір: " : "Your  choice: ");
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
        lang = eng;
        break;

    case 2:
        lang = ukr;
        break;
    
    default:
        cout << ((lang == ukr) ? "Неправельне введення! Спробуйте ще раз" : "Incorrect number! Try again") << endl;
        setLanguage();
    }
}



class userInput {
public:
    static bool getUkrAnswer();
    static bool getEngAnswer();
    static string inputAnimal(Language lang);
    static string inputQuestion();
private: 
    static void removeNonAlphabetic(string &str);
    static void stringToLower(string &str);
};

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
        if (islower(newAnimal[2]) && islower(newAnimal[3])) {
            if(isspace(newAnimal[2])) {
                newAnimal[3] = toupper(newAnimal[3]);
            } else {
                newAnimal[2] = toupper(newAnimal[2]);
            }
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
    regex pattern("\\s+");
    str = regex_replace(str, pattern, " ");
    wstring wstr = wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(str);
    for (size_t i = 0; i < wstr.length(); i++) {
        if (!iswalpha(wstr[i]) && !iswspace(wstr[i])) {
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

class thinkingGame : public Game {
private:
    treeNode* treeRoot;
public:
    thinkingGame(Language l) {
        lang = l;
        treeRoot = NULL;
        string filename = (lang == ukr) ? "animals_tree_ukr.txt" :  "animals_tree_eng.txt";
        files = fileManager(filename);
    }
    void play();
    void question(treeNode *root);
    void addQuestion(treeNode* &node);
};

void thinkingGame::addQuestion(treeNode* &node) {
    cout << ((lang == ukr) ? "Яку тварину ви загадали?" : "What's your animal?") << endl;
    string newAnimal = userInput::inputAnimal(lang);
    cin.clear();
    if (lang == ukr) {
        cout << "Введіть питання таке, щоб для " << newAnimal << " відповідь на нього була так, а для " << node->text << " - ні" << endl;
    } else {
        cout << "Enter a question such that the answer to it for " << newAnimal << " is yes, and for " << node->text << " - no" << endl;
    }
    string question = userInput::inputQuestion();
    size_t minLength = (lang == ukr) ? 16 : 10;
    while (question.length() < minLength) {
       cout << ((lang == ukr) ? "Питання занадто коротке. Спробуйте ще раз." : "The question is too short. Try again.") << endl;
       question = userInput::inputQuestion();
    }
    treeNode *yes = new treeNode();
    yes->text = newAnimal;
    treeNode *no = new treeNode();
    no->text = node->text;
    node->text = question;
    node->yes = yes;
    node->no = no;
    cout << ((lang == ukr) ? "Вашу тварину було успішно додано" : "Your animal was added successful") << endl;
}

void thinkingGame::question(treeNode *root) {
    if (root->yes == NULL ||  root->no == NULL) {
        cout << ((lang == ukr) ? "Ваша тварина - це " : "Is your animal ") << root->text << endl;
        bool ans = (lang == ukr) ? userInput::getUkrAnswer() : userInput::getEngAnswer();
        if (ans) {
            cout << ((lang == ukr) ? "Круто!" : "Cool!") << endl;
        } else {
            cout << ((lang == ukr) ? "хммм..." : "hmmm...") << endl;
            addQuestion(root);
        }
        return;
    }
    cout << root->text << endl;
    bool ans = (lang == ukr) ? userInput::getUkrAnswer() : userInput::getEngAnswer();
    if (ans) {
        question(root->yes);
    } else {
        question(root->no);
    }
}

class GuessingGame : public Game {
private:
    unordered_map<string, unordered_set<string>> animals;
    unordered_map<string, unordered_set<string>> keywords;

public:
    GuessingGame(Language l) {
        lang = l;
        initAnimals();
        initKeywords();
    }
    void play();
private:
    void initAnimals();
    void initKeywords();
};

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

void thinkingGame::play() {
    files.readFromFile(treeRoot);
    if (lang == ukr) {
        cout << "Загадайте тварину, я спробую її вгадати. Натисніть enter, щоб розпочати";
    } else {
        cout << "Think of animal, I try to guess it for you! Tap enter to start";
    }
    cin.get();
    question(treeRoot);
    files.writeToFile(treeRoot);
}


class QuestionAsker {
public:
    void ask(const string& animal, const unordered_map<string, unordered_set<string>>& animals, const unordered_map<string, unordered_set<string>>& keywords, Language lang) {
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
};

class Guesser {
public:
    bool guess(const string& animal, Language lang) {
        if (lang == ukr) {
            cout << "\nВаше припущення: ";
        } else {
            cout << "\nYour guess: ";
        }
        string guess;
        getline(cin, guess);

        wstring_convert<codecvt_utf8<wchar_t>> converter;

        wstring wguess = converter.from_bytes(guess);
        wstring wanimal = converter.from_bytes(animal);

        transform(wguess.begin(), wguess.end(), wguess.begin(), towlower);
        transform(wanimal.begin(), wanimal.end(), wanimal.begin(), towlower);

        guess = converter.to_bytes(wguess);
        string animLow = converter.to_bytes(wanimal);

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
};

void GuessingGame::play() {
    srand(time(nullptr));
    auto iter = animals.begin();
    advance(iter, rand() % animals.size());
    const string& animal = iter->first;
    if (lang == ukr) {
        cout << "\nКомп'ютер загадав тварину. Спробуйте вгадати, яку саме." << endl;
    } else {
        cout << "\nThe computer guessed the animal. Try to guess which animal the computer chose." << endl;
    }

    int input;
    while (true) {
        if (lang == ukr) {
            cout << "\nЩо ви хочете зробити? (1 - задати запитання, 2 - зробити припущення, 3 - завершити гру): ";
        } else {
            cout << "\nWhat do you want to do? (1 - ask a question, 2 - make a guess, 3 - end the game): ";
        }
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << ((lang == ukr) ? "Помилка введення! Спробуйте ще раз" : "Invalid input! Try again") << endl;
            continue;
        }
        cin.ignore();
        switch (input) {
            case 1: {
                QuestionAsker asker;
                asker.ask(animal, animals, keywords, lang);
                break;
            }
            case 2: {
                Guesser guesser;
                bool correct = guesser.guess(animal, lang);
                if (correct) {
                    return; 
                }
                break;
            }
            case 3: {
                if (lang == ukr) {
                    cout << "\nГра завершена. Чекаємо на вас знову!" << endl;
                } else {
                    cout << "\nThe game is over. We are waiting for you again!" << endl;
                }
                return;
            }
            default: {
                if (lang == ukr) {
                    cout << "\nНекоректний вибір. Оберіть 1 для запитання, 2 для припущення, або 3 для завершення гри." << endl;
                } else {
                    cout << "\nInvalid choice. Choose 1 for asking, 2 for guessing, or 3 to end the game." << endl;
                }
            }
        }
    }
}

void GuessingGame::initAnimals() {
    if (lang == ukr) {
        animals = {
            {"Тигр", {"хижак", "смугастий", "велика", "гострі зуби", "кігті", "швидка", "ссавець"}},
            {"Лев", {"хижак", "грива", "велика", "кігті", "гострі зуби", "швидка", "стадна"}},
            {"Лисиця", {"хижак", "хитра", "рижа", "невелика", "швидка", "ссавець", "розумний", "гострі зуби"}},
            {"Корова", {"травоїдна", "домашня", "має роги", "молоко", "велика", "ссавець", "пасеться", "довгі роги"}},
            {"Жираф", {"травоїдна", "довга шия", "високий", "плямиста шкіра", "довгі ноги", "має роги"}},
            {"Верблюд", {"ссавець", "травоїдний", "великий", "довга шия", "горби", "пустельний"}},
            {"Краб", {"водний", "ракоподібний", "панцир", "хижак", "клешні", "морський"}},
            {"Каракатиця", {"хижак", "водний", "щупальця", "м'яке тіло", "випускає чорнило", "змінює колір"}},
            {"Кальмар", {"хижак", "водний", "швидкий", "м'яке тіло", "щупальця", "випускає чорнило", "безхребетний", "велика", "змінює колір"}},
            {"Орел", {"хижак", "літає", "гострий зір", "велика", "кігті", "швидка", "перната"}},
            {"Ластівка", {"всеїдна", "літає", "швидка", "невелика", "перната", "гніздиться", "мігрує"}},
            {"Папуга", {"травоїдна", "літає", "яскраве пір'я", "розмовляє", "невелика", "перната", "розумний"}},
            {"Кіт", {"ссавець", "домашня", "вуса", "нічний зір", "м'яке хутро", "кігті", "соціальна", "нявкає"}},
            {"Собака", {"домашня", "нюх", "гавкає", "вірна", "соціальна", "ссавець", "м'яке хутро"}},
            {"Кролик", {"травоїдна", "домашня", "довгі вуха", "швидка", "моркву", "м'яке хутро", "стрибає"}}
        };
    } else {
        animals = {
            {"Tiger", {"predator", "striped", "big", "sharp teeth", "claws", "fast", "mammal"}},
            {"Lion", {"predator", "mane", "big", "claws", "sharp teeth", "fast", "social"}},
            {"Fox", {"predator", "cunning", "red", "small", "fast", "mammal", "intelligent", "sharp teeth"}},
            {"Cow", {"herbivore", "domestic", "has horns", "milk", "big", "mammal", "grazing", "long horns"}},
            {"Giraffe", {"herbivore", "long neck", "tall", "spotted skin", "long legs", "has horns"}},
            {"Camel", {"mammal", "herbivore", "big", "long neck", "humps", "desert"}},
            {"Crab", {"aquatic", "crustacean", "shell", "predator", "claws", "marine"}},
            {"Cuttlefish", {"predator", "aquatic", "tentacles", "soft body", "ink", "changes color"}},
            {"Squid", {"predator", "aquatic", "fast", "soft body", "tentacles", "ink", "invertebrate", "big", "changes color"}},
            {"Eagle", {"predator", "flies", "sharp vision", "big", "claws", "fast", "feathered"}},
            {"Swallow", {"omnivore", "flies", "fast", "small", "feathered", "nests", "migrates"}},
            {"Parrot", {"herbivore", "flies", "bright feathers", "talks", "small", "feathered", "intelligent"}},
            {"Cat", {"mammal", "domestic", "whiskers", "night vision", "soft fur", "claws", "social", "meows"}},
            {"Dog", {"domestic", "sense of smell", "barks", "loyal", "social", "mammal", "soft fur"}},
            {"Rabbit", {"herbivore", "domestic", "long ears", "fast", "carrots", "soft fur", "hops"}}
        };
    }
}

void GuessingGame::initKeywords() {
    if (lang == ukr) {
        keywords = {
            {"хижак", {"хижак", "Хижак", "хижий", "Хижий", "хижа", "Хижа"}},
            {"травоїдна", {"травоїдна", "Травоїдна", "травоїдний", "Травоїдний"}},
            {"всеїдна", {"всеїдна", "Всеїдна", "всеїдний", "Всеїдний"}},
            {"літає", {"літає", "Літає", "літаючий", "Літаючий", "літаюча", "Літаюча", "вміє літати", "Вміє літати", "може літати", "Може літати"}}, 
            {"водний", {"водний", "Водний",  "водна", "Водна", "живе у воді", "Живе у воді" }},
            {"домашня", {"домашня", "Домашня", "домашній", "Домашній", "свійська", "Свійська"}},
            {"смугастий", {"смугастий", "Смугастий", "смугаста", "Смугаста",  "зі смугами", "Зі смугами", "в смужках", "В смужках"}},
            {"велика", {"велика", "Велика", "великий", "Великий"}},
            {"гострі зуби", {"гострі зуби", "Гострі зуби", "гострі ікла", "Гострі ікла"}},
            {"кігті", {"кігті", "Кігті","кігтями", "Кігтями"}},
            {"швидка", {"швидка", "Швидка", "швидкий", "Швидкий", "швидко", "Швидко"}},
            {"ссавець", {"ссавець", "Ссавець", "ссавці", "Ссавці"}},
            {"грива", {"грива", "Грива", "гриву", "Гриву", "гриви", "Гриви", "з гривою", "З гривою"}},
            {"стадна", {"стадна", "Стадна", "стадний", "Стадний", "в стаді", "В стаді", "стадом", "Стадом"}},
            {"хитра", {"хитра", "Хитра", "хитрий", "Хитрий"}},
            {"рижа", {"рижа", "Рижа", "рижий", "Рижий", "рудий", "Рудий", "руда", "Руда"}},
            {"невелика", {"невелика", "Невелика", "невеликий", "Невеликий", "маленька", "Маленька", "малий", "Малий"}},
            {"розумний", {"розумний", "Розумний", "розумна", "Розумна"}},
            {"має роги", {"має роги", "Має роги", "з рогами", "З рогами", "рогатий", "Рогатий", "рогата", "Рогата"}},
            {"молоко", {"молоко", "Молоко"}},
            {"пасеться", {"пасеться", "Пасеться", "пасти", "Пасти"}},
            {"довга шия", {"довга шия", "Довга шия", "довгу шию", "Довгу шию"}},
            {"високий", {"високий", "Високий", "висока", "Висока"}},
            {"плямиста шкіра", {"плямиста шкіра", "Плямиста шкіра", "плямистий", "Плямистий", "плямиста", "Плямиста"}},
            {"довгі ноги", {"довгі ноги", "Довгі ноги", "довгонога", "Довгонога"}},
            {"пустельний", {"пустельний", "Пустельний", "пустельна", "Пустельна", "живе в пустелі", "Живе в пустелі"}},
            {"ракоподібний", {"ракоподібний", "Ракоподібний", "ракоподібна", "Ракоподібна"}},
            {"панцир", {"панцир", "Панцир", "панцирний", "Панцирний", "панцирна", "Панцирна"}},
            {"клешні", {"клешні", "Клешні", "клешня", "Клешня", "клешню", "Клешню"}},
            {"щупальця", {"щупальця", "Щупальця", "щупалець", "Щупалець", "щупальці", "Щупальці"}},
            {"м'яке тіло", {"м'яке тіло", "М'яке тіло"}},
            {"випускає чорнило", {"випускає чорнило", "Випускає чорнило", "чорнило", "Чорнило"}},
            {"змінює колір", {"змінює колір", "Змінює колір", "змінювати колір", "Змінювати колір", "колір"}},
            {"безхребетний", {"безхребетний", "Безхребетний", "безхребетна", "Безхребетна"}},
            {"гострий зір", {"гострий зір", "Гострий зір", "зір"}},
            {"перната", {"перната", "Перната", "пернатий", "Пернатий", "з пір'ям", "З пір'ям"}},
            {"гніздиться", {"гніздиться", "Гніздиться", "гніздиться в", "Гніздиться в", "гніздо", "Гніздо"}},
            {"мігрує", {"мігрує", "Мігрує", "мігрують", "Мігрують", "мігруючий", "Мігруючий"}},
            {"яскраве пір'я", {"яскраве пір'я", "Яскраве пір'я"}},
            {"розмовляє", {"розмовляє", "Розмовляє", "говорить", "Говорить", "розмовляти", "Розмовляти"}},
            {"вуса", {"вуса", "Вуса", "вусики", "Вусики", "з вусами", "З вусами"}},
            {"нічний зір", {"нічний зір", "Нічний зір", "бачить вночі", "Бачить вночі"}},
            {"м'яке хутро", {"м'яке хутро", "М'яке хутро"}},
            {"соціальна", {"соціальна", "Соціальна", "соціальний", "Соціальний"}},
            {"нявкає", {"нявкає", "Нявкає", "мяукає", "Мяукає", "мяу", "Мяу"}},
            {"нюх", {"нюх", "Нюх", "запах", "Запах", "чутливий до запахів", "Чутливий до запахів"}},
            {"гавкає", {"гавкає", "Гавкає", "гав", "Гав", "гавкати", "Гавкати"}},
            {"вірна", {"вірна", "Вірна", "вірний", "Вірний"}},
            {"моркву", {"моркву", "Моркву", "морква", "Морква"}},
            {"довгі вуха", {"довгі вуха", "Довгі вуха", "вуха"}},
            {"стрибає", {"стрибає", "Стрибає", "стрибати", "Стрибати"}}
        };
    } else {
        keywords = {
            {"predator", {"predator", "Predator", "predatory", "Predatory"}},
            {"herbivore", {"herbivore", "Herbivore", "herbivorous", "Herbivorous"}},
            {"omnivore", {"omnivore", "Omnivore", "omnivorous", "Omnivorous"}},
            {"flies", {"flies", "Flies", "flying", "Flying", "can fly", "Can fly"}},
            {"aquatic", {"aquatic", "Aquatic", "water-dwelling", "Water-dwelling"}},
            {"domestic", {"domestic", "Domestic", "tame", "Tame"}},
            {"striped", {"striped", "Striped", "stripes", "Stripes"}},
            {"big", {"big", "Big", "large", "Large"}},
            {"sharp teeth", {"sharp teeth", "Sharp teeth", "sharp fangs", "Sharp fangs"}},
            {"claws", {"claws", "Claws"}},
            {"fast", {"fast", "Fast", "quick", "Quick"}},
            {"mammal", {"mammal", "Mammal", "mammals", "Mammals"}},
            {"mane", {"mane", "Mane"}},
            {"social", {"social", "Social"}},
            {"cunning", {"cunning", "Cunning"}},
            {"red", {"red", "Red"}},
            {"small", {"small", "Small"}},
            {"intelligent", {"intelligent", "Intelligent"}},
            {"has horns", {"has horns", "Has horns", "horned", "Horned"}},
            {"milk", {"milk", "Milk"}},
            {"grazing", {"grazing", "Grazing"}},
            {"long neck", {"long neck", "Long neck"}},
            {"tall", {"tall", "Tall"}},
            {"spotted skin", {"spotted skin", "Spotted skin"}},
            {"long legs", {"long legs", "Long legs"}},
            {"desert", {"desert", "Desert", "desert-dwelling", "Desert-dwelling"}},
            {"crustacean", {"crustacean", "Crustacean"}},
            {"shell", {"shell", "Shell"}},
            {"claws", {"claws", "Claws"}},
            {"tentacles", {"tentacles", "Tentacles"}},
            {"soft body", {"soft body", "Soft body"}},
            {"ink", {"ink", "Ink"}},
            {"changes color", {"changes color", "Changes color"}},
            {"invertebrate", {"invertebrate", "Invertebrate"}},
            {"sharp vision", {"sharp vision", "Sharp vision"}},
            {"feathered", {"feathered", "Feathered"}},
            {"nests", {"nests", "Nests"}},
            {"migrates", {"migrates", "Migrates"}},
            {"bright feathers", {"bright feathers", "Bright feathers"}},
            {"talks", {"talks", "Talks", "speaks", "Speaks"}},
            {"whiskers", {"whiskers", "Whiskers"}},
            {"night vision", {"night vision", "Night vision"}},
            {"soft fur", {"soft fur", "Soft fur"}},
            {"meows", {"meows", "Meows", "meowing", "Meowing"}},
            {"sense of smell", {"sense of smell", "Sense of smell"}},
            {"barks", {"barks", "Barks", "barking", "Barking"}},
            {"loyal", {"loyal", "Loyal"}},
            {"carrots", {"carrots", "Carrots"}},
            {"long ears", {"long ears", "Long ears"}},
            {"hops", {"hops", "Hops", "hopping", "Hopping"}}
            };
    }
}

int main() {
    Game game;
    while(true) {
        game.menu();
    }
    return 0;
}

