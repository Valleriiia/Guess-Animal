#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <Game.h>

using namespace std;

class QuestionAsker {
public:
    void ask(const string& animal, const unordered_map<string, unordered_set<string>>& animals, const unordered_map<string, unordered_set<string>>& keywords, Language lang);
};