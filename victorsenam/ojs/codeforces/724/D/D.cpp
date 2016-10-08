#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e5+7;
const int K = 300;

char str[N];
int m;
int n;
int cnt[K];
int crc;

int solve (char curr) {
    int cut = -1;
    int ls = -1;
    int res = 0;
    
    for (int i = 0; i < n; i++) {
        if (str[i] < curr)
            cut = i;
        else if (str[i] == curr)
            ls = i;
            
        if (i - cut >= m) {
            if (i - ls >= m) return n+1;
            cut = ls;
            res++;
        }
    }
    return res;
}

int main () {
    scanf("%d", &m);
    scanf(" %s", str);
    n = strlen(str);

    for (int i = 0; i < K; i++)
        cnt[i] = 0;

    for (int i = 0; i < n; i++)
        cnt[str[i]]++;

    char ans;
    for (ans = 'a'; ans <= 'z' && (crc = solve(ans)) == n+1; ans++);

    for (char k = 'a'; k < ans; k++) {
        for (int i = 0; i < cnt[k]; i++)
            putchar(k);
    }

    for (int i = 0; i < crc; i++)
        putchar(ans);
}
