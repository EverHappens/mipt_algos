//https://codeforces.com/group/PVbQ8eK2T4/contest/374347/submission/150947919

#include <iostream>
#include <vector>
#include <set>

void dfs(int v, std::vector<int> *next, int *pre, int *post, bool *visited, int &t) {
    pre[v] = ++t;
    visited[v] = true;
    for (int c: next[v]) {
        if (!visited[c]) dfs(c, next, pre, post, visited, t);
    }
    post[v] = ++t;
}

bool isAncestor(int left, int right, int *pre, int *post) {
    if ((pre[left] < pre[right]) && (post[left] > post[right])) return true;
    else return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    int n;
    std::cin >> n;
    std::vector<int> next[n + 1];
    int root = 0;
    for (int i = 1; i <= n; ++i) {
        int temp;
        std::cin >> temp;
        if (temp) next[temp].push_back(i);
        else root = i;
    }
    int pre[n + 1];
    for (int i = 0; i <= n; ++i) {
        pre[i] = 0;
    }
    int post[n + 1];
    for (int i = 0; i <= n; ++i) {
        post[i] = 0;
    }
    bool visited[n + 1];
    for (int i = 0; i <= n; ++i) {
        visited[i] = false;
    }
    int t = 0;
    dfs(root, next, pre, post, visited, t);//count in preorder traversal
    int k;
    std::cin >> k;
    for (int i = 0; i <k; ++i) {
        int left, right;
        std::cin >> left >> right;
        if (isAncestor(left, right, pre, post)) std::cout << "1\n";
        else std::cout << "0\n";
    }
}
