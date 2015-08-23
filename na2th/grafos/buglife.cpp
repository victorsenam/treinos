#include <bits/stdc++.h>
#define MAX 3000

using namespace std;

vector<int> E[MAX];
int sex[MAX];
int achou;

int dfs(int v, int s)
{
    sex[v] = s;
    for( int i = 0; i < E[v].size(); i++ )
    {
        int viz = E[v][i];
        if( sex[viz] == -1 )
            dfs(viz, !s );
        else if( sex[viz] == s )
            achou = 1;
    }
}

int main()
{
    int s, b, it, e, f;
    scanf("%d", &s);
    for(int i = 1; i <= s ; i++ )
    {
        scanf("%d %d", &b, &it);

        memset(sex, -1, b*sizeof(int));
        for(int j = 0 ; j < b ; j++ )
            E[j].clear();

        printf("Scenario #%d:\n", i);

        while( it-- > 0 )
        {
            scanf("%d %d", &e, &f);
            e--; f--;
            E[e].push_back(f);
            E[f].push_back(e);
        }

        achou = 0;
        for(int j = 0; j < b && !achou; j++)
            if(sex[j] == -1)
                dfs(j,0);

        if(achou)
            printf("Suspicious bugs found!\n");
        else
            printf("No suspicious bugs found!\n");
    }
}
