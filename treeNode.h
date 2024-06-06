#include <iostream>
using namespace std;

#ifndef ADD_H
// Структура вузла бінарного дерева
struct treeNode {
    string text;
    treeNode *yes, *no;
};
#endif