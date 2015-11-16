#include<bits/stdc++.h>
using namespace std;
typedef int num;
const int MS = (1<<13)+300;
const int MN = 1.1e3;

num sol[MN][MS];
num in[MN], acc[MN], tgt, nxt;
char out[MN][MS];
int tc, n;

inline bool power(num x)
{ return !(x - (x&-x)); }

void build(int i, int l)
{
    assert(sol[i][l] != -1);
    if( i == n+1 ) return;
    putchar(out[i][l]);
    build(i+1, sol[i][l]);
}

int main()
{
    scanf(" %d", &tc);
    while(tc--)
    {
        scanf(" %d", &n);
        for(int i=1;i<n+1;i++)
        {
            scanf(" %d", in+i);
            acc[i] = acc[i-1] + in[i];
        }

        for(int l=0;l<acc[n]+1;l++)
        {
            int r = acc[n] - l;
            sol[n+1][l] = -1;
            if( r == 0 && power(l) ) sol[n+1][l] = 1;
            if( l == 0 && power(r) ) sol[n+1][l] = 1;
            if( r == l && power(l) ) sol[n+1][l] = 1;
        }
        for(int i=n;i>0;--i)
            for(int l=0;l<acc[i-1]+1;l++)
            {
                int r = acc[i-1] - l;
                sol[i][l] = -1;
                out[i][l] = 0;
                if( l == 0 || in[i] <= (l&-l) )
                {
                    tgt = l + in[i];
                    nxt = ( power(tgt) && (tgt<<1) > r ) ? 0 : tgt;
                    if( sol[i+1][nxt] != -1 )
                    {
                        sol[i][l] = nxt;
                        out[i][l] = 'l';
                    }
                }

                if( ( r == 0 || in[i] <= (r&-r) ) && ( sol[i+1][l] != -1 ) )
                {
                    sol[i][l] = l;
                    out[i][l] = 'r';
                }
            }

        if( sol[1][0] != -1 ) build(1,0);
        else printf("no");
        printf("\n");
    }
}
