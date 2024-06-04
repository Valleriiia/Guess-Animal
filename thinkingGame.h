#include <iostream>
#include <Game.h>
#include <treeNode.h>

class thinkingGame : public Game {
private:
    treeNode* treeRoot;
public:
    thinkingGame(Language l) {
        lang = l;
        treeRoot = NULL;
        string filename = (lang == ukr) ? "animals_tree_ukr.txt" :  "animals_tree_eng.txt";
        files = fileManager(filename);
    }
    void play();
    void question(treeNode *root);
    void addQuestion(treeNode* &node);
};