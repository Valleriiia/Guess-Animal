#include <iostream>
#include <fstream>
#include <fileManager.h>

enum Language {ukr, eng};

class Game {
protected:
    enum Language lang;
    fileManager files;
public:
    Game() {lang = ukr;}
    void setLanguage();
    void menu();
};