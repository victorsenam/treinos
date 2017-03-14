#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 405;

int n, es = 2;
int head[N], to[N*N], nx[N*N];
int vis[N];
map<string, int> m;
string ss;
int prog[N], p, k;
char s[150];

void dfs (int u) {
    vis[u] = 1;
    for(int e = head[u]; e; e = nx[e]) {
        int v = to[e];    
        if(!vis[v]) dfs(v);
    }
}

bool isProgram() {
    int i = 0;
    while(s[i++] != ':');
    i++;
    string t = s+i;
    if(t.compare("PROGRAM") == 0) return 1;
    return 0;
}

int main () {
    scanf("%d",&n);
    int kk = 1;
    for (int i = 0; i < n; i++) {
        scanf(" %s",s);
        ss = s;
        if(!m.count(ss)) m[ss] = kk++;
        int u = m[ss];
        if(isProgram()) prog[p++] = u;
        scanf("%d",&k);
        for(int j = 0; j < k; j++) {
            scanf(" %s", s);
            ss = s;
            if(!m[ss]) m[ss] = kk++;
            int v = m[ss];
            to[es] = u; nx[es] = head[v]; head[v] = es++;
        }
    }
    for(int i = 0; i < p; i++) dfs(prog[i]);
    int ans = 0;
    for(int i = 1; i <= n; i++) if(!vis[i]) ans++;
    printf("%d\n",ans);
}

