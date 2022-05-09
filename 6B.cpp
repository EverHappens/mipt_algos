//https://codeforces.com/group/PVbQ8eK2T4/contest/371629/submission/150550918

#include <iostream>

long long fastPow(long long base, long long pow, long long mod) {
    long long out = base;
    --pow;
    while (pow > 0) {
        if (pow % 2 == 1) out = (out * base) % mod;
        pow >>= 1;
        base = (base * base) % mod;
    }
    return out;
}

std::string montyProb(int n, long long *part){
    long long mod = 1e9 + 7;
    long long up = 2, down = 1;
    bool even = false;
    for (int i = 0; i < n; ++i) {//state is just matrix exponentiation
        up = (fastPow(up, part[i], mod)) % mod;
        if(part[i] % 2 == 0) even = true;//we may count odd cases
    }
    up = (up * 500000004) % mod;//div by 2
    down = up;//all cases
    up = ((up + ((even) ? 1 : -1))*333333336) % mod;//div by 3 and add magic
    return std::to_string(up) + '/' + std::to_string(down);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    int n;
    std::cin >> n;
    long long part[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> part[i];
    }
    std::cout << montyProb(n, part);
}
