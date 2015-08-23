#include<bits/stdc++.h>
using namespace std;
typedef long long int num;
const int MP = 5004;
num ini[MP], fim[MP], aval[2*MP], tree[2*MP], n, s, e, as;

void insert(int pos, num val)
{
    for(;pos>0;pos-=(pos&-pos))
        tree[pos] += val;
}

num count(int pos)
{
    num sum=0;
    for(;pos<=as;pos+=(pos&-pos))
        sum += tree[pos];
    return sum;
}

int main()
{
    ios::sync_with_stdio(false);
    while( cin >> s >> e )
    {
        memset(tree, 0, sizeof tree);
        cin >> n;
        as = 0;
        aval[as++] = s;
        aval[as++] = e;
        for(int i=0; i<n;i++)
        {
            cin >> ini[i] >> fim[i];
            aval[as++] = ini[i];
            aval[as++] = fim[i];
        }
        sort(aval, aval+as);
        sort(ini, ini+n);
        sort(fim, fim+n);
        as = unique(aval, aval+as) - aval;

        for(int i=0;i<n;i++)
        {
            num lo = lower_bound(aval, aval+as, ini[i]) - aval,
                hi = lower_bound(aval, aval+as, fim[i]) - aval + 1;
            insert(hi, 1);
            insert(lo, -1);
        }
        int minVal, maxVal;

        s = lower_bound(aval, aval+as, s) - aval + 1;
        e = lower_bound(aval, aval+as, e) - aval + 1;
        minVal = count(s);
        maxVal = count(s);

        for(int pos=s;pos<=e;pos++)
        {
            num val    = count(pos),
                ending = upper_bound(fim,fim+n,aval[pos-1])-lower_bound(fim,fim+n,aval[pos-1]); 

            // Pessoas entre esse e o próximo tempo
            if( pos != e && val - ending < minVal )
                minVal = val - ending;

            // Pessoas no tempo fechado
            if( val < minVal )
                minVal = val;
            if( val > maxVal )
                maxVal = val;
        }
        cout << minVal << " " << maxVal << endl;
    }
}
