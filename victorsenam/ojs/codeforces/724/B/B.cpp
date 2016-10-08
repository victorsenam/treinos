#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 100;

int n, m;
int a[N][N];
int v[N];

void testit () {
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < m; j++)
            if (a[i][j] != v[j]) cnt++;

        if (cnt > 2) return;
    }
    printf("YES\n");
    exit(0);
}

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++)
        v[i] = i;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
            a[i][j]--;
        }
    }


    testit();
    for (int i = 0; i < m; i++) {
        for (int j = i+1; j < m; j++) {
            swap(v[i], v[j]);
            testit();
            swap(v[i], v[j]);
        }
    }

    printf("NO\n");
}
