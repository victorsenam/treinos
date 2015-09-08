#include <bits/stdc++.h>

using namespace std;

#define MAX 510

double memo[MAX][MAX][2];

int mod(int a)
{ return (a%20 + 20)%20; }

int v[20];

double pd(int na, int nb, int p)
{
    // 0 == a
    // 1 == b
    /*
    if (na < 0 && p == 0)
        return 0.0;
    if (nb < 0 && p == 1)
        return 0.0;
        */
    double &m = memo[na][nb][p];
    if (m >= 0) return m;
    if (na == 0 || nb == 0)
    {
        if (p == 0 && na == 0)
            m = 1.0;
        if (p == 1 && nb == 0)
            m = 1.0;

        if (p == 0 && nb == 0)
            m = 0.0;
        if (p == 1 && na == 0)
            m = 0.0;
        return m;
    }
    if (p == 0)
    {
        m = 0.0;
        for (int i = 1; i <= 20 && na-i >= 0; i++)
            m += 1-pd(na-i, nb, 1);
        m /= 20.0;
        return m;
    }
    double maxi = -1;
    int midx = -1;
    for (int i = 0; i < 20; i++)
    {
        // if (nb-v[i] >= 0 && 1-pd(na, nb-v[i], 0) > maxi)
        if (1-pd(na, nb-v[i], 0) > maxi)
        {
            maxi = 1-pd(na, nb-v[i], 0);
            midx = i;
        }
    }
    if (midx < 0)
    { m = 0.0; return m; }
    m = 1-pd(na, nb-v[midx], 0);
    if (nb-v[mod(midx-1)] >= 0)
        m += 1-pd(na, nb-v[mod(midx-1)], 0); 
    if (nb-v[mod(midx-1)] >= 0)
        m += 1-pd(na, nb-v[mod(midx+1)], 0);
    m /= 3.0;
    return m;
}


int main()
{
    int n;
    v[0] = 20;
    v[1] = 1;
    v[2] = 18;
    v[3] = 4;
    v[4] = 13;
    v[5] = 6;
    v[6] = 10;
    v[7] = 15;
    v[8] = 2;
    v[9] = 17;
    v[10] = 3;
    v[11] = 19;
    v[12] = 7;
    v[13] = 16;
    v[14] = 8;
    v[15] = 11;
    v[16] = 14;
    v[17] = 9;
    v[18] = 12;
    v[19] = 5;
    while(scanf("%d", &n) != EOF && n)
    {
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
            {
                memo[i][j][0] = -1;
                memo[i][j][1] = -1;
            }
        printf("%lf %lf\n", pd(n, n, 0), pd(n, n, 1));
    }
}
