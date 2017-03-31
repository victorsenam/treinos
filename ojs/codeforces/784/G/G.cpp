#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

int a;
char c;

void go (int a) {
    for (int i = 0; i < a + '0'; i++)
        putchar('+');
    putchar('.');
    putchar('>');
}

int main () {
    scanf("%d", &a);

    int x;

    while (scanf(" %c%d", &c, &x) != EOF) 
        if (c == '+')
            a += x;
        else
            a -= x;

    if (a >= 100) {
        go(a/100);
        a%=100;
    }
    if (a >= 10) {
        go(a/10);
        a%=10;
    }
    go(a);
}
