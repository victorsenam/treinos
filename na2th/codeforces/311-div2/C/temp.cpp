#include <bits/stdc++.h>
#define MAX 100004
using namespace std;
typedef int num;
num n, l[MAX], d[MAX], freq[MAX], legs[MAX],
    mFreq = 1, currLeg, ans;
set< pair<int, int> > freqLegs;

int main()
{
    scanf("%d", &n);
    for( int i = 0 ; i < n; i++ )
    {
        scanf("%d", l+i);
        freq[l[i]]++;
    }
    for( int i = 0; i < n; i++ )
    {
        scanf("%d", d+i);
        legs[i] = i;
        freqLegs.insert( make_pair(freq[l[i]], i) );
    }

    if( freqLegs.rbegin()->first == 1 )
    {
        sort(legs, legs+n, [&](int a, int b)
        { return d[a] < d[b]; }); 
        for( int i = 0; i < n-1; i++ )
            ans += d[legs[i]];

        printf("%d\n", ans);
        return 0;
    }

    ans = INT_MAX;
    while( !freqLegs.empty() )// &&  freqLegs.rbegin()->first > 1 )
    {
        currLeg = freqLegs.rbegin()->second;
        int f = freqLegs.rbegin()->first;
        printf("%d %d %d\n", currLeg, l[currLeg], f);
        sort(legs, legs+n, [&](int a, int b) 
                {
                if( l[a] == l[currLeg] && l[b] == l[currLeg] ) 
                    return ( d[a] < d[b] );
                if( l[a] == l[currLeg] || l[b] == l[currLeg] )
                    return ( l[b] == l[currLeg] );
                return d[a] < d[b];
                });

        num local = 0;
        for( int i = 0; i < n; i++ )
            printf("%d ", d[i]);
        printf("\n");
        for( int i = 0; i < n - 2*freq[l[currLeg]] + 1 ; i++ )
            local += d[legs[i]];

        printf("[%d]", local);
        ans = min(ans, local);
        while( !freqLegs.empty() && freqLegs.rbegin()->first == freq[l[currLeg]] )
            freqLegs.erase( freqLegs.begin() );
    }
    printf("%d\n", ans);
}
