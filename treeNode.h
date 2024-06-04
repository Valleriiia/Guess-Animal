#include <iostream>
using namespace std;

#ifndef ADD_H

struct treeNode {
    string text;
    treeNode *yes, *no;
};
#endif