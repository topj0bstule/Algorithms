#include <iostream>
#include <vector>
#include <fstream>
#include <string>

struct PotomokInterval {
    std::vector<long long int> min;
    std::vector<long long int> max;
};

int main()
{
    std::ifstream in("bst.in");

    PotomokInterval interval;
    bool ok = true;
    long long int tempZnachenie = 0;
    long long int tempPotomok = 0;
    long long int size;
    long long int max = LLONG_MAX;
    long long int min = LLONG_MIN;

    std::vector<long long int> znacheniya;
    std::string tempString;

    in >> size;
    in >> tempZnachenie;
    znacheniya.push_back(tempZnachenie);
    interval.min.push_back(min);
    interval.max.push_back(max);
    for (long long int i = 1; i < size; i++) {
        in >> tempZnachenie;
        znacheniya.push_back(tempZnachenie);
        in >> tempPotomok;
        in >> tempString;
        if (tempString == "L") {
            max = znacheniya[tempPotomok - 1];
            min = interval.min[tempPotomok - 1];
        }
        else {
            min = znacheniya[tempPotomok - 1];
            max = interval.max[tempPotomok - 1];
        }
        if (znacheniya[i] >= max || znacheniya[i] < min)
        {
            ok = false;
            break;
        }
        interval.max.push_back(max);
        interval.min.push_back(min);
    }
    in.close();
    std::ofstream out("bst.out");
    if (ok == true)
        out << "YES";
    else
        out << "NO";
    out.close();
}