//https://codeforces.com/group/PVbQ8eK2T4/contest/368711/submission/147905473

#include <iostream>

long long getPeacefulNum(int n) {
    long long dp[n + 1][n + 1];//knapsack dp
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = 0;
        }
    }
    for(int i = 0; i <= n; ++i) {
        dp[i][i] = 1;//fill starting cells
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = i / 2 + 1; j <= i; ++j) {
            for (int k = 2 * j; k <= n - i; ++k) {
                dp[i + k][k] += dp[i][j];
            }
        }
    }
    long long num = 0;
    for (int i = 0; i <= n; ++i) {
        num += dp[n][i];
    }
    return num;
}


int main() {
    long long n;
    std::cin >> n;
    std::cout << getPeacefulNum(n);
}
