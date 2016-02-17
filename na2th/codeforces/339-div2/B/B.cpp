#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define all(a) a.begin(), a.end()
using namespace std;
typedef long long num;
const int S = 1e5+1;
int n, m, diff, as, z;
char in[S];
char ans[2*S];

int main()
{
    scanf(" %d", &n);
    for(int i=0;i<n;i++)
    {
        scanf(" %s", in);
        if(in[1] == 0 && in[0] == '0')
        {
            printf("0\n");
            return 0;
        }
        m = strlen(in);
        int lu, lz;
        lu = lz = 0;
        for(int j=0;j<m;j++)
            if(in[j] == '0') lz++;
            else if(in[j] == '1') lu++;

        if(lu == 1 && lu + lz == m) z += lz; 
        else
        {
            for(int j=0;j<m;j++)
                ans[as++] = in[j];
        }
    }
    printf("%s", ans);
    if(as == 0) putchar('1');
    for(int i=0;i<z;i++) putchar('0');
    putchar('\n');
}
