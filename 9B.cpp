#include <iostream>

struct Node {
    int a;
    int b;
    int weight;

    Node() = default;

    Node(int x, int y, int w) : a(x), b(y), weight(w) {}
};

bool operator<(const Node &left, const Node &right) {
    return left.weight < right.weight;
}

int getSet(int *parent, int v) {
    if (parent[v] == v) return v;
    else{
        parent[v] = getSet(parent, parent[v]);
        return parent[v];
    }
}

void unite(int *cnt, int *parent, int v, int u) {
    if (cnt[v] < cnt[u]) {
        parent[v] = u;
    } else {
        parent[u] = v;
        if (cnt[u] == cnt[v]) {
            ++cnt[u];
        }
    }
}

int kruskall(Node *nodes, int n, int m) {
    int cnt[n];
    int parent[n];
    for (int i = 0; i < n; ++i) {
        cnt[i] = 0;
        parent[i] = i;
    }
    int ansWeight = 0;

    for (int i = 0; i < m; ++i) {
        int set1 = getSet(parent, nodes[i].a);
        int set2 = getSet(parent, nodes[i].b);
        if (set1 != set2) {
            unite(cnt, parent, set1, set2);
            ansWeight += nodes[i].weight;
        }
    }
    return ansWeight;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    Node nodes[m];
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        nodes[i] = Node(a - 1, b - 1, c);
    }
    std::sort(nodes, nodes + m);
    int cnt[n];
    int parent[n];
    for (int i = 0; i < n; ++i) {
        cnt[i] = 0;
        parent[i] = i;
    }
    std::cout << kruskall(nodes, n, m);
}
