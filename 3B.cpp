#include <iostream>
#include <vector>

struct FenwickTree {
    std::vector<int> bit;
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit = std::vector<int>(n, 0);
    }

    int sum(int r) {
        int sm = 0;
        int prev = r;
        for (; r >= 0; r = (r & (r + 1)) - 1) {
            if ((r & (r + 1)) % 2 == 0) {
                sm += bit[r];
            } else sm -= bit[r];
            prev = r;
        }
        return sm;
    }

    int sum(int l, int r) {
        if(l%2 == 0){
            return sum(r) - sum(l - 1);
        } else return sum(l - 1) - sum(r);
    }

    void add(int ind, int delta) {
        int init = ind;
        for (; ind < n; ind = ind | (ind + 1)) {
            if (init % 2 == 0) {
                bit[ind] += delta;
            } else bit[ind] -= delta;
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    std::cin >> n;
    int a[n];
    FenwickTree fen(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        fen.add(i, a[i]);
    }
    int m;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        int ord, l, r;
        std::cin >> ord >> l >> r;
        if (ord == 0) {
            --l;
            fen.add(l, r - a[l]);
            a[l] = r;
        } else {
            --l, --r;
            std::cout << fen.sum(l, r) << '\n';
        }
    }
    return 0;
}