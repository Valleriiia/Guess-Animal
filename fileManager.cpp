#include "fileManager.h"


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