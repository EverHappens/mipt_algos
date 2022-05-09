//https://codeforces.com/group/PVbQ8eK2T4/contest/368711/submission/147378773

#include <iostream>

int getLCSLength(int n, int k, int *array1, int *array2){
    int dp[n + 1][k + 1];//knapsack dp
    for(int i = 0; i <= n; ++i){
        dp[i][0] = 0;
    }
    for(int i = 0; i <= k; ++i){
        dp[0][i] = 0;
    }
    for(int i = 1; i <= n; ++i){//greedy search with knapsack dp
        for(int j = 1; j <= k; ++j){
            if(array1[i - 1] == array2[j - 1]) dp[i][j] = dp[i-1][j-1] + 1;//greedy search
            else dp[i][j] = std::max(dp[i][j-1], std::max(dp[i-1][j], dp[i-1][j-1]));
        }
    }
    return dp[n][k];
}

int main() {
    int n;
    std::cin >> n;
    int array1[n];
    for(int i = 0; i < n; ++i){
        std::cin >> array1[i];
    }
    int k;
    std::cin >> k;
    int array2[k];
    for(int i = 0; i < k; ++i){
        std::cin >> array2[i];
    }
    std::cout << getLCSLength(n, k, array1, array2);
}
