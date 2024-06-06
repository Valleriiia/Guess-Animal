#include <iostream>
#include "userInput.h"

class thinkingGame : public Game {
private:
    treeNode* treeRoot;
public:
    thinkingGame(Language l);
    void play();
    void question(treeNode *root);
    void addQuestion(treeNode* &node);
};