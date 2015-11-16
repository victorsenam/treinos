#include <bits/stdc++.h>
using namespace std;
typedef int num;
const int R  = 201;

num in[R][R];
int seen[R][R], turn, cmp, border;
int r, c, p, q, anc;
int di[4] = {-1,0,0,1},
    dj[4] = {0,-1,1,0};

inline bool inRange(int lo, int x, int hi)
{ return lo <= x && x < hi; }
inline bool isVal(int i, int j)
{ return inRange(0,i,r) && inRange(0,j,c); }
inline num sign(num x)
{ return (x>0)-(x<0); }

void dfs(int i, int j)
{
    int ti, tj;
    seen[i][j] = turn;
    for(int k=0;k<4;k++)
        if( isVal(ti=i+di[k],tj=j+dj[k]) && 
            in[ti][tj] == in[i][j] &&
            seen[ti][tj] != turn )
                dfs(ti,tj);
}

int main()
{
    while( scanf(" %d%d", &r, &c) != EOF )
    {
        for(int i=0;i<r;i++)
            for(int j=0;j<c;j++)
                scanf(" %d", &in[i][j]);
        turn++;
        cmp =  border = 0;
        for(int i=0;i<r;i++)
            for(int j=0;j<c;j++)
                if( seen[i][j] != turn )
                    dfs(i,j),cmp++;
        for(int j=0;j<c-1;j++)
        {
            p = 0;
            while( p < r )
            {
                q = p;
                bool st = 0;
                int s = sign(in[p][j] - in[p][j+1]);
                while( p < r &&  sign(in[p][j]-in[p][j+1]) == s && 
                    (!st || (sign(in[p][j]-in[p-1][j+1]) == s && sign(in[p-1][j]-in[p][j+1]) == s) ) ) 
                {
                    p++;
                    st = 1;
                }
                border += !!s;
            }
        }
        for(int i=0;i<r-1;i++)
        {
            p = 0;
            while( p < c )
            {
                q = p;
                bool st = 0;
                int s = sign(in[i][p] - in[i+1][p]);
                while( p < c && sign(in[i][p]-in[i+1][p]) == s &&
                        (!st || (sign(in[i][p]-in[i+1][p-1]) == s && sign(in[i][p-1]-in[i+1][p]) == s) ) ) 
                {
                    p++;
                    st = 1;
                }
                border += !!s;
            }
        }
        printf("%d\n", 5 + cmp + border);
    }
}
