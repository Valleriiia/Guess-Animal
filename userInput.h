#include <iostream>
#include <Game.h>

class userInput {
public:
    static bool getUkrAnswer();
    static bool getEngAnswer();
    static string inputAnimal(Language lang);
    static string inputQuestion();
    static void stringToLower(string &str);
private: 
    static void removeNonAlphabetic(string &str);   
};