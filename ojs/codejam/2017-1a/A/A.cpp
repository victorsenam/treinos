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

const int N = 50;

char mat[N][N];

int n, m;
int ts;

int main () {
    scanf("%d", &ts);
    
    for (int tt = 1; tt <= ts; tt++) {
        printf("Case #%d:\n", tt);
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n; i++)
            scanf(" %s", mat[i]);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                if (mat[i][j] == '?' && j)
                    mat[i][j] = mat[i][j-1];
            for (int j = m-1; j >= 0; j--)
                if (mat[i][j] == '?' && j < m - 1)
                    mat[i][j] = mat[i][j+1];
        }
        
        for (int i = 0; i < n; i++) {
            if (mat[i][0] == '?' && i)
                for (int j = 0; j < m; j++)
                    mat[i][j] = mat[i-1][j];
        }

        for (int i = n-1; i >= 0; i--) {
            if (mat[i][0] == '?' && i < n-1)
                for (int j = 0; j < m; j++)
                    mat[i][j] = mat[i+1][j];
        }

        for (int i = 0; i < n; i++)
            printf("%s\n", mat[i]);
    }
}
