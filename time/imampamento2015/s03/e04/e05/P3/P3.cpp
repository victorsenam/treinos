#include <bits/stdc++.h>

using namespace std;

#define MAX 1005

typedef long long int num;

map <string, int> ops;
int ln, ls;
num ncost[MAX];
int nops[MAX];
num scost[MAX];
int sops[MAX];

num memo_val[MAX][MAX];
int memo_num[MAX][MAX];

num pd(int a, int b)
{
    if (a >= ln) return 0;
    if (b >= ls) return 0;

    num & m = memo_val[a][b];
    num res;

    if (m != -1)
        return m;

    m = 0;
    memo_num[a][b] = 0;

    res = pd(a+1, b);
    if (res > m || (res == m && memo_num[a][b] > memo_num[a+1][b])) {
        m = res;
        memo_num[a][b] = memo_num[a+1][b];
    }
    res = pd(a, b+1);
    if (res > m || (res == m && memo_num[a][b] > memo_num[a][b+1])) {
        m = res;
        memo_num[a][b] = memo_num[a][b+1];
    }

    if (nops[a] == sops[b] && ncost[a] + scost[b] > 0) {
        //m += ncost[a] + scost[b];
        //memo_num[a][b]++;
        res = pd(a+1, b+1) + ncost[a] + scost[b]; 
        if (res > m || (res == m && memo_num[a][b] > memo_num[a+1][b+1]+1)) {
            m = res;
            memo_num[a][b] = memo_num[a+1][b+1]+1;
        }
    }


    return m;
}

int main()
{
    int t;
    scanf("%d", &t);
    while(t-- > 0)
    {
        ops.clear();
        scanf("%d", &ln);
        for(int i = 0; i < ln; i++)
        {
            string str;
            int cost;
            cin >> str;
            cin >> str >> cost;
            ncost[i] = cost;
            if (ops.find(str) == ops.end())
                ops[str] = ops.size()-1;
            nops[i] = ops[str];
        }
        scanf("%d", &ls);
        for(int i = 0; i < ls; i++)
        {
            string str;
            int cost;
            cin >> str;
            cin >> str >> cost;
            scost[i] = cost;
            if (ops.find(str) == ops.end())
                ops[str] = ops.size()-1;
            sops[i] = ops[str];
        }

        for (int i = 0; i < ln; i++)
            for (int j = 0; j < ls; j++)
                memo_val[i][j] = -1;
        for (int i = 0; i <= ls; i++)
            memo_val[ln][i] = memo_num[ln][i] = 0;
        for (int i = 0; i <= ln; i++)
            memo_val[i][ls] = memo_num[i][ls] = 0;
        

        pd (0,0);
        printf("%lld %d\n", memo_val[0][0], memo_num[0][0]);
    }
}
