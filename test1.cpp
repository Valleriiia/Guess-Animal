#include <iostream>
#include <fstream>
using namespace std;

struct treeNode {
    string text;
    treeNode *yes, *no;
};

void readFromFile(treeNode* &root) {
    ifstream file("animals_tree.txt");
    string input;
    getline(file, input);
    if (input == "#") {
        root = NULL;
        return;
    }
    root = new treeNode();
    root->text = input;
    readFromFile(root->yes);
    readFromFile(root->no);
}