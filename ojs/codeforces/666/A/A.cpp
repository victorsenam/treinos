#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 10007;
set<string> s;
char str[N];
char aux[3];

bool visi[N][2][2];

void pd (int n, bool p2, bool p3) {
    if (n < 4) return;

    if (visi[n][p2][p3]) return;
    visi[n][p2][p3] = 1;

    if (p2 && n-2 > 4) {
        for (int i = 0; i < 2; i++)
            aux[i] = str[n-2+i];
        aux[2] = 0;
        s.insert(aux);
        bool ok = 0;
        for (int i = 0; !ok && i < 2; i++)
            ok = (str[n-4+i] != str[n-2+i]);

        if (ok) pd(n-2, 1, 1);
        else pd(n-2, 0, 1);
    }
    if (p3 && n-3 > 4) {
        for (int i = 0; i < 3; i++)
            aux[i] = str[n-3+i];
        aux[3] = 0;
        s.insert(aux);
        bool ok = 0;
        for (int i = 0; !ok && i < 3; i++)
            ok = (str[n-6+i] != str[n-3+i]);

        if (ok) pd(n-3, 1, 1);
        else pd(n-3, 1, 0);
    }   
}

int main () {
    scanf(" %s", str);
    pd(strlen(str), 1, 1);

    printf("%d\n", (int) s.size());
    for (string pr : s)
        printf("%s\n", pr.c_str());
}
