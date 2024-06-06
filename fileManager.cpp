#include "fileManager.h"

// Конструктор з ім'ям файлу
fileManager::fileManager(string name) {filename = name;}

// Встановлює назву файлу для менеджера файлів
void fileManager::setFilename(string name) {
    filename = name;
}

// Читає та виводить у консоль текст з файлу
void fileManager::readAndPrintText() {
    // Відкриває файл у режимі читання
    file.open(filename, ios::in);
    if (!file.is_open()) {
        cout << "File not found" << endl;
        exit(1);
    }
    string text;

    // Читає файл рядок за рядком та виводить кожен рядок
    while (!file.eof()) {
        getline(file, text);
        cout << text << endl;
    }    
    cout << endl;

    // Закриває файл
    file.close();
}

// Зчитує з файлу та будує бінарне дерево
void fileManager::readFromFile(treeNode* &root) {
    // Відкриває файл у режимі читання
    file.open(filename, ios::in);
    if (!file.is_open()) {
        cout << "File not found" << endl;
        exit(1);
    }

    // Читає з файлу та будує бінарне дерево
    read(root);

    // Закриває файл
    file.close();
}

// Рекурсивно зчитує з файлу кожен вузол дерева та будує його
void fileManager::read(treeNode* &root) {
    string input;

    // Зчитує рядок з файлу
    getline(file, input);

    // Якщо рядок починається з #, запусує вузол як null
    if (input[0] == '#') {
        root = NULL;
        return;
    }

    // Створює новий вузол зі зчитаним з файлу рядком
    root = new treeNode();
    root->text = input;
    input.clear();

    // Рекурсивно читає файл та будує праву і ліву гілки дерева
    read(root->yes);
    read(root->no);
}


// Записує бінарне дерево до файлу
void fileManager::writeToFile(treeNode *root) {
    // Відкриває файл в режимі введення
    file.open(filename, ios::out | ios::trunc);
    if (!file.is_open()) {
        cout << "File not found" << endl;
        exit(1);
    }

    // Записує бінарне дерево до файлу
    write(root);

    // Закриває файл
    file.close();
}

// Рекурсивно записує вузли бінарного дерева до файлу
void fileManager::write(treeNode *root) {
    // Якщо вузол null, записує до файлу #
    if (root == NULL) {
        file << "#" << endl;
        return;
    }

    // Записує до файлу текст вузла
    file <<  root->text << endl;

    // Рекурсивно записує праву та ліву гілки до файлу
    write(root->yes);
    write(root->no);
}