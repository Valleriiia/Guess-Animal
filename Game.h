#include <iostream>
#include "fileManager.h"
#ifndef ADD_H
#define ADD_H

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
#endif