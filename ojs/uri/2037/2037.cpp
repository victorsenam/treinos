#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 12;
const int M = 107;

char str[N][M];
int n;
int p[N];

int main () {
    while (scanf("%d", &n) != EOF && n != -1) {
        int cnt = 0;
        for (int i = 1; i < n; i++) {
            p[i] = 0;
            scanf(" %s", str[i]);
            cnt += strlen(str[i]);
        }

        while (cnt) {
            int s = 0;
            for (int i = 1; i < n; i++) {
                if (str[i][p[i]] == '\0') continue;
                else if (str[i][p[i]] == '1') {
                    putchar('1'+i);
                    p[i]++;
                    cnt--;
                    continue;
                } 
                int j = str[i][p[i]] - '1';
                if (str[j][p[j]] == '1'+i) {
                    p[i]++;
                    p[j]++;
                    cnt -= 2;
                }
            }
        }
        putchar('\n');
    }
}
