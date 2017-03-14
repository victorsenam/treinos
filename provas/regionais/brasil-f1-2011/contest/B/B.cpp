#include <bits/stdc++.h>

using namespace std;

#define N 31

int n, m;
int a;
int cnt;
char c;
int bt[N][2];

int main () {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i <= 30; i++)
            bt[i][0] = bt[i][1] = 0;

        for (int i = 0; i < n; i++) {
            scanf("%d %c", &a, &c);
            bt[a-30][(c=='E')]++;
        }
        
        cnt = 0;
        for (int i = 0; i <= 30; i++) {
            cnt += min(bt[i][0], bt[i][1]);
        }
        printf("%d\n", cnt);
    }
}
