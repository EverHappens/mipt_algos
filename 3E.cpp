#include <iostream>

struct Node {
    long long val = 0;
    Node *c[2];

    Node() {
        c[0] = c[1] = NULL;
    }

    void upd(long long ind, long long v, long long L = 0, long long R = 1e9) { // add v
        if (L == ind && R == ind) {
            val += v;
            return;
        }
        long long M = (L + R) / 2;
        if (ind <= M) {
            if (!c[0]) c[0] = new Node();
            c[0]->upd(ind, v, L, M);
        } else {
            if (!c[1]) c[1] = new Node();
            c[1]->upd(ind, v, M + 1, R);
        }
        val = 0;
        for (long long i = 0; i < 2; i++) {
            if (c[i]) val += c[i]->val;
        }
    }

    long long query(long long lo, long long hi, long long L = 0, long long R = 1e9 - 1) { // query sum of segment
        if (hi < L || R < lo) return 0;
        if (lo <= L && R <= hi) return val;
        long long M = (L + R) / 2;
        long long res = 0;
        if (c[0]) res += c[0]->query(lo, hi, L, M);
        if (c[1]) res += c[1]->query(lo, hi, M + 1, R);
        return res;
    }
};

int main() {
    long long n;
    std::cin >> n;
    Node node;
    for (long long i = 0; i < n; ++i) {
        char ord;
        long long val;
        std::cin >> ord >> val;
        if (ord == '+') {
            node.upd(val, val);
        } else {
            std::cout << node.query(0, val) << '\n';
        }
    }
}