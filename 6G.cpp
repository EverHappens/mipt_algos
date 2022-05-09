//https://codeforces.com/group/PVbQ8eK2T4/contest/371629/submission/150553198

#include <iostream>
#include <string>
#include <vector>

long long countCases(int n, int m, std::string *cities){
    long long mod = 1e9 + 7;
    long long dp[1 << n][m];
    for(int i = 0; i < (1<<n); ++i){
        for(int j = 0 ; j < m; ++j){
            dp[i][j] = 0;
        }
    }
    for (int mask = 0; mask < (1 << n); ++mask) {//1 for every non determined city mask, 0 for every other
        dp[mask][0] = 1;
        for(int i = 0; i < n; ++i){
            if((((mask & (1 << i)) >> i) == 0 & cities[i][0] == '+') || (((mask & (1 << i)) >> i) == 1 & cities[i][0] == '-')){
                dp[mask][0] = 0;
                break;
            }
        }
    }
    for (int i = 1; i < m; ++i) {//bitmask dp solution
        for (int mask = 0; mask < (1 << n); ++mask) {
            for (int bit = 0; bit <= 1; ++bit) {
                if((bit == 0 & cities[0][i] == '+') || (bit == 1 & cities[0][i] == '-')){
                    continue;
                }
                int new_mask = bit;//if new_mask == -1 then mask cant be next
                for (int j = 1; j < n; ++j) {//sum is the balance of possible -'s and +'s in 2x2
                    int sum = ((mask & (1 << j)) >> j) + ((mask & (1 << (j - 1))) >> (j - 1)) + ((new_mask & (1 << (j - 1))) >> (j - 1));
                    if (sum > 2 || sum == 0) {
                        new_mask = -1;
                        break;
                    }
                    if (sum == 1) {//check is we can restore balance
                        if (cities[j][i] == '-') {
                            new_mask = -1;
                            break;
                        }
                        new_mask += (1 << j);
                    } else if (cities[j][i] == '+') {
                        new_mask = -1;
                        break;
                    }
                }
                if (new_mask != -1){
                    dp[new_mask][i] = (dp[new_mask][i] + dp[mask][i - 1]) % mod;
                }
            }
        }
    }
    long long sum = 0;
    for (int i = 0; i < (1 << n); ++i) {//count all cases of last mask
        sum = (sum + dp[i][m - 1]) % mod;
    }
    return sum;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::string cities[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> cities[i];
    }
    std::cout << countCases(n, m, cities);
}
