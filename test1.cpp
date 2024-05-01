#include <iostream>
#include <fstream>
using namespace std;
typedef struct treeNode treeNode;
struct treeNode {
    string text;
    treeNode *yes, *no;
};

void readFromFile(treeNode* &root, ifstream& file) {
    string input;
    getline(file, input);
    if (input == "#") {
        root = NULL;
        return;
    }
    root = new treeNode();
    root->text = input;
    input.clear();
    readFromFile(root->yes, file);
    readFromFile(root->no, file);
}

void writeToFile(treeNode *root, ofstream& file) {
    
    if (root == NULL) {
        file << "#" << endl;
        return;
    }
    file <<  root->text << endl;
    writeToFile(root->yes, file);
    writeToFile(root->no, file);
}

int main() {
    
}