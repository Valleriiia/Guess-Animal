#include "thinkingGame.h"

// Конструктор класу thinkingGame
    thinkingGame::thinkingGame(Language l) {
        lang = l;
        treeRoot = NULL;
        string filename = (lang == ukr) ? "animals_tree_ukr.txt" :  "animals_tree_eng.txt";
        files = fileManager(filename);
    }

// Додає нове питання та нову тварину до ігрового дерева
void thinkingGame::addQuestion(treeNode* &node) {
    // Пропонує користувачу ввести нову тварину
    cout << ((lang == ukr) ? "Яку тварину ви загадали?" : "What's your animal?") << endl;
    cin.ignore();
    string newAnimal = userInput::inputAnimal(lang);
    cin.clear();

    // Просить користувача ввести питання, яке відрізняє нову тварину від тварини поточного вузла дерева
    if (lang == ukr) {
        cout << "Введіть питання таке, щоб для " << newAnimal << " відповідь на нього була так, а для " << node->text << " - ні" << endl;
    } else {
        cout << "Enter a question such that the answer to it for " << newAnimal << " is yes, and for " << node->text << " - no" << endl;
    }

    // Перевіряє чи речення не занадто коротке
    string question = userInput::inputQuestion();
    size_t minLength = (lang == ukr) ? 16 : 10;
    while (question.length() < minLength) {
       cout << ((lang == ukr) ? "Питання занадто коротке. Спробуйте ще раз." : "The question is too short. Try again.") << endl;
       question = userInput::inputQuestion();
    }

    // Створює нові вузли для гілок "так" і "ні"
    treeNode *yes = new treeNode();
    yes->text = newAnimal;
    treeNode *no = new treeNode();
    no->text = node->text;

    // Оновлює поточний вузол новим питанням та дочірніми вузлами
    node->text = question;
    node->yes = yes;
    node->no = no;
    // Підтверджує, що нову тварину було додано
    cout << ((lang == ukr) ? "Вашу тварину було успішно додано" : "Your animal was added successful") << endl;
}

// Ставить користувачу питання та рекурсивно пересувається по ігровому дереву в залежності від відповіді користувача
void thinkingGame::question(treeNode *root) {
    // Якщо поточний вузол є листковим, запитує користувачачи його тварина співпадає з твариною вузла
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

    // Ставить користувачу питтанч з поточного вузла
    cout << root->text << endl;
    bool ans = (lang == ukr) ? userInput::getUkrAnswer() : userInput::getEngAnswer();

    // Рекурсивно проходить "так" або "ні" гілку, в залежності від відповіді користувача
    if (ans) {
        question(root->yes);
    } else {
        question(root->no);
    }
}

// Починаєнову гру
void thinkingGame::play() {
    // Зчитує ігорове дерево з файлу
    files.readFromFile(treeRoot);

    // Просить користувача загадати тварину та почати гру
    if (lang == ukr) {
        cout << "Загадайте тварину, я спробую її вгадати. Натисніть enter, щоб розпочати";
    } else {
        cout << "Think of animal, I try to guess it for you! Tap enter to start";
    }
    cin.get();

    // Починає ставити питання
    question(treeRoot);

    // Зберігає оновлене ігрове дерево до файлу
    files.writeToFile(treeRoot);
}