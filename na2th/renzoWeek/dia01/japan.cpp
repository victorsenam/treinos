#include<bits/stdc++.h>
using namespace std;
typedef int num;
const num MN = 1002;
const num MK = (MN*MN);

num tree[MK], perm[MK], seq[MK], fst[MN], snd[MN], m, n, k;

void insert(int p, num val)
{
    for(;p<=k;p+=(p&-p))
        tree[p] += val;
}

num count(int p)
{
    num sum=0;
    for(;p>0;p-=(p&-p))
        sum += tree[p];
    return sum;
}

bool lexLess(int a, int b)
{ 
    if( fst[a] == fst[b] ) return snd[a] < snd[b];
    return fst[a] < fst[b];
}

bool seqLess(int a,int b)
{ return seq[a] < seq[b]; }

int main()
{
    int tc;
    ios::sync_with_stdio(false);
    cin >> tc;
    for(int tcn=1;tcn<tc+1;tcn++)
    {
        num ans;
        cout << "Test case " << tcn << ": ";
        cin >> n >> m >> k;
        for(int i=0;i<k;i++)
        {
            cin >> fst[i] >> snd[i];
            perm[i] = i;
        }
        sort(perm, perm+k, lexLess);
        for(int i=0;i<k;i++)
        {
            seq[i]  = snd[perm[i]];
            perm[i] = i;
        }
        sort(perm, perm+k, seqLess);

        for(int i=1;i<k+1;i++)
            tree[i] = (i&-i);
        
        int curr, range, pos = 0;
        ans = 0;
        while( pos < k )
        {
            curr = seq[perm[pos]];
            range = pos;
            while( range < k && seq[perm[range]] == curr )
                insert(perm[range++]+1, -1);
            while( pos < range )
                ans += count(perm[pos++]+1);
        }
        cout << ans << endl;
    }
}
