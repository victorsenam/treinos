#include<bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
typedef int edge;

const int MN = 2000000;
int freq[MN], n, ans;

int main()
{
    scanf(" %d", &n);
    for(int i=0;i<n;i++)
    {
        int aux;
        scanf(" %d", &aux);
        freq[aux]++;
    }

    for(int i=0;i<MN-1;i++)
    {
        freq[i+1] += freq[i]/2;
        freq[i] %= 2;
        ans += !!(freq[i]);
    }

    printf("%d\n", ans);
}
