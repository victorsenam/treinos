#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 41;
const int K = 80003;
const int S = 40001;

int n, f;
int turn;
int visi[N][K];
int status[N];
int visi2[N];
bool memo[N][K];
int v[N];

int pd (int i, int s) {
    if (i == n) return (s == f);
    
    if (visi[i][s+S] == turn) return memo[i][s+S];
    visi[i][s+S] = turn;
    if (visi2[i] != turn) status[i] = 0;
    visi2[i] = turn;
    
    int st = 0;
    if (pd(i+1, s-v[i])) st |= 2;
    if (pd(i+1, s+v[i])) st |= 1;
    status[i] |= st;
    memo[i][s+S] = !!st;
    return memo[i][s+S];
}

int main () {
    while (scanf("%d %d", &n, &f) != EOF && n) {
        bool r = (f < 0);
        if (r) f = -f;

        for (int i = 0; i < n; i++)
            scanf("%d", v+i);

        ++turn;
        if (!pd(0, 0))
            printf("*\n");
        else { 
            for (int i = 0; i < n; i++) {
                if (status[i] == 3)
                    putchar('?');
                else if ((status[i] == 1)^r)
                    putchar('+');
                else
                    putchar('-');
            }
            putchar('\n');
        }
    }
}
