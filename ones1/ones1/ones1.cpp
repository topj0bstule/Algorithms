#include <iostream>
#include <cmath>

static unsigned long long int factorial(int n) {
    if (n < 0) throw std::invalid_argument("Не может быть строка отрицательной длины!");
    unsigned long long sum = 1;
    while (n > 1) {
        sum *= n;
        sum = sum % (1000000007);
        n--;
    }
    return sum;
}

unsigned long long int calcInvDown(long long int denominator, long long int pow, long long int mod) {
    long long int result = 1;
    while (pow > 0) {
        if (pow % 2 == 1) result = (result * denominator) % mod;
        denominator = (denominator * denominator) % mod;
        pow /= 2;
    }
    return result;
}

static unsigned long long int calcStrings(int n, int k) {
    if (k > n) return 0;
    else return (factorial(n) * calcInvDown((factorial(k) * factorial(n - k)) % (1000000007), 1000000005, 1000000007)) % (1000000007);
}

int main()
{
    setlocale(LC_ALL, "rus");
    int n;
    std::cin >> n;
    int k;
    std::cin >> k;
    std::cout << calcStrings(n, k);
    return 0;
}