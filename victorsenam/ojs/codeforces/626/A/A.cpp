#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 207;

int ch[N], cv[N];
int n;
char c;

int main () {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf(" %c", &c);
        ch[i] = ch[i-1];
        cv[i] = cv[i-1];
        if (c == 'U')
            ch[i]++;
        else if (c == 'D')
            ch[i]--;
        else if (c == 'R')
            cv[i]++;
        else
            cv[i]--;
    }

    int cnt = 0;
    for (int i = 0; i <= n; i++)
        for (int j = i+1; j <= n; j++)
            cnt += (!(ch[j]-ch[i]) && !(cv[j]-cv[i]));

    printf("%d\n", cnt);
}
