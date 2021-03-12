/*
 *小扣出去秋游，途中收集了一些红叶和黄叶，他利用这些叶子初步整理了一份秋叶收藏集 leaves， 字符串 leaves 仅包含小写字符 r 和 y， 其中字符 r 表示一片红叶，字符 y 表示一片黄叶。
 *出于美观整齐的考虑，小扣想要将收藏集中树叶的排列调整成「红、黄、红」三部分。每部分树叶数量可以不相等，但均需大于等于 1。每次调整操作，小扣可以将一片红叶替换成黄叶或者将一片黄叶替换成红叶。请问小扣最少需要 *多少次调整操作才能将秋叶收藏集调整完毕。
 */

#include <iostream>
#include <string.h>
#include <limits.h>
#include <vector>

using std::string;
using std::vector;

int MIN(int x, int y) {
    if (x < y) {
        return x;
    } else {
        return y;
    }
}

int minimumOperations(string leaves) {
    int len = leaves.length();
    int dp[3][len];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < len; j++) {
            dp[i][j] = 0;
        }
    }
    if (leaves[0] == 'y') dp[0][0] += 1;
    if (leaves[1] == 'r') {
        dp[1][1] = dp[0][0] + 1;
    } else {
        dp[1][1] = dp[0][0];
    }
    if (leaves[2] == 'y') {
        dp[2][2] = dp[1][1] + 1;
    } else {
        dp[2][2] = dp[1][1];
    }
    for (int i = 1; i < len; i++) {
        if (leaves[i] == 'y') {
            dp[0][i] = dp[0][i-1] + 1;
        } else {
            dp[0][i] = dp[0][i-1];
        }
        if (i >= 2) {
            if (leaves[i] == 'r') {
                dp[1][i] = MIN(dp[0][i-1], dp[1][i-1]) + 1;
            } else {
                dp[1][i] = MIN(dp[0][i-1], dp[1][i-1]);
            }   
        }
        if (i >= 3) {
            if (leaves[i] == 'y') {
                dp[2][i] = MIN(dp[1][i-1], dp[2][i-1]) + 1;
            } else {
                dp[2][i] = MIN(dp[1][i-1], dp[2][i-1]);
            }
        }
    }
    return dp[2][len-1];
}

//leetcode answer
int minimumOperations_2(string leaves) {
    int n = leaves.size();
    vector<vector<int>> f(n, vector<int>(3));
    f[0][0] = (leaves[0] == 'y');
    f[0][1] = f[0][2] = f[1][2] = INT_MAX;
    for (int i = 1; i < n; ++i) {
        int isRed = (leaves[i] == 'r');
        int isYellow = (leaves[i] == 'y');
        f[i][0] = f[i - 1][0] + isYellow;
        f[i][1] = MIN(f[i - 1][0], f[i - 1][1]) + isRed;
        if (i >= 2) {
            f[i][2] = MIN(f[i - 1][1], f[i - 1][2]) + isYellow;
        }
    }
    return f[n - 1][2];
}

int main() {
    int num = minimumOperations("ryrryyrrrrryyyyyryrrryyyyrrryryrrryyryyryryyryrryyryrryrrryyyyyyrrrryryyyryyryyyyyryyryrryryyyryyy");
    //int num = minimumOperations("yry");
    printf("%d\n", num);
    return 0;
}
