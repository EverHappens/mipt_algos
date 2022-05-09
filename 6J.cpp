//https://codeforces.com/group/PVbQ8eK2T4/contest/371629/submission/149964821

#include <iostream>
#include <vector>
#include <algorithm>

long long countCases(int n, int m) {
    long long isNeighbour[1 << m][1 << m];//array for mask compatability
    for (int i = 0; i < (1 << m); ++i) {
        for (int j = 0; j < (1 << m); ++j) {
            isNeighbour[i][j] = 1;
            for (int k = 0; k < m - 1; ++k) {
                if ((i & (1 << k)) == 0 && (j & (1 << k)) == 0 && (i & (1 << (k + 1))) == 0 &&
                    (j & (1 << (k + 1))) == 0) {
                    isNeighbour[i][j] = 0;
                    break;
                } else if ((i & (1 << k)) != 0 && (j & (1 << k)) != 0 && (i & (1 << (k + 1))) != 0 &&
                           (j & (1 << (k + 1))) != 0) {
                    isNeighbour[i][j] = 0;
                    break;
                }
            }
        }
    }
    long long dp[n][1 << m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (1 << m); ++j) {
            dp[i][j] = 0;
        }
    }
    for (int i = 0; i < (1 << m); ++i) {
        dp[0][i] = 1;
    }
    for (int i = 1; i < n; ++i) {//bitmask dp solution, we have already checked for mask compatability
        for (int j = 0; j < (1 << m); ++j) {
            for (int k = 0; k < (1 << m); ++k) {
                dp[i][j] += dp[i - 1][k] * isNeighbour[k][j];//check if mask can be transitioned
            }
        }
    }
    long long sum = 0;
    for (int i = 0; i < (1 << m); ++i) {
        sum += dp[n - 1][i];//count all cases
    }
    return sum;
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    if (n < m) std::swap(n, m);//optimization
    std::cout << countCases(n, m);
}
