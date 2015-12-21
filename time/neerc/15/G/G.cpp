#include <bits/stdc++.h>
using namespace std;
typedef int num;
const int N = 1e4+2;
const int C = 1e3+3;
int n, k, a, b, c, f;
int tot, ans, fix, cnt;
int bst[N], sbst[N], bi[N], sbi[N], idx[C];
int seen[C], turn;

int main()
{
    freopen("generators.in", "r", stdin);
    freopen("generators.out", "w", stdout);
    scanf(" %d%d", &n, &k);
    for(int i=0;i<n;i++)
    {
        turn++;
        scanf(" %d%d%d%d", &f, &a, &b, &c);
        bst[i] = -1;
        int x = f;
        idx[x] = cnt = 0;
        while(seen[x] != turn)
        {
            seen[x] = turn;
            bst[i] = max(bst[i], x);
            idx[(a*x+b)%c] = ++cnt;
            x = (a*x+b)%c;
        }
        tot += bst[i];
        sbst[i] = sbi[i] = -1;
        bi[i] = idx[bst[i]];
        for(int j=bst[i]; j>=0; --j)
            if( seen[j] == turn && (bst[i]-j)%k )
            {
                sbst[i] = j;
                sbi[i] = idx[j];
                break;
            }
    }
    if(tot%k)
    {
        printf("%d\n", tot);
        for(int i=0;i<n;i++)
            printf("%d ", bi[i]);
        putchar('\n');
        return 0;
    }

    fix = -1;
    ans = 0;
    for(int i=0;i<n;i++)
        if(sbst[i] != -1 && ans < tot-bst[i]+sbst[i])
        {
            ans = tot - bst[i] + sbst[i];
            fix = i;
        }
    if(fix == -1)
        printf("%d\n", -1);
    else
    {
        printf("%d\n", ans);
        for(int i=0;i<n;i++)
            printf("%d ", fix==i? sbi[i] : bi[i]);
        putchar('\n');
    }
}
