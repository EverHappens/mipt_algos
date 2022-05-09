//https://codeforces.com/group/PVbQ8eK2T4/contest/377095/submission/154232666

#include <iostream>
#include <vector>
#include <queue>

long long dijkstra(int n, std::vector<std::vector<std::pair<long long, long long>>> &adj, int from, int to) {
    long long INF = 1e18;
    std::priority_queue<std::pair<long long, long long>> q;
    bool visited[n + 1];
    for (int i = 0; i <= n; ++i) {
        visited[i] = false;
    }
    long long distance[n + 1];
    for (int i = 0; i <= n; ++i) {
        distance[i] = INF;
    }
    distance[from] = 0;
    q.push({0, from});
    while (!q.empty()) {
        long long v = q.top().second;
        q.pop();
        if (visited[v]) continue;
        visited[v] = true;
        for (std::pair<long long, long long> node: adj[v]) {
            if (distance[node.first] > distance[v] + node.second) {
                distance[node.first] = distance[v] + node.second;
                q.push({-distance[node.first], node.first});
            }
        }
    }
    if (distance[to] == INF) {
        return -1;
    } else {
        return distance[to];
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    long long n, m;
    std::cin >> n >> m;
    long long from, to;
    std::cin >> from >> to;
    std::vector<std::vector<std::pair<long long, long long>>> adj(n + 1);//graph
    for (long long i = 0; i < m; ++i) {
        long long a, b, c;
        std::cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    std::cout << dijkstra(n, adj, from, to);
}
