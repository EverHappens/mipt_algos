//https://codeforces.com/group/PVbQ8eK2T4/contest/374347/submission/151601954

#include <iostream>
#include <vector>

void euler(int v, std::vector<std::vector<int>> &graph, std::vector<int> &ans, int n) {
    for(int i = 1; i <= n; ++i){
        if(graph[v][i] == 1){
            graph[v][i] = 0;
            euler(i, graph, ans, n);
        }
    }
    ans.push_back(v);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    int n, start;
    std::cin >> n >> start;
    std::vector<std::vector<int>> graph(n+1, std::vector<int>(n+1, 0));//can't pass modified 2d arrays to functions,
    // so we'll have to use dynamic structures anyway
    for (int i = 1; i <= n; ++i) {//we need to find complete traversal on graphs' complement
        for (int j = 1; j <= n; ++j) {
            int way;
            std::cin >> way;
            if (i != j && way == 0) graph[i][j] = 1;//if there is no edge
        }
    }
    std::vector<int> ans(0);
    euler(start, graph, ans, n);
    for(int i = ans.size() - 1; i > 0; --i){
        std::cout << ans[i] << " " << ans[(i - 1 + ans.size()) % ans.size()] << '\n';
    }
}
