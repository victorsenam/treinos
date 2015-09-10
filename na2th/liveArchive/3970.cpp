#include<bits/stdc++.h>
#define oo 1000000000
#define MP 51
using namespace std;
typedef int num;
typedef unsigned long long line;
typedef int point;
num x[MP], y[MP], z[MP];
line goal, curr, aux, good[MP*MP], sol[MP*MP], ss, gs;
set<line> goodLines;
num n;

inline bool collinear( point a, point b, point c )
{
    return ( (y[b]-y[a])*(z[c]-z[a]) == (z[b]-z[a])*(y[c]-y[a]) ) &&
           ( (z[b]-z[a])*(x[c]-x[a]) == (x[b]-x[a])*(z[c]-z[a]) ) &&
           ( (x[b]-x[a])*(y[c]-y[a]) == (y[b]-y[a])*(x[c]-x[a]) );
}

int minimize( int p , line state )
{
    if( state == goal ) return 0;
    if( p >= gs ) return oo;
    if( (good[p]|state) == state ) return minimize(p+1, state);
    return min( minimize(p+1,state), 1 + minimize(p+1, (state|good[p]) ) );
}

int main()
{
    int tc = 1;
    while( scanf(" %d", &n) && n )
    {
        num ans = 0; ss = 0;
        gs = 0; goodLines.clear();
        goal = 0ull;

        for( int i = 0; i < n; i++ )
            scanf("%d %d %d", x+i, y+i, z+i);

        for( int i = 0; i < n; i++ )
            for( int j = i+1; j < n; j++ )
            {
                curr = 0ull;
                curr |= (1ull<<i);
                curr |= (1ull<<j);
                aux = curr;
                for( int k = 0; k < n; k++ )
                    if( collinear(i,j,k) )
                        curr |= (1ull<<k);

                if( curr != aux )
                {
                    goal |= curr;
                    if( goodLines.count(curr) == 0 )
                    {
                        good[gs++] = curr;
                        goodLines.insert(curr);
                    }
                }
            }
        for( int i = 0; i < n; i++ )
            if( (goal&(1ull<<i)) == 0 ) ans++;
        ans++; ans /= 2;
        printf("Target set %d can be cleared using only %d shots.\n", tc++, ans + minimize(0, 0ull) );
    }
}
