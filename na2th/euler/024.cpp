#include <bits/stdc++.h>
using namespace std;
typedef int num;
const int MD = 11;
int ans[MD], sol[MD], used[MD], fact[MD];
int n, k, aux, d;

int main()
{
    fact[0] = 1;
    for(int i=1;i<MD;i++)
        fact[i] = i*fact[i-1];

    scanf(" %d%d", &n, &k);
    k--;
    for(int i=0;i<n;i++)
    {
        ans[i] = k/fact[n-1-i];
        k %= fact[n-1-i];
    }
    sol[0] = ans[0];
    used[ans[0]] = 1;
    for(int i=1;i<n;i++)
    {
        aux = 0;
        for(d=0;d<n;d++)
        {
            if(used[d]) continue;
            if(aux == ans[i]) break;
            aux++;
        }
        sol[i]  = d;
        used[d] = 1;
    }
    for(int i=0;i<n;i++)
        putchar(48+sol[i]);
    putchar('\n');
}
