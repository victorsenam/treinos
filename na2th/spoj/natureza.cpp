#include<bits/stdc++.h>
#define MV 5004
#define ME 10004
using namespace std;
typedef int num;

num head[MV], label[MV], freq[MV];
num to[ME], next[ME], es;
num c, r, out;

num dfs( num s, num l )
{
    freq[l]++;
    label[s] = l;
    for( num e = head[s]; e >= 0; e = next[e] )
        if( label[to[e]] == -1 )
            dfs( to[e], l );
}

int main()
{
    ios::sync_with_stdio(false);
    while( cin >> c >> r  && c )
    {
        map<string, int> names;
        string aux, aux2;
        es = 0;
        memset(head, -1, sizeof head);
        for( int i = 0; i < c; i++ )
        {
            cin >> aux;
            names[aux] = i;
        }

        for( int i = 0; i < r; i++ )
        {
            cin >> aux >> aux2;
            int u = names[aux],
                v = names[aux2];
            to[es] = u; next[es] = head[v]; head[v] = es++;
            to[es] = v; next[es] = head[u]; head[u] = es++;
        }
        memset(label, -1, sizeof label);
        memset(freq,   0, sizeof freq);
        for( int i = 0; i < c; i++ )
            if( label[i] == -1 )
                dfs(i, i);
        out = INT_MIN;
        for( int i = 0; i < c; i++ )
            out = max(out, freq[i]);
        cout << out << endl;
    }
}
