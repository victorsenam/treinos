#include <bits/stdc++.h>

using namespace std;

typedef int cood;
typedef pair<cood, cood> point;

cood cP(point A, point B, point C)
{
    // A.first A.second 1
    // B.first B.second 1
    // C.first C.second 1

    return A.first*B.second + A.second*C.first + B.first*C.second
        - C.first*B.second - C.second*A.first - B.first*A.second;
}

int main()
{
    int t;
    point E, g;
    vector<point> P;
    scanf("%d", &t);
    while( t-- > 0 )
    {
        int ans = 0, p;
        cood x, y;
        scanf("%d %d", &x, &y);
        E = make_pair(x,y);

        scanf("%d", &p);
        P.clear();
        for(int i = 0; i < p; i++)
        {
            scanf("%d %d", &x, &y);
            P.push_back( make_pair(x,y) );
        }

        sort(P.begin(), P.end());
        scanf("%d", &p);
        while( p-- > 0 )
        {
            scanf("%d %d", &x, &y);
            g = make_pair(x,y);

            // Handmade binary search
            int lo = 0, hi = P.size();
            while ( lo <= hi )
            {
                int mid = lo + (hi-lo)/2;
                long long f1 = cP(g , make_pair( 0, P[mid].first  ), E),
                     s1 = cP(g , make_pair( 0, P[mid].second ), E),
                     f2 = cP( make_pair( 0, P[mid].first  ), g, E),
                     s2 = cP( make_pair( 0, P[mid].second ), g, E);

                if( s1*f1 <= 0 )
                {
                    if( s1*f1 < 0 && f2*s2 < 0 )
                        ans++;
                    lo = hi+1;
                }
                else if( s1 < 0 ) // Ponto baixo demais
                    lo = mid+1;
                else
                    hi = mid-1;
            }
        }

        printf("%d\n", ans);
    }
}
