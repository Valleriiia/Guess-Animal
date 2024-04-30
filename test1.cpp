#include <iostream>
using namespace std;

int factorial(int n) {

    if (n == 0) {
        return 1;
    }

    return n * factorial(n - 1);
}

int main() {
    int number;
    cout << "Введіть ціле число: ";
    cin >> number;


    if (number < 0) {
        cout << "Факторіал не визначений для негативних чисел" << endl;
    } else {
        int result = factorial(number);
        cout << "Факторіал " << number << " дорівнює: " << result << endl;
    }

    return 0;
}
