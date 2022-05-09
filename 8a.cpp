//https://codeforces.com/group/PVbQ8eK2T4/contest/377095/submission/154150357

#include <iostream>
#include <vector>
#include <queue>

void findPath(std::pair<int, int> &start, std::pair<int, int> &end, std::vector<std::pair<int, int>> &path) {
    int dx[] = {-2, -1, 1, 2, -2, -1, 1, 2};
    int dy[] = {1, 2, -2, -1, -1, -2, 2, 1};
    std::pair<int, int> prev[8][8];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            prev[i][j] = {-1, -1};
        }
    }
    bool visited[8][8];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            visited[i][j] = false;
        }
    }
    path.push_back(end);
    std::queue<std::pair<int, int>> que;
    que.push(start);
    while (!que.empty()) {//simple bfs because we dont have that many cases on 8x8
        std::pair<int, int> curr = que.front();
        que.pop();
        for (int i = 0; i < 8; ++i) {
            int x = curr.first + dx[i];
            int y = curr.second + dy[i];
            if (x >= 0 && x < 8 && y >= 0 && y < 8 && prev[x][y].first == -1 && prev[x][y].second == -1) {//add cases
                que.push({x, y});
                prev[x][y] = {curr.first, curr.second};
            }
        }
    }
    while (path[path.size() - 1] != start) {//fill path array backwards
        path.push_back(prev[path[path.size() - 1].first][path[path.size() - 1].second]);
    }
}

int main() {
    std::string from, to;
    std::cin >> from >> to;
    std::pair<int, int> start = {from[0] - 'a', from[1] - '0' - 1};
    std::pair<int, int> end = {to[0] - 'a', to[1] - '0' - 1};
    std::vector<std::pair<int, int>> path(0);
    findPath(start, end, path);
    for (int i = path.size() - 1; i >= 0; --i) {//we have filled path array backwards
        std::cout << (char) ('a' + path[i].first) << path[i].second + 1 << '\n';
    }
}
