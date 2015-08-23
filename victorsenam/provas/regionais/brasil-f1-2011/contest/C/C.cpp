#include <bits/stdc++.h>

using namespace std;

int button[27];
int press[27];
double d[12][12];

int v[141];
int size = 0;

double memo[12][12][141][2];

double dst(int a, int b)
{
    int l1 = abs( b%3 - a%3 );
    int l2 = abs( b/3 - a/3 );
    return sqrt (l1*l1 + l2*l2);
}

double pd(int l, int r, int i, int h)
{
    if (memo[l][r][i][h] != DBL_MAX)
        return memo[l][r][i][h];
    int b = button[v[i]];
    double tl, tr;
    if (h == 1)
    {
        tl = d[l][11]/30 + 0.2;  
        tr = d[r][11]/30 + 0.2;  
        memo[l][r][i][h] = min(tl + pd(11, r, i, 0),
                               tr + pd(l, 11, i, 0));
        return memo[l][r][i][h];
    }
    // h == 0
    if (i == size-1)
    {
        tl = d[l][b]/30 + 0.2*press[v[i]];
        tr = d[r][b]/30 + 0.2*press[v[i]];
        memo[l][r][i][h] = min(tl, tr);
        return memo[l][r][i][h];
    }
    tl = d[l][b]/30 + 0.2*press[v[i]];
    tr = d[r][b]/30 + 0.2*press[v[i]];
    bool go = button[v[i+1]] == button[v[i]];
    memo[l][r][i][h] = min(tl + pd(b, r, i+1, go), tr + pd(l, b, i+1, go));
    return memo[l][r][i][h];
}

int main()
{
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 12; j++)
            d[i][j] = dst(i,j);
    for (int c = 0; c < 26; c++)
    {
        if (c + 'a' < 's')
        {
            press[c] = c%3 + 1;
            button[c] = c/3 + 1;
        }
        else if (c + 'a' == 's')
        {
            press[c] = 4;
            button[c] = 6;
        }
        else
        {
            press[c] = (c-1)%3 + 1;
            button[c] = (c-1)/3 + 1;
        }
    }
    press[25] = 4; 
    button[25] = 8;
    press[26] = 1;
    button[26] = 10;
    size = 0;
    char c;
    while (scanf("%c", &c) != EOF)
    {
        if (c != '\n')
        {
            if (c != ' ')
                v[size++] = c - 'a';
            else v[size++] = 26;
        }
        else
        {
            for (int i = 0; i < 12; i++)
                for (int j = 0; j < 12; j++)
                    for (int k = 0; k < 141; k++)
                    {
                        memo[i][j][k][0] = DBL_MAX;
                        memo[i][j][k][1] = DBL_MAX;
                    }
            pd(3, 5, 0, 0);
            printf("%.2lf\n", memo[3][5][0][0]);
            size = 0;
        }
    }
}
