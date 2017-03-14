#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define lld I64d
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 1007;
int t;
bool ok;
char c;
int i;

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf(" %c", &c);
        ok = 0;
        do {
            if ((c >= '0' && c <= '9') && (ok || c != '0')) {
                putchar(c);
                ok = 1;
            }
            scanf("%c", &c);
        } while (c != '\n');
        if (!ok)
            putchar('0');
        putchar('\n');
    }
}

