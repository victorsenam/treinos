#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define MAX 1005
#define eps 1e-9

int n;
set< pair<num, pair<num,num> > > triples;
set< pair<num, pair<num,num> > >::iterator it, goal;

int gcd(int a, int b)
{ return (a%b==0) ? b : gcd(b,a%b); }

int main () 
{
    int t, h, w, tc=1;
    scanf("%d", &t);
    for(int u = 1; u < MAX; u++ )
        for(int v=u+1; v < MAX; v++ )
            if( gcd(u,v) == 1 && !(u%2&&v%2) )
            {
                num a = v*v-u*u,
                    b = 2*u*v,
                    c = u*u + v*v;
                for(int k =1; k*a < MAX && k*b < MAX; k++)
                {
                    triples.insert(make_pair(k*c, make_pair(k*a,k*b)));
                    triples.insert(make_pair(k*c, make_pair(k*b,k*a)));
                }
            }
    while (t-- > 0) 
    {
        scanf("%d %d", &h, &w);
        ll ans = 0;
        // horizontal
        for (int r = 1; 2*r <= w && 2*r <= h; r++) 
        {
            for (int l = 1; l <= r && 2*(l+r) <= w; l++) 
            {
                ans += (w - 2*(l+r) + 1)*(h - 2*r + 1);
                if (l != r)
                    ans += (w - 2*(l+r) + 1)*(h - 2*r + 1);
            }
        }
        // vertical
        for (int r = 1; 2*r <= h && 2*r <= w; r++) 
        {
            for (int l = 1; l <= r && 2*(l+r) <= h; l++) 
            {
                ans += (h - 2*(l+r) + 1)*(w - 2*r + 1);
                if (l != r)
                    ans += (h - 2*(l+r) + 1)*(w - 2*r + 1);
            }
        }

        // Diagoloucos
        for( it = triples.begin(); it != triples.end(); ++it )
        {
            num c  = it->first,
                dx = it->second.first,
                dy = it->second.second;
            for( int r = 1; r < c ; r++ )
            {
                int l  = c-r,
                    xs = max( r+dx+l, 2*max(r,l) ),
                    ys = max( r+dy+l, 2*max(r,l) );
                if( xs <= w && ys <= h )
                    ans += 2*(w-xs+1)*(h-ys+1);
            }
        }

        printf("Case %d: %lld\n",tc++, ans);
    }
}
