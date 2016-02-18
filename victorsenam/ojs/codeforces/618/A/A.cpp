#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 100007;

int ss, st[N];
int n;

int main () {
    scanf("%d", &n);

    int att = 30;
    while (att >= 0) {
        if ((1<<att)&n)
            printf("%d ", att+1);
        att--;
    }

    printf("\n");
}
