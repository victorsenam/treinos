#include <bits/stdc++.h>



using namespace std;

const int N = 9000;

int n, c[4];
int m[N];

int main () {
    scanf("%d %d %d %d", &n, c, c+1, c+2);
    
    for (int i = 1; i <= n; i++) {
        m[i] = 0;
        for (int j = 0; j < 3; j++) {
            if (i - c[j] < 0) continue;
            else if (i - c[j] == 0)
                m[i] = max(m[i], 1);
            else if (m[i-c[j]] != 0)
                m[i] = max(m[i], m[i-c[j]] + 1);
        }
    }
    printf("%d\n", m[n]);
}
