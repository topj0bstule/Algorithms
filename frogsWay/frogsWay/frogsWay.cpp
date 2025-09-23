#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void maxSumOfMosquitoes(vector<unsigned short>& MassiveNumbers, int currentIndex, long long int& sum, vector<int>& FrogsWay) {
    if (MassiveNumbers.size() == 2 || MassiveNumbers.size() == 0) {
        sum = -1;
        return;
    }
    if (MassiveNumbers.size() == 1) {
        sum = MassiveNumbers[0];
        FrogsWay.push_back(1);
        return;
    }
    vector<int> prev(MassiveNumbers.size(), -1);
    vector <long long int> sums(MassiveNumbers.size(), -1);
    while (currentIndex <= MassiveNumbers.size() - 1) {
        if (currentIndex == 0) {
            sums[currentIndex] = (long long int)MassiveNumbers[currentIndex];
            prev[0] = -1;
            currentIndex++;
        }
        else if (currentIndex == 1) {
            sums[currentIndex] = -1;
            prev[1] = -1;
            currentIndex++;
        }
        else if (currentIndex == 2) {
            sums[currentIndex] = (long long int)(sums[currentIndex - 2] + MassiveNumbers[currentIndex]);
            prev[2] = 0;
            currentIndex++;
        }
        else {
            if (sums[currentIndex - 3] > sums[currentIndex - 2]) {
                sums[currentIndex] = (long long int)(sums[currentIndex - 3] + MassiveNumbers[currentIndex]);
                prev[currentIndex] = currentIndex - 3;
                currentIndex++;
            }
            else {
                sums[currentIndex] = (long long int)(sums[currentIndex - 2] + MassiveNumbers[currentIndex]);
                prev[currentIndex] = currentIndex - 2;
                currentIndex++;
            }
        }
    }
    sum = sums[MassiveNumbers.size() - 1];
    int pos = MassiveNumbers.size() - 1;
    while (pos > -1) {
        FrogsWay.push_back(pos + 1);
        pos = prev[pos];
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int kolvoWaterLilys;
    cin >> kolvoWaterLilys;
    vector<unsigned short> MassiveNumbers;
    vector<int> FrogsWay;
    unsigned short currentNumber = 0;
    for (int i = 0; i < kolvoWaterLilys; i++) {
        cin >> currentNumber;
        MassiveNumbers.push_back(currentNumber);
    }
    vector <long long int> sums(MassiveNumbers.size(), -1);
    long long int sum = 0;
    maxSumOfMosquitoes(MassiveNumbers, 0, sum, FrogsWay);
    cout << sum << "\n";
    while (!FrogsWay.empty()) {
        cout << FrogsWay.back();
        FrogsWay.pop_back();
        if (!FrogsWay.empty()) cout << " ";
    }
    return 0;
}