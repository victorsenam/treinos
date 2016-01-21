#include <bits/stdc++.h>
using namespace std;
typedef long long num;

int * kmp;
int i, j, k, m, n;
char c, * P;

int main()
{
    while(scanf(" %d", &m))
    {
        if(feof(stdin)) break;
        kmp = new int [m+1];
        P   = new char [m+2];
        scanf(" %s", P+1);
        kmp[0] = k = -1;
        for(j=1;j<m+1;j++)
        {
            while(k >= 0 && P[k+1] != P[j]) k = kmp[k];
            kmp[j] = ++k;
        }
        c = i = j = 0;
        while(isspace(c=getchar()));
        while(c != '\n')
        {
            c = getchar();
            while(j >= 0 && P[j+1] != c) j = kmp[j];
            if(++j == m)
            {
                printf("%d\n", i-j+2);
                j = kmp[j];
            }
            i++;
        }

        delete[] kmp;
        delete[] P;
        putchar('\n');
    }
}
