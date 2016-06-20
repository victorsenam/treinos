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

char c;
int n;

int main () {
    scanf("I am Groot%c", &c);
    while (c == '!') {
        n++;
        scanf("%c", &c);
    }

    if (n) {
        printf("W");
        for( int i = 0; i < n; i++)
            printf("o");
        printf("w\n");
    } else {
        printf("Pfff\n");
    }
}
