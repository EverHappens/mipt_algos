//https://codeforces.com/group/PVbQ8eK2T4/contest/374347/submission/151018906

#include <iostream>
#include <vector>

int dfs(int v, std::vector<int> *graph, int *visited, std::vector<int> &cycle) {
    visited[v] = 1;
    int start = -1;
    for (int node: graph[v]) {
        if (visited[node] == 1) {//found an element of cycle
            cycle.push_back(v);
            start = node;
            break;
        }
        if (visited[node] == 0) {//looking for cycle
            start = dfs(node, graph, visited, cycle);
            if (start != -1) {//if is in cycle
                cycle.push_back(v);
                break;
            }
        }
    }
    visited[v] = 2;
    if (v == start) return -1;//if in the start of the cycle
    return start;
}

void findCycle(int n, std::vector<int> &cycle, std::vector<int> *graph, int *visited) {
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) dfs(i, graph, visited, cycle);//look for cycles from every node
        if (!cycle.empty()) break;
    }
    std::reverse(cycle.begin(), cycle.end());
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> graph[n + 1];
    for (int i = 0; i < k; ++i) {
        int left, right;
        std::cin >> left >> right;
        graph[left].push_back(right);
    }
    int visited[n + 1];//0 - was not visited, 1 - was visited, 2 - was visited, definitely no cycles there
    for (int i = 0; i <= n; ++i) {
        visited[i] = 0;
    }
    std::vector<int> cycle(0);
    findCycle(n, cycle, graph, visited);
    if (cycle.empty()) std::cout << "NO";
    else {
        std::cout << "YES\n";
        for (int node: cycle) {
            std::cout << node << " ";
        }
    }
}
