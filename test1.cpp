#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

class QuestionAsker {
public:
    void ask(const string& animal, const unordered_map<string, unordered_set<string>>& animals, const unordered_map<string, unordered_set<string>>& keywords, int language) {
        string question;
        if (language == 2) {
            cout << "\nЗадайте своє запитання: ";
        } else {
            cout << "\nAsk your question: ";
        }
        getline(cin, question);

        for (const auto& [key, keys] : keywords) {
            for (const auto& _key : keys) {
                if (strstr(question.c_str(), _key.c_str()) != nullptr) {
                    if (animals.at(animal).count(key) > 0) {
                        if (language == 2) {
                            cout << "\nТак." << endl;
                        } else {
                            cout << "\nYes." << endl;
                        }
                    } else {
                        if (language == 2) {
                            cout << "\nНі." << endl;
                        } else {
                            cout << "\nNo." << endl;
                        }
                    }
                    return;
                }
            }
        }

        if (language == 2) {
            cout << "\nНезрозуміле запитання. Спробуйте знову." << endl;
        } else {
            cout << "\nSorry, I don't understand the question. Please try again." << endl;
        }
    }
};

class Guesser {
public:
    bool guess(const string& animal, int language) {
        if (language == 2) {
            cout << "\nВаше припущення: ";
        } else {
            cout << "\nYour guess: ";
        }
        string guess;
        getline(cin, guess);

        char guessArr[100];
        strcpy(guessArr, guess.c_str());
        for (size_t i = 0; i < strlen(guessArr); i++) {
            guessArr[i] = tolower(guessArr[i]);
        }

        char animalArr[100];
        strcpy(animalArr, animal.c_str());
        for (size_t i = 0; i < strlen(animalArr); i++) {
            animalArr[i] = tolower(animalArr[i]);
        }

        if (strcmp(guessArr, animalArr) == 0) {
            if (language == 2) {
                cout << "\nВітаю! Ви вгадали тварину: " << animal << "!" << endl;
            } else {
                cout << "\nCongratulations! You guessed the animal: " << animal << "!" << endl;
            }
            return true; 
        } else {
            if (language == 2) {
                cout << "\nНеправильно." << endl;
            } else {
                cout << "\nIncorrect." << endl;
            }
            return false; 
        }
    }
};

class AnimalGame {
private:
    unordered_map<string, unordered_set<string>> animals;
    unordered_map<string, unordered_set<string>> keywords;
    int language;

public:
    AnimalGame(int lang) : language(lang) {
        initAnimals();
        initKeywords();
    }

    void play() {
        srand(time(nullptr));
        auto iter = animals.begin();
        advance(iter, rand() % animals.size());
        const string& animal = iter->first;

        if (language == 2) {
            cout << "Комп'ютер загадав тварину. Спробуйте вгадати, яку саме." << endl;
        } else {
            cout << "The computer guessed the animal. Try to guess which animal the computer chose." << endl;
        }

        string input;
        while (true) {
            if (language == 2) {
                cout << "\nЩо ви хочете зробити? (1 - задати запитання, 2 - зробити припущення, 3 - завершити гру): ";
            } else {
                cout << "\nWhat do you want to do? (1 - ask a question, 2 - make a guess, 3 - end the game): ";
            }
            getline(cin, input);

            if (input == "1") {
                QuestionAsker asker;
                asker.ask(animal, animals, keywords, language);
            } else if (input == "2") {
                Guesser guesser;
                bool guessed_correctly = guesser.guess(animal, language);
                if (guessed_correctly) {
                    break; // Виходимо з циклу, якщо вгадано
                }
            } else if (input == "3") {
                if (language == 2) {
                    cout << "\nГра завершена. Дякую за участь!" << endl;
                } else {
                    cout << "\nThe game is over. Thank you for playing!" << endl;
                }
                return;
            } else {
                if (language == 2) {
                    cout << "Неправильний вибір. Введіть 1, щоб задати запитання, 2, щоб зробити припущення, або 3, щоб завершити гру." << endl;
                } else {
                    cout << "Invalid choice. Enter 1 to ask a question, 2 to make a guess, or 3 to end the game." << endl;
                }
            }
        }
    }

private:
void initAnimals() {
    if (language == 2) { 
        animals = {
            {"Тигр", {"хижак", "смугастий", "велика", "гострі зуби", "кігті", "швидка", "ссавець"}},
            {"Лев", {"хижак", "грива", "велика", "кігті", "гострі зуби", "швидка", "стадна"}},
            {"Лисиця", {"хижак", "хитра", "рижа", "невелика", "швидка", "ссавець", "розумний", "гострі зуби"}},
            {"Корова", {"травоїдна", "домашня", "має роги", "молоко", "велика", "ссавець", "пасеться", "довгі роги"}},
            {"Жираф", {"травоїдна", "довга шия", "високий", "плямиста шкіра", "довгі ноги", "має роги"}},
            {"Верблюд", {"ссавець", "травоїдний", "великий", "довга шия", "горби", "пустельний"}},
            {"Краб", {"водний", "ракоподібний", "панцир", "хижак", "клешні", "морський"}},
            {"Каракатиця", {"хижак", "водний", "щупальця", "м'яке тіло", "випускає чорнило", "змінює колір"}},
            {"Кальмар", {"хижак", "водний", "швидкий", "м'яке тіло", "щупальця", "випускає чорнило", "безхребетний", "велика", "змінює колір"}},
            {"Орел", {"хижак", "літає", "гострий зір", "велика", "кігті", "швидка", "перната"}},
            {"Ластівка", {"всеїдна", "літає", "швидка", "невелика", "перната", "гніздиться", "мігрує"}},
            {"Папуга", {"травоїдна", "літає", "яскраве пір'я", "розмовляє", "невелика", "перната", "розумний"}},
            {"Кіт", {"ссавець", "домашня", "вуса", "нічний зір", "м'яке хутро", "кігті", "соціальна", "нявкає"}},
            {"Собака", {"домашня", "нюх", "гавкає", "вірна", "соціальна", "ссавець", "м'яке хутро"}},
            {"Кролик", {"травоїдна", "домашня", "довгі вуха", "швидка", "моркву", "м'яке хутро", "стрибає"}}
        };
    } else { 
        animals = {
            {"Tiger", {"predator", "striped", "big", "sharp teeth", "claws", "fast", "mammal"}},
            {"Lion", {"predator", "mane", "big", "claws", "sharp teeth", "fast", "social"}},
            {"Fox", {"predator", "cunning", "red", "small", "fast", "mammal", "intelligent", "sharp teeth"}},
            {"Cow", {"herbivore", "domestic", "has horns", "milk", "big", "mammal", "grazing", "long horns"}},
            {"Giraffe", {"herbivore", "long neck", "tall", "spotted skin", "long legs", "has horns"}},
            {"Camel", {"mammal", "herbivore", "big", "long neck", "humps", "desert"}},
            {"Crab", {"aquatic", "crustacean", "shell", "predator", "claws", "marine"}},
            {"Cuttlefish", {"predator", "aquatic", "tentacles", "soft body", "ink", "changes color"}},
            {"Squid", {"predator", "aquatic", "fast", "soft body", "tentacles", "ink", "invertebrate", "big", "changes color"}},
            {"Eagle", {"predator", "flies", "sharp vision", "big", "claws", "fast", "feathered"}},
            {"Swallow", {"omnivore", "flies", "fast", "small", "feathered", "nests", "migrates"}},
            {"Parrot", {"herbivore", "flies", "bright feathers", "talks", "small", "feathered", "intelligent"}},
            {"Cat", {"mammal", "domestic", "whiskers", "night vision", "soft fur", "claws", "social", "meows"}},
            {"Dog", {"domestic", "sense of smell", "barks", "loyal", "social", "mammal", "soft fur"}},
            {"Rabbit", {"herbivore", "domestic", "long ears", "fast", "carrots", "soft fur", "hops"}}
        };
    }
}


 void initKeywords() {
    if (language == 2) { 
        keywords = {
            {"хижак", {"хижак", "Хижак", "хижий", "Хижий", "хижа", "Хижа"}},
            {"травоїдна", {"травоїдна", "Травоїдна", "травоїдний", "Травоїдний"}},
            {"всеїдна", {"всеїдна", "Всеїдна", "всеїдний", "Всеїдний"}},
            {"літає", {"літає", "Літає", "літаючий", "Літаючий", "літаюча", "Літаюча", "вміє літати", "Вміє літати", "може літати", "Може літати"}}, 
            {"водний", {"водний", "Водний",  "водна", "Водна", "живе у воді", "Живе у воді" }},
            {"домашня", {"домашня", "Домашня", "домашній", "Домашній", "свійська", "Свійська"}},
            {"смугастий", {"смугастий", "Смугастий", "смугаста", "Смугаста",  "зі смугами", "Зі смугами", "в смужках", "В смужках"}},
            {"велика", {"велика", "Велика", "великий", "Великий"}},
            {"гострі зуби", {"гострі зуби", "Гострі зуби", "гострі ікла", "Гострі ікла"}},
            {"кігті", {"кігті", "Кігті","кігтями", "Кігтями"}},
            {"швидка", {"швидка", "Швидка", "швидкий", "Швидкий", "швидко", "Швидко"}},
            {"ссавець", {"ссавець", "Ссавець", "ссавці", "Ссавці"}},
            {"грива", {"грива", "Грива", "гриву", "Гриву", "гриви", "Гриви", "з гривою", "З гривою"}},
            {"стадна", {"стадна", "Стадна", "стадний", "Стадний", "в стаді", "В стаді", "стадом", "Стадом"}},
            {"хитра", {"хитра", "Хитра", "хитрий", "Хитрий"}},
            {"рижа", {"рижа", "Рижа", "рижий", "Рижий", "рудий", "Рудий", "руда", "Руда"}},
            {"невелика", {"невелика", "Невелика", "невеликий", "Невеликий", "маленька", "Маленька", "малий", "Малий"}},
            {"розумний", {"розумний", "Розумний", "розумна", "Розумна"}},
            {"має роги", {"має роги", "Має роги", "з рогами", "З рогами", "рогатий", "Рогатий", "рогата", "Рогата"}},
            {"молоко", {"молоко", "Молоко"}},
            {"пасеться", {"пасеться", "Пасеться", "пасти", "Пасти"}},
            {"довга шия", {"довга шия", "Довга шия", "довгу шию", "Довгу шию"}},
            {"високий", {"високий", "Високий", "висока", "Висока"}},
            {"плямиста шкіра", {"плямиста шкіра", "Плямиста шкіра", "плямистий", "Плямистий", "плямиста", "Плямиста"}},
            {"довгі ноги", {"довгі ноги", "Довгі ноги", "довгонога", "Довгонога"}},
            {"пустельний", {"пустельний", "Пустельний", "пустельна", "Пустельна", "живе в пустелі", "Живе в пустелі"}},
            {"ракоподібний", {"ракоподібний", "Ракоподібний", "ракоподібна", "Ракоподібна"}},
            {"панцир", {"панцир", "Панцир", "панцирний", "Панцирний", "панцирна", "Панцирна"}},
            {"клешні", {"клешні", "Клешні", "клешня", "Клешня", "клешню", "Клешню"}},
            {"щупальця", {"щупальця", "Щупальця", "щупалець", "Щупалець", "щупальці", "Щупальці"}},
            {"м'яке тіло", {"м'яке тіло", "М'яке тіло"}},
            {"випускає чорнило", {"випускає чорнило", "Випускає чорнило", "чорнило", "Чорнило"}},
            {"змінює колір", {"змінює колір", "Змінює колір", "змінювати колір", "Змінювати колір", "колір"}},
            {"безхребетний", {"безхребетний", "Безхребетний", "безхребетна", "Безхребетна"}},
            {"гострий зір", {"гострий зір", "Гострий зір", "зір"}},
            {"перната", {"перната", "Перната", "пернатий", "Пернатий", "з пір'ям", "З пір'ям"}},
            {"гніздиться", {"гніздиться", "Гніздиться", "гніздиться в", "Гніздиться в", "гніздо", "Гніздо"}},
            {"мігрує", {"мігрує", "Мігрує", "мігрують", "Мігрують", "мігруючий", "Мігруючий"}},
            {"яскраве пір'я", {"яскраве пір'я", "Яскраве пір'я"}},
            {"розмовляє", {"розмовляє", "Розмовляє", "говорить", "Говорить", "розмовляти", "Розмовляти"}},
            {"вуса", {"вуса", "Вуса", "вусики", "Вусики", "з вусами", "З вусами"}},
            {"нічний зір", {"нічний зір", "Нічний зір", "бачить вночі", "Бачить вночі"}},
            {"м'яке хутро", {"м'яке хутро", "М'яке хутро"}},
            {"соціальна", {"соціальна", "Соціальна", "соціальний", "Соціальний"}},
            {"нявкає", {"нявкає", "Нявкає", "мяукає", "Мяукає", "мяу", "Мяу"}},
            {"нюх", {"нюх", "Нюх", "запах", "Запах", "чутливий до запахів", "Чутливий до запахів"}},
            {"гавкає", {"гавкає", "Гавкає", "гав", "Гав", "гавкати", "Гавкати"}},
            {"вірна", {"вірна", "Вірна", "вірний", "Вірний"}},
            {"моркву", {"моркву", "Моркву", "морква", "Морква"}},
            {"довгі вуха", {"довгі вуха", "Довгі вуха", "вуха"}},
            {"стрибає", {"стрибає", "Стрибає", "стрибати", "Стрибати"}}
        };
    } else { 
        keywords = {
            {"predator", {"predator", "Predator", "predatory", "Predatory"}},
            {"herbivore", {"herbivore", "Herbivore", "herbivorous", "Herbivorous"}},
            {"omnivore", {"omnivore", "Omnivore", "omnivorous", "Omnivorous"}},
            {"flies", {"flies", "Flies", "flying", "Flying", "can fly", "Can fly"}},
            {"aquatic", {"aquatic", "Aquatic", "water-dwelling", "Water-dwelling"}},
            {"domestic", {"domestic", "Domestic", "tame", "Tame"}},
            {"striped", {"striped", "Striped", "stripes", "Stripes"}},
            {"big", {"big", "Big", "large", "Large"}},
            {"sharp teeth", {"sharp teeth", "Sharp teeth", "sharp fangs", "Sharp fangs"}},
            {"claws", {"claws", "Claws"}},
            {"fast", {"fast", "Fast", "quick", "Quick"}},
            {"mammal", {"mammal", "Mammal", "mammals", "Mammals"}},
            {"mane", {"mane", "Mane"}},
            {"social", {"social", "Social"}},
            {"cunning", {"cunning", "Cunning"}},
            {"red", {"red", "Red"}},
            {"small", {"small", "Small"}},
            {"intelligent", {"intelligent", "Intelligent"}},
            {"has horns", {"has horns", "Has horns", "horned", "Horned"}},
            {"milk", {"milk", "Milk"}},
            {"grazing", {"grazing", "Grazing"}},
            {"long neck", {"long neck", "Long neck"}},
            {"tall", {"tall", "Tall"}},
            {"spotted skin", {"spotted skin", "Spotted skin"}},
            {"long legs", {"long legs", "Long legs"}},
            {"desert", {"desert", "Desert", "desert-dwelling", "Desert-dwelling"}},
            {"crustacean", {"crustacean", "Crustacean"}},
            {"shell", {"shell", "Shell"}},
            {"claws", {"claws", "Claws"}},
            {"tentacles", {"tentacles", "Tentacles"}},
            {"soft body", {"soft body", "Soft body"}},
            {"ink", {"ink", "Ink"}},
            {"changes color", {"changes color", "Changes color"}},
            {"invertebrate", {"invertebrate", "Invertebrate"}},
            {"sharp vision", {"sharp vision", "Sharp vision"}},
            {"feathered", {"feathered", "Feathered"}},
            {"nests", {"nests", "Nests"}},
            {"migrates", {"migrates", "Migrates"}},
            {"bright feathers", {"bright feathers", "Bright feathers"}},
            {"talks", {"talks", "Talks", "speaks", "Speaks"}},
            {"whiskers", {"whiskers", "Whiskers"}},
            {"night vision", {"night vision", "Night vision"}},
            {"soft fur", {"soft fur", "Soft fur"}},
            {"meows", {"meows", "Meows", "meowing", "Meowing"}},
            {"sense of smell", {"sense of smell", "Sense of smell"}},
            {"barks", {"barks", "Barks", "barking", "Barking"}},
            {"loyal", {"loyal", "Loyal"}},
            {"carrots", {"carrots", "Carrots"}},
            {"long ears", {"long ears", "Long ears"}},
            {"hops", {"hops", "Hops", "hopping", "Hopping"}}
        };
    }
}


int main() {
    AnimalGame game(2);
    game.play();
    return 0;
}
};

