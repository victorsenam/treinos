#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 2e6+7;

int n;
char str[N];

int main () {
    scanf("%d", &n);
    scanf(" %s", str);

    int res = 0;
    for (int i = 0; i < n; i++)
        if (str[i] == '<') res++;
        else break;

    for (int i = n-1; i >= 0; i--)
        if (str[i] == '>') res++;
        else break;

    printf("%d\n", res);
}
