#include <iostream>
#include <vector>
#include <stack>

struct Answer {
    short result;
    std::stack<short> indisex1;
    std::stack<short> indisex2;
    Answer() {
        this->result = 0;
        this->indisex1 = std::stack<short>();
        this->indisex2 = std::stack<short>();
    }
    Answer(short result_): result(result_) {}
    Answer(short result_, std::stack<short> indisex1_, std::stack<short> indisex2_): result(result_), indisex1(indisex1_), indisex2(indisex2_){}
};

short max(short a, short b) {
    return a > b ? a : b;
}

Answer maxLen(std::vector<short> &arr1, std::vector<short> &arr2) {
    if (arr1.size() > 1) {
        Answer answer;
        short** resultsMatr = new short* [arr1.size() + 1];
        for (size_t i = 0; i < arr1.size() + 1; i++) {
            resultsMatr[i] = new short[arr2.size() + 1];
        }
        for (size_t i = 0; i < arr1.size() + 1; i++) 
            resultsMatr[i][0] = 0;
        for (size_t i = 0; i < arr2.size() + 1; i++)
            resultsMatr[0][i] = 0;
        for (size_t i = 1; i < arr1.size() + 1; i++) {
            for (size_t j = 1; j < arr2.size() + 1; j++) {
                if (arr1[i - 1] == arr2[j - 1])
                    resultsMatr[i][j] = resultsMatr[i - 1][j - 1] + 1;
                else 
                    resultsMatr[i][j] = max(resultsMatr[i][j - 1], resultsMatr[i - 1][j]);
            }
        }
        size_t i = arr1.size();
        size_t j = arr2.size();
        answer.result = resultsMatr[i][j];
        while (i > 0 && j > 0) {
            if (arr1[i - 1] == arr2[j - 1]) {
                answer.indisex1.push(i - 1);
                answer.indisex2.push(j - 1);
                i--;
                j--;
            }
            else if (resultsMatr[i][j] == resultsMatr[i - 1][j] ) i--;
            else j--;
        }
        for (int i = 0; i < arr1.size() + 1; i++)
            delete[] resultsMatr[i];
        delete[] resultsMatr;
        return answer;
    }
    else if (arr1.size() == 1) return arr1[0] == arr2[0] ? Answer(1, std::stack<short>({0}), std::stack<short>({0})) : Answer(0);
    else return Answer(0);
}

int main()
{
    short lenSequence;
    std::cin >> lenSequence;
    std::vector<short> arr1;
    std::vector<short> arr2;
    short temp = 0;
    for (size_t i = 0; i < lenSequence; i++) {
        std::cin >> temp;
        arr1.push_back(temp);
    }
    for (size_t i = 0; i < lenSequence; i++) {
        std::cin >> temp;
        arr2.push_back(temp);
    }
    Answer answer = maxLen(arr1, arr2); 
    int arrSize = answer.indisex1.size();
    std::cout << answer.result;
    if(!answer.indisex1.empty()){
        std::cout << "\n";
        for (int i = 0; i < arrSize; i++) {
            if (i != arrSize - 1) std::cout << answer.indisex1.top() << " ";
            else std::cout << answer.indisex1.top();
            answer.indisex1.pop();
        }
        std::cout << "\n";
        for (int i = 0; i < arrSize; i++) {
            if (i != arrSize - 1) std::cout << answer.indisex2.top() << " ";
            else std::cout << answer.indisex2.top();
            answer.indisex2.pop();
        }
    }
}