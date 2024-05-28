#include <iostream>
#include <fstream>
#include <regex>
#include <locale>
#include <codecvt>
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
    if (lang == ukr) {
        cout << "Введіть питання таке, щоб для " << newAnimal << " відповідь на нього була так, а для " << node->text << " - ні" << endl;
    } else {
        cout << "Enter the question in such a way that for " << newAnimal << " the answer to it is yes, and for " << node->text << " it is no" << endl;
    }
    std::cin.clear();
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

void show(treeNode *root) {
    if (root == NULL) {
        return;
    }
    cout << root->text << endl;
    show(root->yes);
    show(root->no);
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
    cin.ignore();
    thinkingGame tgame(lang);
    switch (choice) {
        case 1:
            tgame.play();
            break;

        case 2:

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
            menu();
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


int main() {
    Game game;
    while(true) {
        game.menu();
    }
    return 0;
}
