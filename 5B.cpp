//https://codeforces.com/group/PVbQ8eK2T4/contest/368711/submission/147819305

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

void findSubsequence(int *sequence, int n, std::list<int> &output) {
    int INF = 2147483647;
    int indices[n + 1];
    int prev[n + 1];
    int decreasing[n + 1];
    for (int i = 0; i <= n; ++i) {
        decreasing[i] = INF;
    }
    decreasing[0] = -INF;
    for (int i = 0; i < n; ++i) {//searching for subsequence, saving their indices
        int index = upper_bound(decreasing.begin(), decreasing.end(), sequence[i]) - decreasing.begin();
        if (decreasing[index - 1] <= sequence[i] && sequence[i] <= decreasing[index]) {
            decreasing[index] = sequence[i];
            indices[index] = i;
            prev[i] = indices[index - 1];
        }
    }
    int maxIndex = lower_bound(decreasing.begin(), decreasing.end(), INF) - decreasing.begin() -
                   1;//finding the end of subsequence
    int curr = indices[maxIndex];
    std::cout << maxIndex << '\n';
    output.push_back(curr + 1);
    for (int i = maxIndex - 2; i >= 0; --i) {//finding indices of elements
        curr = prev[curr];
        output.push_front(curr + 1);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int n;
    std::cin >> n;
    int sequence[n];
    for (int i = 0; i < n; ++i) {
        int temp;
        std::cin >> temp;
        sequence[i] = -temp;
    }
    std::list<int> ans(0);
    findSubsequence(sequence, n, ans);
    for (int an: ans) {
        std::cout << an << " ";
    }
}
