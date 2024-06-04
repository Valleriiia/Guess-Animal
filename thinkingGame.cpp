#include <thinkingGame.h>
#include <userInput.h>

void thinkingGame::addQuestion(treeNode* &node) {
    cout << ((lang == ukr) ? "Яку тварину ви загадали?" : "What's your animal?") << endl;
    string newAnimal = userInput::inputAnimal(lang);
    cin.clear();
    if (lang == ukr) {
        cout << "Введіть питання таке, щоб для " << newAnimal << " відповідь на нього була так, а для " << node->text << " - ні" << endl;
    } else {
        cout << "Enter a question such that the answer to it for " << newAnimal << " is yes, and for " << node->text << " - no" << endl;
    }
    string question = userInput::inputQuestion();
    size_t minLength = (lang == ukr) ? 16 : 10;
    while (question.length() < minLength) {
       cout << ((lang == ukr) ? "Питання занадто коротке. Спробуйте ще раз." : "The question is too short. Try again.") << endl;
       question = userInput::inputQuestion();
    }
    treeNode *yes = new treeNode();
    yes->text = newAnimal;
    treeNode *no = new treeNode();
    no->text = node->text;
    node->text = question;
    node->yes = yes;
    node->no = no;
    cout << ((lang == ukr) ? "Вашу тварину було успішно додано" : "Your animal was added successful") << endl;
}

void thinkingGame::question(treeNode *root) {
    if (root->yes == NULL ||  root->no == NULL) {
        cout << ((lang == ukr) ? "Ваша тварина - це " : "Is your animal ") << root->text << endl;
        bool ans = (lang == ukr) ? userInput::getUkrAnswer() : userInput::getEngAnswer();
        if (ans) {
            cout << ((lang == ukr) ? "Круто!" : "Cool!") << endl;
        } else {
            cout << ((lang == ukr) ? "хммм..." : "hmmm...") << endl;
            addQuestion(root);
        }
        return;
    }
    cout << root->text << endl;
    bool ans = (lang == ukr) ? userInput::getUkrAnswer() : userInput::getEngAnswer();
    if (ans) {
        question(root->yes);
    } else {
        question(root->no);
    }
}

void thinkingGame::play() {
    files.readFromFile(treeRoot);
    if (lang == ukr) {
        cout << "Загадайте тварину, я спробую її вгадати. Натисніть enter, щоб розпочати";
    } else {
        cout << "Think of animal, I try to guess it for you! Tap enter to start";
    }
    cin.get();
    question(treeRoot);
    files.writeToFile(treeRoot);
}