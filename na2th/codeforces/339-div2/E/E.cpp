#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define all(a) a.begin(), a.end()
using namespace std;
typedef long long num;
const int S = 1e5;

int n, sz;
int freq[26], in[26];
int ans[S], as, sol;
int flag, co;
vector<int> spc[S];
int ss;

int main()
{
    scanf(" %d", &n);
    for(int i=0;i<n;i++) scanf(" %d", in+i);
    if(n == 1)
    {
        printf("%d\n", in[0]);
        for(int i=0;i<26;i++)
            for(int j=0;j<in[i];j++)
                putchar('a'+i);
        putchar('\n');
        return 0;
    }
    for(int i=0;i<n;i++) sz += (freq[i] = in[i]);
    while(42)
    {
        co = 0;
        if(*max_element(freq,freq+26) == 0) break;
        for(int i=0;i<26;i++)
        {
            if(freq[i]&1) spc[ss].pb(i);
            freq[i] >>= 1;
        }
        ss++;
    }
    if(ss == 1)
    {
        printf("0\n");
        for(int i=0;i<26;i++)
            for(int j=0;j<in[i];j++)
                putchar('a'+i);
    }
    else
    {
        sol = 1;
        while(ss > 0)
        {
        }
    }
}
