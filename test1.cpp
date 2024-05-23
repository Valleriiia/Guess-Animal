#include <iostream>
#include <fstream>
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
    int lang;
    cin >> lang;
    switch (lang) {
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
    file.open(filename, ios::out);
    if (!file.is_open()) {
        cout << "File not found" << endl;
        exit(1);
    }
    write(root);
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

class thinkingGame : public Game {
    treeNode* treeRoot;
    fileMeneger files;
public:
    thinkingGame() : Game() {
        treeRoot = NULL;
        string filename = (lang == ukr) ? "animals_tree_ukr.txt" :  "animals_tree_eng.txt";
        files = fileMeneger(filename);
    }
    void play();
    void question(treeNode *root);
    void addQuestion(treeNode* &node);
};

bool getAnswer() {
    string answer;
    cin >> answer;
    if(answer == "yes" || answer == "y"){
        return true;
    } else if (answer == "no" || answer == "n"){
        return false;
    }else{
        cout << "Invalid response! Try again" << endl;
        return getAnswer();
    }
}

void thinkingGame::addQuestion(treeNode* &node) {
    cout << "What's your animal?" << endl;
    string newAnimal;
    cin.ignore();
    getline(cin, newAnimal);
    cout << "Enter the question in such a way that for " << newAnimal << " the answer to it is yes, and for " << node->text << " it is no" << endl;
    string question;
    getline(cin, question);
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
        if (getAnswer()) {
            cout << "cool!" << endl;
        } else {
            cout << "hmmm..." << endl;
            addQuestion(root);
        }
        return;
    }
    cout << root->text << endl;
    if (getAnswer()) {
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
    thinkingGame tgame;
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