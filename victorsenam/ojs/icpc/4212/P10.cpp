#include <bits/stdc++.h>

using namespace std;

#define N 100001

typedef long long int num;

vector<num> mat[N];
num sums[N];
num memo[N];
int n, m;
num aux;

int main () {
    while (scanf("%d %d", &n, &m) != EOF && n && m) {
        for (int i = 0; i < n; i++) {
            mat[i].clear();
            for (int j = 0; j < m; j++) {
                scanf("%llu", &aux);
                mat[i].push_back(aux);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!j) memo[j] = mat[i][j];
                else if (j == 1) memo[j] = max(mat[i][j], mat[i][j-1]);
                else memo[j] = max(mat[i][j] + memo[j-2], memo[j-1]);
            }
            sums[i] = memo[m-1];
        }

        for (int j = 0; j < n; j++) {
            if (!j) memo[j] = sums[j];
            else if (j == 1) memo[j] = max(sums[j], sums[j-1]);
            else memo[j] = max(sums[j] + memo[j-2], memo[j-1]);
        }

        printf("%llu\n", memo[n-1]);
    }
}

