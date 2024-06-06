#include "GuessingGame.h"
#include "QuestionAsker.h"
#include "Guesser.h"

// Конструктор класу
GuessingGame::GuessingGame(Language l) {
        lang = l;
        initAnimals();
        initKeywords();
    }

// Починає нову гру
void GuessingGame::play() {
    // Обирає рандомну тварину зі списку
    srand(time(nullptr));
    auto iter = animals.begin();
    advance(iter, rand() % animals.size());
    const string& animal = iter->first;
    if (lang == ukr) {
        cout << "\nКомп'ютер загадав тварину. Спробуйте вгадати, яку саме." << endl;
    } else {
        cout << "\nThe computer guessed the animal. Try to guess which animal the computer chose." << endl;
    }

    int input;

    // Входить у цикл, щоб неодноразово запитувати у користувача введення, доки він не вгадає правильно або не вирішить вийти
    while (true) {
        // Виводить під меню режиму гри
        if (lang == ukr) {
            cout << "\nЩо ви хочете зробити? (1 - задати запитання, 2 - зробити припущення, 3 - завершити гру): ";
        } else {
            cout << "\nWhat do you want to do? (1 - ask a question, 2 - make a guess, 3 - end the game): ";
        }
        cin >> input;

        // Перевіряє правельність введення
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << ((lang == ukr) ? "Помилка введення! Спробуйте ще раз" : "Invalid input! Try again") << endl;
            continue;
        }
        cin.ignore();

        // Опрацьовує введення користувача
        switch (input) {
            case 1: {
                // Переходить до питання
                QuestionAsker asker;
                asker.ask(animal, animals, keywords, lang);
                break;
            }
            case 2: {
                // Переходить до припущення
                Guesser guesser;
                bool correct = guesser.guess(animal, lang);
                if (correct) {
                    return; 
                }
                break;
            }
            case 3: {
                // Виходить з режиму гри
                if (lang == ukr) {
                    cout << "\nГра завершена. Чекаємо на вас знову!" << endl;
                } else {
                    cout << "\nThe game is over. We are waiting for you again!" << endl;
                }
                return;
            }
            default: {
                if (lang == ukr) {
                    cout << "\nНекоректний вибір. Оберіть 1 для запитання, 2 для припущення, або 3 для завершення гри." << endl;
                } else {
                    cout << "\nInvalid choice. Choose 1 for asking, 2 for guessing, or 3 to end the game." << endl;
                }
            }
        }
    }
}

// Ініціалізує меп тварин
void GuessingGame::initAnimals() {
    if (lang == ukr) {
        animals = {
            {"Тигр", {"ссавець", "хижак", "смугастий", "велика", "гострі зуби", "кігті", "швидка"}},
            {"Лев", {"ссавець", "хижак", "грива", "велика", "кігті", "гострі зуби", "швидка", "стадна"}},
            {"Лисиця", {"ссавець", "хижак", "хитра", "рижа", "невелика", "швидка", "розумний", "гострі зуби"}},
            {"Корова", {"ссавець", "травоїдна", "домашня", "має роги", "молоко", "велика", "пасеться", "довгі роги"}},
            {"Жираф", {"ссавець", "травоїдна", "довга шия", "високий", "плямиста шкіра", "довгі ноги", "має роги"}},
            {"Верблюд", {"ссавець", "травоїдна", "великий", "довга шия", "горби", "пустельний"}},
            {"Краб", {"ракоподібний", "всеїдний", "водний", "панцир", "хижак", "клешні", "морський"}},
            {"Каракатиця", {"молюск", "хижак", "водний", "щупальця", "м'яке тіло", "випускає чорнило", "змінює колір"}},
            {"Кальмар", {"молюск", "хижак", "водний", "швидкий", "м'яке тіло", "щупальця", "випускає чорнило", "безхребетний", "велика", "змінює колір"}},
            {"Орел", {"птах", "хижак", "літає", "гострий зір", "велика", "кігті", "швидка", "перната"}},
            {"Ластівка", {"птах", "всеїдний", "літає", "швидка", "невелика", "перната", "гніздиться", "мігрує"}},
            {"Папуга", {"птах", "травоїдна", "літає", "яскраве пір'я", "розмовляє", "невелика", "перната", "розумний"}},
            {"Кіт", {"ссавець", "хижак", "домашня", "вуса", "нічний зір", "м'яке хутро", "кігті", "соціальна", "нявкає"}},
            {"Собака", {"ссавець", "всеїдний", "домашня", "нюх", "гавкає", "вірна", "соціальна", "м'яке хутро"}},
            {"Кролик", {"ссавець", "травоїдна", "домашня", "довгі вуха", "швидка", "моркву", "м'яке хутро", "стрибає"}}
        };
    } else {
        animals = {
            {"Tiger", {"mammal", "predator", "striped", "big", "sharp teeth", "claws", "fast"}},
            {"Lion", {"mammal", "predator", "mane", "big", "claws", "sharp teeth", "fast", "social"}},
            {"Fox", {"mammal", "predator", "cunning", "red", "small", "fast", "smart", "sharp teeth"}},
            {"Cow", {"mammal", "herbivore", "domestic", "has horns", "milk", "big", "grazes", "long horns"}},
            {"Giraffe", {"mammal", "herbivore", "long neck", "tall", "spotted skin", "long legs", "has horns"}},
            {"Camel", {"mammal", "herbivore", "big", "long neck", "humps", "desert"}},
            {"Crab", {"crustacean", "omnivore", "aquatic", "shell", "predator", "claws", "marine"}},
            {"Cuttlefish", {"mollusk", "predator", "aquatic", "tentacles", "soft body", "ink", "changes color"}},
            {"Squid", {"mollusk", "predator", "aquatic", "fast", "soft body", "tentacles", "ink", "invertebrate", "big", "changes color"}},
            {"Eagle", {"bird", "predator", "flies", "sharp vision", "big", "claws", "fast", "feathered"}},
            {"Swallow", {"bird", "omnivore", "flies", "fast", "small", "feathered", "nests", "migrates"}},
            {"Parrot", {"bird", "herbivore", "flies", "bright feathers", "talks", "small", "feathered", "smart"}},
            {"Cat", {"mammal", "predator", "domestic", "whiskers", "night vision", "soft fur", "claws", "social", "meows"}},
            {"Dog", {"mammal", "omnivore", "domestic", "smell", "barks", "loyal", "social", "soft fur"}},
            {"Rabbit", {"mammal", "herbivore", "domestic", "long ears", "fast", "carrots", "soft fur", "jumps"}}
        };
    }
}

// Ініціалізує меп ключових слів
void GuessingGame::initKeywords() {
    if (lang == ukr) {
        keywords = {
            {"хижак", {"хижак", "Хижак", "хижий", "Хижий", "хижа", "Хижа"}},
            {"травоїдна", {"травоїдна", "Травоїдна", "травоїдний", "Травоїдний"}},
            {"всеїдна", {"всеїдна", "Всеїдна", "всеїдний", "Всеїдний"}},
            {"літає", {"літає", "Літає", "літаючий", "Літаючий", "літаюча", "Літаюча", "вміє літати", "Вміє літати", "може літати", "Може літати"}}, 
            {"водний", {"водний", "Водний",  "водна", "Водна", "живе у воді", "Живе у воді" }},
            {"домашня", {"домашня", "Домашня", "домашній", "Домашній", "свійська", "Свійська"}},
            {"смугастий", {"смугастий", "Смугастий", "смугаста", "Смугаста",  "зі смугами", "Зі смугами", "в смужках", "В смужках"}},
            {"велика", {"велика", "Велика", "великий", "Великий"}},
            {"гострі зуби", {"гострі зуби", "Гострі зуби", "ікла", "Ікла"}},
            {"кігті", {"кігті", "Кігті","кігтями", "Кігтями"}},
            {"швидка", {"швидка", "Швидка", "швидкий", "Швидкий", "швидко", "Швидко"}},
            {"ссавець", {"ссавець", "Ссавець", "ссавці", "Ссавці"}},
            {"грива", {"грива", "Грива", "гриву", "Гриву", "гриви", "Гриви", "з гривою", "З гривою"}},
            {"стадна", {"стадна", "Стадна", "стадний", "Стадний", "в стаді", "В стаді", "стадом", "Стадом"}},
            {"хитра", {"хитра", "Хитра", "хитрий", "Хитрий"}},
            {"рижа", {"рижа", "Рижа", "рижий", "Рижий", "рудий", "Рудий", "руда", "Руда"}},
            {"невелика", {"невелика", "Невелика", "невеликий", "Невеликий", "маленька", "Маленька", "малий", "Малий"}},
            {"розумний", {"розумний", "Розумний", "розумна", "Розумна"}},
            {"має роги", {"роги", "Роги", "з рогами", "З рогами", "рогатий", "Рогатий", "рогата", "Рогата"}},
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
            {"гострий зір", {"гострий зір", "Гострий зір"}},
            {"перната", {"перната", "Перната", "пернатий", "Пернатий", "з пір'ям", "З пір'ям", "пір'я", "Пір'я"}},
            {"гніздиться", {"гніздиться", "Гніздиться", "гніздиться в", "Гніздиться в", "гніздо", "Гніздо"}},
            {"мігрує", {"мігрує", "Мігрує", "мігрують", "Мігрують", "мігруючий", "Мігруючий"}},
            {"яскраве пір'я", {"яскраве пір'я", "Яскраве пір'я"}},
            {"розмовляє", {"розмовляє", "Розмовляє", "говорить", "Говорить", "розмовляти", "Розмовляти"}},
            {"вуса", {"вуса", "Вуса", "вусики", "Вусики", "з вусами", "З вусами"}},
            {"нічний зір", {"нічний зір", "Нічний зір", "бачить вночі", "Бачить вночі"}},
            {"м'яке хутро", {"м'яке хутро", "М'яке хутро"}},
            {"соціальна", {"соціальна", "Соціальна", "соціальний", "Соціальний"}},
            {"нявкає", {"нявкає", "Нявкає", "мяукає", "Мяукає", "Няв", "няв"}},
            {"нюх", {"нюх", "Нюх", "запах", "Запах", "чутливий до запахів", "Чутливий до запахів"}},
            {"гавкає", {"гавкає", "Гавкає", "гав", "Гав", "гавкати", "Гавкати"}},
            {"вірна", {"вірна", "Вірна", "вірний", "Вірний"}},
            {"моркву", {"моркву", "Моркву", "морква", "Морква"}},
            {"довгі вуха", {"довгі вуха", "Довгі вуха", "вуха"}},
            {"стрибає", {"стрибає", "Стрибає", "стрибати", "Стрибати"}},
            {"птах", {"птах", "Птах", "птахи", "Птахи", "перната", "Перната", "пернатий", "Пернатий"}},
            {"ракоподібний", {"ракоподібний", "Ракоподібний"}},
            {"молюск", {"молюск", "Молюск", "молюски", "Молюски", "безхребетний", "Безхребетний"}}
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
            {"sharp teeth", {"sharp teeth", "Sharp teeth", "fangs", "Fangs", "teeth", "Teeth"}},
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
            {"meows", {"meows", "Meows", "meowing", "Meowing", "meow", "Meow",}},
            {"sense of smell", {"sense of smell", "Sense of smell"}},
            {"barks", {"barks", "Barks", "barking", "Barking", "bark", "Bark"}},
            {"loyal", {"loyal", "Loyal"}},
            {"carrots", {"carrots", "Carrots"}},
            {"long ears", {"long ears", "Long ears"}},
            {"hops", {"hops", "Hops", "hopping", "Hopping", "jump", "Jump", "jumping", "Jumping"}},
            {"bird", {"bird", "Bird", "birds", "Birds"}},
            {"crustacean", {"crustacean", "Crustacean"}},
            {"mollusk", {"mollusk", "Mollusk", "mollusks", "Mollusks"}}
        };
    }
}