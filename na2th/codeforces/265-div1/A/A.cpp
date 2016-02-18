#include <bits/stdc++.h>
using namespace std;
typedef int num;

const int N = 1e3;
int fst, k, n, p, in[N], tg[N];
char aux;

int main()
{
    scanf(" %d%d", &n, &p);
    for(int i=0;i<n;i++)
    {
        scanf(" %c", &aux);
        in[i] = aux-'a';
    }
    fst = -1;
    if(in[0] < p-1) fst = 0;
    if(in[0] < p-1 || in[1] < p-1) fst = 1;
    for(int i=2;i<n;i++)
    {
        k = in[i];
        if(k == in[i-1] || k == in[i-2]) k++;
        if(k == in[i-1] || k == in[i-2]) k++;
        tg[i] = k;
        if(k < p) fst = i;
        else tg[i] = 30;
    }
    in[fst] = tg[fst];
    fst++;
    for(int i=fst;i<n;i++)
    {
        in[i] = 0;
        if(in[i] == in[i-1] || in[i] == in[i-2] ) in[i]++;
        if(in[i] == in[i-1] || in[i] == in[i-2] ) in[i]++;
    }
    if(*max_element(in,in+n) >= p)
        printf("NO");
    else
        for(int i=0;i<n;i++)
            putchar('a'+in[i]);
    putchar('\n');
}
