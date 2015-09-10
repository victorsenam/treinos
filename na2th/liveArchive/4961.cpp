#include<bits/stdc++.h>
#define oo 1000000000
#define MS 30
#define ME 201
using namespace std;
typedef int num;

num  cost[MS][MS], mem[ME][ME][MS], result[MS][MS], inp[ME];
num k, n, es;
char sim[MS];

void solve(int l, int r)
{
    if( l > r || r >= es ) return;

    if( mem[l][r][k] == -1 )
    {
        if( l == r )
        {
            for( int i = 0; i < k; i++ )
                mem[l][r][i] = ( inp[l] == i ) ? 0 : oo ;
        }
        else
        {
            for( int i = 0; i < k; i++ )
                mem[l][r][i] = oo;
            for( int p = l; p+1 <= r; p++ )
            {
                solve(l,p);
                solve(p+1,r);

                for( int s1 = 0; s1 < k; s1++ )
                    if( mem[l][p][s1] < oo )
                        for( int s2 = 0; s2 < k; s2++ )
                            if( mem[p+1][r][s2] < oo )
                            {
                                mem[l][r][result[s1][s2]] = min( mem[l][r][result[s1][s2]], cost[s1][s2] + mem[l][p][s1] + mem[p+1][r][s2] );
                                //printf("[%d,%d]Juntando (%c, %c) a custo %d\n",l,r, sim[s1], sim[s2], cost[s1][s2] + mem[l][p][s1] + mem[p+1][r][s2]);
                            }
            }
        }
        mem[l][r][k] = 1;
    }
}

int main()
{
    while( scanf(" %d", &k) && k > 0 )
    {
        if( n != 0 ) printf("\n");
        map<char, int> rsim;
        for( int i = 0; i < k; i++ )
        {
            scanf(" %[a-z]", sim+i);
            rsim[sim[i]] = i;
        }
        for( int i = 0; i < k; i++ )
            for( int j = 0; j < k; j++ )
            {
                char in;
                scanf(" %d-%[a-z]", &cost[i][j], &in);
                result[i][j] = rsim[in];
            }

        scanf("%d ", &n);
        while( n-- > 0 )
        {
            memset( inp, 0, sizeof inp );
            char c = '0';
            es = 0;
            while( c != '\n' )
            {
                scanf("%c", &c);
                if( !isspace(c) )
                    inp[es++] = rsim[c];
                else break;
            }
            memset( mem, -1, sizeof mem );
            solve(0,es-1);
            num out = INT_MAX;
            int ans = -1;
            for( int i = 0; i < k; i++ )
                if( mem[0][es-1][i] < out )
                {
                    ans = i;
                    out = mem[0][es-1][i];
                }
            printf("%d-%c\n", out, sim[ans]);
        }
    }
}
