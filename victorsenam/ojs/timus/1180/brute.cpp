#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 100000;

char c;

int main () {
    int s = 0;
    while (scanf(" %c", &c) != EOF) {
        s += c-'0';
        s %= 3;
    }
    printf("%d\n", 2-!!s);
    if (!!s)
        printf("%d\n", s);
}
