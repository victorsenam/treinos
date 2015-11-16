#include <bits/stdc++.h>

using namespace std;

const int N = 20;

typedef long long int num;

vector<int> ini;
map<vector<int>, int> memo[N][2];
map<vector<int>, int>::iterator it;
char str[N];

int dp (int i, bool pre, vector<int> s) {
    it = memo[i][pre].find(s);
    if (it != memo[i][pre].end())
        return *it;
    
    if (pre) {
        for (int i = str[i]; i >= '0'; i--):w
    } else {
    }
}

int solve (int i, bool pre) {
    int r = memo[i][pre][ini];

    printf("%d", r);
    ini[r]--;
    solve(i+1, pre&&(r==str[i]));
}

int main () {
    while (scanf("%s", str) != EOF) {
        for (int i = 0; i < 19; i++) {
            memo[i][0].clear();
            memo[i][1].clear();
        }

        ini.clear();
        for (int i = 0; i < 10; i++)
            ini.push_back(2);

        if (dp(0, 1, ini) >= 0) {
            sol(0, 1);
        } else {
            for (int i = 0; i || str[i+1]; i++)
                printf("%d", 9-(i/2));
        }
        printf("\n");
    }
}
