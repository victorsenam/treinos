#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

const int N = 300008;

num ans;
num val;
num v[N];
num it[N];
num qtd[N];
int a, n, m;
char c;
num mask;
char str[N];

int main () {
    freopen("hyperdrome.in", "r", stdin);
    freopen("hyperdrome.out", "w", stdout);
    while (scanf("%d", &n) != EOF) {
        mask = 0;
        scanf(" %s", str);
        v[0] = 0;
        for (int i = 0; i < n; i++) {
            c = str[i];
            if (c >= 'a' && c <= 'z')
                a = c - 'a';
            else
                a = c - 'A' + 26;
            
            mask = (mask^(1llu<<a));
            v[i+1] = mask;
        }
        sort(v, v+n+1);
        
        it[0] = 0;
        qtd[0] = 1;
        m = 1;
        for (int i = 1; i <= n; i++) {
            if (v[i] == v[i-1])
                qtd[m-1]++;
            else {
                it[m] = v[i];
                qtd[m] = 1;
                m++;
            }
        }

        ans = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < 52; j++) {
                val = (int) (lower_bound(it, it+m, ((1llu<<j)^it[i])) - it);
                if (val < m && it[val] == (((1llu<<j)^it[i])))
                    ans += qtd[i]*qtd[val];
            }
            ans += qtd[i]*(qtd[i]-1);
        }
            
        printf("%I64u\n", ans/2);
    }
}
