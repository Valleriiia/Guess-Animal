#include <unordered_map>
#include <unordered_set>
#include <Game.h>

class GuessingGame : public Game {
private:
    unordered_map<string, unordered_set<string>> animals;
    unordered_map<string, unordered_set<string>> keywords;

public:
    GuessingGame(Language l) {
        lang = l;
        initAnimals();
        initKeywords();
    }
    void play();
private:
    void initAnimals();
    void initKeywords();
};