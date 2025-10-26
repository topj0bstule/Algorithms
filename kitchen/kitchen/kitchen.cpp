#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

struct Primanka {
    int x = -1;
    int y = -1;

    bool operator ==(const Primanka& other) const{
        if ((this->x != other.x) || (this->y != other.y))
            return 0;
        return 1;
    }
};

struct Tarakan {
    int timeToDie = -1;
    int time = 0;
    int x = -1;
    int y = -1;
    int eatenPoison = 0;
    bool isDied = false;
    Primanka goal;

    Primanka assignNearestPrimanka(vector<Primanka>& primankas) {
        int result = INT_MAX;
        for (int i = 0; i < primankas.size(); i++) {
            if ((abs(primankas[i].x - this->x) + abs(primankas[i].y - this->y)) < result) {
                result = abs(primankas[i].x - this->x) + abs(primankas[i].y - this->y);
                this->goal = primankas[i];
            }
            if ((abs(primankas[i].x - this->x) + abs(primankas[i].y - this->y)) == result) {
                if ((primankas[i].x < this->goal.x) || (primankas[i].x == this->goal.x && primankas[i].y < this->goal.y)) {
                    this->goal = primankas[i];
                }
            }
        }
        return this->goal;
    }
    void updateTime() {
        this->time++;
        if (this->timeToDie > 0) this->timeToDie--;
        if (this->timeToDie == 0) this->isDied = true;
    }
    void moveToPrimanka() {
        if (this->x > this->goal.x) this->x--;
        else if (this->x < this->goal.x) this->x++;
        else {
            if (this->y > this->goal.y) this->y--;
            else if (this->y < this->goal.y) this->y++;
        }
    }
};

void readInput(vector<Tarakan>& tarakans, vector<Primanka>& primankas, short int n, short int m) {
    Tarakan tempTarakan;
    Primanka tempPrimanka;
    for (int i = 0; i < n; i++) {
        cin >> tempTarakan.x >> tempTarakan.y;
        tarakans.push_back(tempTarakan);
    }
    for (int i = 0; i < m; i++) {
        cin >> tempPrimanka.x >> tempPrimanka.y;
        primankas.push_back(tempPrimanka);
    }
}

void simulate(vector<Tarakan>& tarakans, vector<Primanka>& primankas, int a, int t) {
    for (int i = 0; i < tarakans.size(); i++) {
        tarakans[i].assignNearestPrimanka(primankas);
    }
    while (primankas.size() > 0) {
        for (int i = 0; i < tarakans.size(); i++) {
            if (!tarakans[i].isDied) {
                tarakans[i].updateTime();
                tarakans[i].moveToPrimanka();
                if (tarakans[i].x == tarakans[i].goal.x && tarakans[i].y == tarakans[i].goal.y) {
                    tarakans[i].eatenPoison++;

                    if (tarakans[i].eatenPoison >= a && tarakans[i].timeToDie == -1) {
                        tarakans[i].timeToDie = t;
                    }
                    auto it = find(primankas.begin(), primankas.end(), tarakans[i].goal);
                    if (it != primankas.end()) primankas.erase(it);
                    for (int j = 0; j < tarakans.size(); j++) {
                        if (tarakans[j].goal == tarakans[i].goal && !tarakans[j].isDied) {
                            tarakans[j].assignNearestPrimanka(primankas);
                        }
                    }
                }
            }
        }
    }
}

void printResults(vector<Tarakan>& tarakans) {
    for (int i = 0; i < tarakans.size(); i++) {
        if (tarakans[i].timeToDie > 0) {
            tarakans[i].time += tarakans[i].timeToDie;
            tarakans[i].isDied = 1;
        }
        if (tarakans[i].timeToDie == -1) tarakans[i].time = -1;
        cout << tarakans[i].time << "\n";
    }
}

int main() {
    short int n, m, a;
    int t, w, h;
    cin >> n >> m >> a >> t;
    cin >> w >> h;
    vector<Tarakan> tarakans;
    vector<Primanka> primankas;
    
    readInput(tarakans, primankas, n, m);
    simulate(tarakans, primankas, a, t);
    printResults(tarakans);

    return 0;
}
/*
3 3 1 2
4 4
0 0
0 1
1 1
2 2
3 3
4 4
*/