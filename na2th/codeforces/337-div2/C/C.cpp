#include <bits/stdc++.h>
using namespace std;
typedef long long num;
typedef int node;
typedef int edge;

const int N = (1<<9);
int base[2][2];
int ans[N][N], aux[N][N];
int k;

int main()
{
    base[0][0] = base[1][0] = base[1][1] = 1;
    base[0][1] = -1;
    scanf(" %d", &k);
    if(k <= 1)
    {
        for(int i=0;i<(1<<k);i++, putchar('\n'))
            for(int j=0;j<(1<<k);j++)
                if(base[i][j]>0)
                    putchar('+');
                else
                    putchar('*');
        return 0;
    }
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            ans[i][j] = base[i][j];

    for(int l=1;l<k;l++)
    {
        for(int i=0;i<(1<<l);i++)
            for(int j=0;j<(1<<l);j++)
                aux[i][j] = base[0][0]*ans[i][j];

        for(int i=0;i<(1<<l);i++)
            for(int j=0;j<(1<<l);j++)
                aux[i][(1<<l)+j] = base[0][1]*ans[i][j];

        for(int i=0;i<(1<<l);i++)
            for(int j=0;j<(1<<l);j++)
                aux[(1<<l)+i][j] = base[1][0]*ans[i][j];

        for(int i=0;i<(1<<l);i++)
            for(int j=0;j<(1<<l);j++)
                aux[(1<<l)+i][(1<<l)+j] = base[1][1]*ans[i][j];

        for(int i=0;i<N;i++)
            for(int j=0; j<N;j++)
                ans[i][j] = aux[i][j];
    }
    for(int i=0;i<(1<<k);i++, putchar('\n'))
        for(int j=0;j<(1<<k);j++)
            if(ans[i][j] == 1)
                putchar('+');
            else if(ans[i][j] == -1)
                putchar('*');
}
