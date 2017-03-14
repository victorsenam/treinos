#include<bits/stdc++.h>
using namespace std;
typedef int num;
typedef int node;
typedef int edge;

const int MV = 53;
const int ME = 2*MV*MV;

int t, aux, cyc;
int anc[MV];
char adj[MV][MV], a1, a2;
char ans[MV][MV];

int dist[MV], pre[MV], pos[MV], ord[MV], prei, posi;
int nxt[MV];
int fst, best;

int dfs(node u, node d)
{
    if (pre[u] != -1 && pos[u] != -1) {
        return -1;
    }
    if (pre[u] != -1) {
        anc[u] = d;
        return u;
    }
    pre[u] = prei++;
    anc[u] = d;
    for(node v=0; v<26;v++)
        if( adj[u][v] ) {
            int w = dfs(v, u);
            if ( w != -1)
                return w;
        }

    pos[u] = posi;
    ord[posi++] = u;
    return -1;
}

int main()
{
    scanf("%d", &t);
    while(t--)
    {
        prei = posi = 0;
        for(int i=0;i<26*26;i++)
            adj[i/26][i%26] = 1;

        scanf(" %d", &aux);
        while(aux--)
        {
            scanf(" %c%c", &a1, &a2);
            adj[a1-'a'][a2-'a'] = 0;
        }

        memset(pre, -1, sizeof pre);
        memset(pos, -1, sizeof pos);
        cyc = -1;
        for(node v=0;cyc==-1 && v<26;v++)
            if( pre[v] == -1 )
                cyc = dfs(v,v);

        if(cyc >= 0)
        {
            aux = cyc;
            for(int i=44;i>=0;i--, aux = anc[aux])
                ans[0][i] = aux+'a';

            for(int i= 1; i < 20; i++)
                for (int j = 0; j < 20; j++)
                    ans[i][j] = ans[0][j+i];

            for(int i=0;i<20;i++)
                ans[i][20] = 0;
            for (int i = 0; i < 20; i++)
                printf("%s\n", ans[i]);
        }
        else
        {
            fst = -1;
            best = -1;
            for(int i=0;i<posi;i++)
            {
                node u = ord[i];
                int aux = 0;
                for(node v=0;v<26;v++)
                    if( adj[u][v] && dist[v]+1 > aux )
                    {
                        aux = dist[v] + 1;
                        nxt[u] = v;
                    }
                dist[u] = aux;
                if( aux > best )
                {
                    best = aux;
                    fst = u;
                }
            }
            best++;
            for(int i=0;i<best;i++)
            {
                ans[0][i] = 'a' + fst;
                fst = nxt[fst];
            }
            for (int i = 1; i < best; i++) {
                for (int j = 0; j < best-i; j++) {
                    ans[i][j] = ans[i-1][j+1];
                }
            }
            for (int i = 0; i < min((best+1)/2,20); i++, printf("\n")) {
                for (int j = 0; j < min((best+1)/2, 20); j++)
                    printf("%c", ans[i][j]);
            }
        }
    }
}
