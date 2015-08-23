#include <bits/stdc++.h>
#define MAX 200003
using namespace std;
typedef unsigned long long num;
num n, m, l[MAX], r[MAX];
int ans[MAX], used[MAX], needed[MAX], aval[MAX];
set< pair<num,int> > bridges;

int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for( int i = 0; i < n; i++ )
    {
        cin >> l[i] >> r[i];
        ans[i] = -1;
    }
    for( int i = 0; i < m; i++ )
    {
        num aux; cin >> aux;
        bridges.insert( make_pair(aux, i) );
        needed[i] = -1;
    }
    for( int i = 0; i < n-1; i++ )
    {
        set< pair<num,int> >::iterator ub = bridges.upper_bound( make_pair(r[i+1]-l[i], INT_MAX)),
                                       lb = bridges.lower_bound( make_pair(l[i+1]-r[i], INT_MIN)), aux;
        aux = lb;
        if( ++aux == ub )
        {
            ans[i] = lb->second;
            used[lb->second]   = 1;
            needed[lb->second] = 0;
        }
        for(; lb != ub; ++lb) aval[i]++;
    }

    for( int i = 0; i < n-1; i++ )
    {
        if( ans[i] > 0 ) continue;
        set< pair<num,int> >::iterator ub = bridges.upper_bound( make_pair(r[i+1]-l[i], INT_MAX)),
                                       lb = bridges.lower_bound( make_pair(l[i+1]-r[i], INT_MIN)), aux;
        for( ; lb != ub; ++lb )
            if( used[lb->second] == 0 && needed[lb->second] > aval[i]  )
            {
                ans[i] = lb->second;
                used[lb->second] = 1;
                break;
            }
        if( ans[i] == -1 )
        {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
    for( int i = 0; i < n-1; i++ )
        cout << ans[i]+1 << " ";
    cout << endl;
}
