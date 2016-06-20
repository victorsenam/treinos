#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define lld I64d
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 207;

int cost[26];
int c;
int l;
int n, m;
char str[N];
char s;

void fail (){ 
    printf("-1\n");
    exit(0);
}

int main () {
    scanf("%d %d", &n, &m);

    scanf(" %s", str);
    for (int i = 0; i < 26; i++)
        cost[i] = 1000;
    
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &l, &c);

        for (int j = 0; j < l; j++) {
            scanf(" %c", &s);
            DEBUG("[%c]\n", s);
            cost[s-'a'] = min(cost[s-'a'], c);
        }
    }

    int res = 0;
    for (int i = 0; i < n; i++)  {
        if (cost[str[i]-'a'] == 1000) {
            DEBUG("%c\n", str[i]);
            fail();
        }

        res += cost[str[i]-'a'];
    }
    printf("%d\n", res);
}
