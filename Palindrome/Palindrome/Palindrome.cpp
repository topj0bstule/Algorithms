#include <iostream>
#include <string>
#include <fstream>
#include <vector>

struct Pal {
    size_t size;
    std::string str;
    Pal(size_t size_) : size(size_) {
        this->str = "";
    }
    Pal(size_t size_, std::string str_): size(size_), str(str_){}
    Pal() {
        this->size = 0;
        this->str = "";
    }
};

size_t max(size_t a, size_t b) {
    return a > b ? a : b;
}

Pal maxPal(std::string str) {
    size_t size1 = str.length();
    if (size1 > 2) {
        Pal pal;
        short** resultsMatr = new short* [size1];
        for (size_t i = 0; i < size1; i++)
            resultsMatr[i] = new short[size1];
        for (size_t i = 0; i < size1; i++)
            for (size_t j = 0; j < size1; j++)
                resultsMatr[i][j] = 0;
        for (size_t i = 0; i < size1; i++)
            resultsMatr[i][i] = 1;
        for (size_t len = 2; len <= size1; ++len) {
            for (size_t i = 0; i <= size1 - len; ++i) {
                size_t j = len + i - 1;
                if (str[i] == str[j])
                    if (len == 2)
                        resultsMatr[i][j] = 2;
                    else 
                        resultsMatr[i][j] = resultsMatr[i + 1][j - 1] + 2;
                else
                    resultsMatr[i][j] = max(resultsMatr[i + 1][j], resultsMatr[i][j - 1]);
            }
        }
        size_t i = 0;
        size_t j = size1 - 1;
        std::vector<char> palindrom;
        while (i <= j) {
            if (str[i] == str[j]) {
                palindrom.push_back(str[i]);
                i++;
                j--;
            }
            else {
                if (resultsMatr[i + 1][j] == resultsMatr[i][j] && i + 1 < size1) i++;
                else j--;
            }
        }
        std::string result;
        if (!palindrom.empty()) {
            std::string right(palindrom.rbegin(), palindrom.rend());
            std::string left(palindrom.begin(), palindrom.end());
            if (resultsMatr[0][size1 - 1] % 2 == 0)
                result = left + right;
            else {
                right.erase(0, 1);
                result = left + right;
            }

        }
        pal.size = resultsMatr[0][size1 - 1];
        pal.str = result;
        for (size_t i = 0; i < size1; i++)
            delete[] resultsMatr[i];
        delete[] resultsMatr;
        return pal;
    }
    else if (size1 == 2)
        if (str[0] == str[1]) return Pal(2, str);
        else return Pal(1, str.erase(1));
    else if (size1 == 1) return Pal(1, str);
    else return Pal(0);
}

int main()
{
    std::string string;
    std::ifstream in("input.txt");
    in >> string;
    in.close();
    Pal pal = maxPal(string);
    std::ofstream out("output.txt");
    out << pal.size << "\n";
    out << pal.str;
    out.close();
}