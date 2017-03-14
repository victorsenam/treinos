
#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

int main () {
    char i = -1;
    char c;
    while (scanf("%c", &c) != EOF) {
        if (i == -1)
            i = c;
        if (c == i) {
            i = (i+127)%128;
        } else {
            printf("%d\n", c);
            i = -1;
        }
    }
}
