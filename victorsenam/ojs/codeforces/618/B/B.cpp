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

const int N = 57;

int n;
int mat[N][N];
int ls[N];
int a;

int main () {
    scanf("%d", &n);
    bool top = 0;

    for (int i = 0; i < n; i++) {
        int val = 0;
        for (int j = 0; j < n; j++) {
            scanf("%d", &a);
            if (val)
                continue;
            if (ls[a] == i+1)
                val = a;
            ls[a] = i+1;
        }

        if (val)
            printf("%d", val);
        else if (top) {
            printf("%d", n-1);
        } else {
            printf("%d", n);
            top = 1;
        }
        printf(" ");
    }
    printf("\n");
}
