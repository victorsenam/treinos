#include <bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
typedef int edge;
const int S = 2e5+5;
const int C = 256;

char in[S], ans[S];
int n, freq[C], as;
int odd, i, j;

int main()
{
    scanf(" %s", in);
    n = strlen(in);
    for(i=0;i<n;i++)
        freq[in[i]]++;
    for(i=0;i<C;i++)
        odd += (freq[i]&1);
    i = 'a'; j = 'z';
    while(odd > 1)
    {
        while(!(freq[i]&1)) i++;
        while(!(freq[j]&1)) --j;
        freq[i] += 1;
        freq[j] -= 1;
        odd -= 2;
    }
    for(i='a';i<'z'+1;i++)
        for(j=0;j<freq[i]/2;j++)
            ans[as++] = i;
    for(i='a';i<'z'+1;i++)
        if(freq[i]&1)
                ans[as++] = i;
    for(i='z';i>='a';--i)
        for(j=0;j<freq[i]/2;j++)
            ans[as++] = i;
    printf("%s\n", ans);
}
