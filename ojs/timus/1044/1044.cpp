#include <bits/stdc++.h>

using namespace std;

const int N = 110;;

int memo[N][10];
int n;

int pd (int s, int d) { 
    if (s < 0)
        return 0;
    if (d == 1)
        return s <= 9;

    int & m = memo[s][d];
    if (m != -1)
        return m;

    m = 0;
    for (int i = 0; i <= 9; i++)
        m += pd(s-i, d-1);
    return m;
}

int main () {
    int n;
    
    scanf("%d", &n);
    int res = 0;
    memset(memo, -1, sizeof memo);
    for (int i = 0; i <= 9*(n/2); i++)
        res += pd(i, n/2)*pd(i, n/2);

    printf("%d\n", res);
}
