#include <iostream>
#include <fstream>
#include <regex>
using namespace std;

enum Language {ukr, eng};

class Game {
protected:
    enum Language lang;
public:
    Game() {lang = ukr;}
    void setLanguage();
    void menu();
};

void Game::setLanguage() {
    cout  << "\nLanguage" << endl << endl;
    cout << "1. English" << endl;
    cout << "2. Українська" << endl << endl;
    cout << "Your  choice: ";
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
        cout << "Incorrect number! Try again" << endl;
        setLanguage();
    }
}

typedef struct treeNode treeNode;
struct treeNode {
    string text;
    treeNode *yes, *no;
};

class fileMeneger {
    string filename;
    fstream file;
    void read(treeNode* &root);
    void write(treeNode* root);
public:
    fileMeneger() {};
    fileMeneger(string name) {
        filename = name;
    }
    void readFromFile(treeNode* &root);
    void writeToFile(treeNode *root);
};

void fileMeneger::readFromFile(treeNode* &root) {
    file.open(filename, ios::in);
    if (!file.is_open()) {
        cout << "File not found" << endl;
        exit(1);
    }
    read(root);
    file.close();
}

void fileMeneger::read(treeNode* &root) {
    
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

void fileMeneger::writeToFile(treeNode *root) {
    file.open(filename, ios::out | ios::trunc);
    if (!file.is_open()) {
        cout << "File not found" << endl;
        exit(1);
    }
    write(root);
    file.close();
}

void fileMeneger::write(treeNode *root) {
    
    if (root == NULL) {
        file << "#" << endl;
        return;
    }
    file <<  root->text << endl;
    write(root->yes);
    write(root->no);
}

class userInput {
public:
    static bool getUkrAnswer();
    static bool getEngAnswer();
    static string inputAnimal(Language lang);
    static string inputQuestion();
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
    regex pattern("\\s+");
    newAnimal = regex_replace(newAnimal, pattern, " ");
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
        if (islower(newAnimal[0])) {
            newAnimal[0] = toupper(newAnimal[0]);
        }
    }
    return newAnimal;
}

string userInput::inputQuestion() {
    string question;
    cin.ignore();
    getline(cin, question);
    regex pattern("\\s+");

    question = regex_replace(question, pattern, " ");
    if (islower(question[0])) {
        question[0] = toupper(question[0]);
    }
    if (question[question.length()-1] != '?') {
        question = question + "?";
    }
    return question;
}

class thinkingGame : public Game {
    treeNode* treeRoot;
    fileMeneger files;
public:
    thinkingGame(Language l) {
        lang = l;
        treeRoot = NULL;
        string filename = (lang == ukr) ? "animals_tree_ukr.txt" :  "animals_tree_eng.txt";
        files = fileMeneger(filename);
    }
    void play();
    void question(treeNode *root);
    void addQuestion(treeNode* &node);
};

void thinkingGame::addQuestion(treeNode* &node) {
    cout << "What's your animal?" << endl;
    string newAnimal = userInput::inputAnimal(lang);
    cout << "Enter the question in such a way that for " << newAnimal << " the answer to it is yes, and for " << node->text << " it is no" << endl;
    string question = userInput::inputQuestion();
    treeNode *yes = new treeNode();
    yes->text = newAnimal;
    treeNode *no = new treeNode();
    no->text = node->text;
    node->text = question;
    node->yes = yes;
    node->no = no;
    cout << "Your animal was added successful" << endl;
}

void thinkingGame::question(treeNode *root) {
    if (root->yes == NULL ||  root->no == NULL) {
        cout << "Is your animal " << root->text << endl;
        bool ans = (lang == ukr) ? userInput::getUkrAnswer() : userInput::getEngAnswer();
        if (ans) {
            cout << "cool!" << endl;
        } else {
            cout << "hmmm..." << endl;
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
    cout << "\nГра \"Тварини\"" << endl << endl;
    cout << "Меню:" << endl;
    cout << "1. Загадай тварину" << endl;
    cout << "2. Відгадай тварину" << endl;
    cout << "3. Мова (Language)" << endl;
    cout << "4. Правила" << endl;
    cout << "5. Вихід" << endl;
    cout << "Введіть номер з меню: ";
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

            break;
        
        case 5:
            exit(0);
        
        default:
            cout << "Invalid input. Try again." << endl;
            menu();
    }                                        
}

void thinkingGame::play() {
    files.readFromFile(treeRoot);
    cout << "Think of animal? I try to guess it for you! Tap enter to start" << endl;
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