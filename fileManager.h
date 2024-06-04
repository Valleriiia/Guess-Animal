#include <iostream>
#include <fstream>
#include "treeNode.h"
#ifndef ADD_H

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
#endif