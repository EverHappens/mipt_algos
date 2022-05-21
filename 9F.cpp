#include <iostream>
#include <vector>

bool dfs(std::vector<int> *graph, bool *visited, int *match, int v) {
    if (!visited[v]) {
        visited[v] = true;
        for (int node: graph[v]) {
            if (match[node] == -1 || dfs(graph, visited, match, match[node])) {
                match[node] = v;
                return true;
            }
        }
    }
    return false;
}

int kuhn(std::vector<int> *graph, int n) {
    int cnt = 0;
    int match[n];
    for (int i = 0; i < n; ++i) {
        match[i] = -1;
    }
    bool visited[n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            visited[j] = false;
        }
        if (dfs(graph, visited, match, i)) ++cnt;
    }
    return n - cnt;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<int> graph[n];
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a - 1].push_back(b - 1);
    }
    std::cout << kuhn(graph, n);
}
