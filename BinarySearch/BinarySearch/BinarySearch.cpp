#include <iostream>
#include <fstream>
using namespace std;

bool findEl(int* MassiveNumbers, int kolvoNumbers, int numberForFinding) {
    int left = 0;
    int right = kolvoNumbers - 1;
    int mid = left + (right - left) / 2;
    while (left <= right) {
        if (MassiveNumbers[mid] == numberForFinding) return true;
        else if (MassiveNumbers[mid] > numberForFinding) right = mid - 1;
        else if (MassiveNumbers[mid] < numberForFinding) left = mid + 1;
        mid = left + (right - left) / 2;
    }
    return false;
}
int findIndexFirstHigherOrEqual(int* MassiveNumbers, int kolvoNumbers, int numberForFinding) {
    int left = 0;
    int right = kolvoNumbers - 1;
    int mid = left + (right - left) / 2;
    while (left <= right) {
        if (MassiveNumbers[mid] == numberForFinding || MassiveNumbers[mid] > numberForFinding) right = mid - 1;
        else if (MassiveNumbers[mid] < numberForFinding) left = mid + 1;
        mid = left + (right - left) / 2;
    }
    return mid;
}
int findIndexFirstHigher(int* MassiveNumbers, int kolvoNumbers, int numberForFinding) {
    int left = 0;
    int right = kolvoNumbers - 1;
    int mid = left + (right - left) / 2;
    while (left <= right) {
        if (MassiveNumbers[mid] == numberForFinding || MassiveNumbers[mid] < numberForFinding) left = mid + 1;
        else if (MassiveNumbers[mid] > numberForFinding) right = mid - 1;
        mid = left + (right - left) / 2;
    }
    return mid;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int kolvoNumbers;
    cin >> kolvoNumbers;
    int* MassiveNumbers = new int[kolvoNumbers];
    for (int i = 0; i < kolvoNumbers; i++) cin >> MassiveNumbers[i];
    int kolvoRequests;
    cin >> kolvoRequests;
    int* MassiveNumbersRequests = new int[kolvoRequests];
    for (int i = 0; i < kolvoRequests; i++) cin >> MassiveNumbersRequests[i];

    for (int i = 0; i < kolvoRequests; i++) {
        cout << findEl(MassiveNumbers, kolvoNumbers, MassiveNumbersRequests[i]) << " " << findIndexFirstHigherOrEqual(MassiveNumbers, kolvoNumbers, MassiveNumbersRequests[i]) << " " << findIndexFirstHigher(MassiveNumbers, kolvoNumbers, MassiveNumbersRequests[i]);
        if (i != kolvoRequests - 1) cout << "\n";
    }
    delete[] MassiveNumbers;
    delete[] MassiveNumbersRequests;
    return 0;
}