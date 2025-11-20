#include <iostream>
#include <queue>
#include <fstream>

struct Point {
    short x = -1;
    short y = -1;
    bool visitedFirstTime = 1;
    bool visitedSecondTime = 0;
    short sum = 0;

    Point(short x_, short y_) {
        this->x = x_;
        this->y = y_;
    }
    Point() {
        this->x = -1;
        this->y = -1;
    }
};

short bfs(short** matr, short n, short m, bool** visited, Point& point1, Point& point2) {
    std::queue<Point> vertexes;
    Point temp;
    short dx[8] = { 1, 2, 1, 2, -1, -2, -1, -2 };
    short dy[8] = { 2, 1, -2, -1, 2, 1, -2, -1 };

    vertexes.push(point1);
    if (point1.x == point2.x && point1.y == point2.y) return 0;

    while (!vertexes.empty()) {
        temp = vertexes.front();
        vertexes.pop();
        visited[temp.x][temp.y] = 1;
        if (temp.visitedSecondTime) {
            temp.sum++;
            temp.visitedFirstTime = 0;
            temp.visitedSecondTime = 0;
            vertexes.push(temp);
            continue;
        }
        for (size_t i = 0; i < 8; i++) {
            Point next_temp(temp.x + dx[i], temp.y + dy[i]);
            next_temp.sum = temp.sum;

            if (next_temp.x == point2.x && next_temp.y == point2.y) {
                if (matr[next_temp.x][next_temp.y] == 0) return ++next_temp.sum;
                else if (matr[next_temp.x][next_temp.y] == 1) return ++++next_temp.sum;
            }
            if (next_temp.x >= 0 && next_temp.y >= 0 && next_temp.x < n && next_temp.y < m && !visited[next_temp.x][next_temp.y]) {
                if (matr[next_temp.x][next_temp.y] == 0) {
                    visited[next_temp.x][next_temp.y] = 1;
                    next_temp.visitedFirstTime = 0;
                    next_temp.visitedSecondTime = 0;
                    next_temp.sum++;
                    vertexes.push(next_temp);
                }
                else if (matr[next_temp.x][next_temp.y] == 1) {
                    if (next_temp.visitedFirstTime && !temp.visitedSecondTime) {
                        visited[temp.x][temp.y] = 1;
                        next_temp.visitedFirstTime = 0;
                        next_temp.visitedSecondTime = 1;
                        next_temp.sum++;
                        vertexes.push(next_temp);
                    }
                }
            }
        }
    }
    return -1;
}

int main()
{
    std::ifstream in("in.txt");
    if (!in.is_open()) {
        std::cerr << "Failed opening file.\n";
        return -1;
    }
    short n, m;
    short x1, y1, x2, y2;
    in >> n >> m;
    short** matr = new short* [n];
    for (size_t i = 0; i < n; i++) matr[i] = new short[m];
    for (size_t i = 0; i < n; i++) for (size_t j = 0; j < m; j++) in >> matr[i][j];
    in >> x1 >> y1 >> x2 >> y2;
    x1--; x2--; y1--; y2--;
    in.close();
    bool** visited = new bool* [n];
    for (size_t i = 0; i < n; i++) visited[i] = new bool[m];
    for (size_t i = 0; i < n; i++) for (size_t j = 0; j < m; j++) visited[i][j] = 0;

    Point point1(x1, y1);
    Point point2(x2, y2);

    short result = bfs(matr, n, m, visited, point1, point2);

    std::ofstream out("out.txt");
    if (!out.is_open()) {
        std::cerr << "Failed opening file.\n";
        return -1;
    }
    if (x1 == x2 && y1 == y2) out << 0;
    else if (result != -1) out << result;
    else out << "No";
    out.close();

    return 0;
}