#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

struct act {
    int ini, fim, qtd, ind;
};
bool operator<(const act & a, const act & b) {
    if (a.ini < b.ini) return 1;
    if (a.ini > b.ini) return 0;
    if (a.fim < b.fim) return 1;
    return 0;
}

struct ply {
    int ini, fim, ind;
};
bool operator<(const ply & a, const ply & b) {
    if (a.ini < b.ini) return 1;
    if (a.ini > b.ini) return 0;
    if (a.fim < b.fim) return 1;
    return 0;
}

act a[N];
ply p[N];
int res[N];
int n, m;
set<pair<int, int> > s;
set<pair<int, int> >::iterator it;

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &p[i].ini, &p[i].fim);
        p[i].ind = i;
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &a[i].ini, &a[i].fim, &a[i].qtd);
        a[i].ind = i;
    }

    sort(p, p+n);
    sort(a, a+m);
    
    int ind = 0;
    for (int i = 0; i < n; i++) {
        while (ind < m && a[ind].ini <= p[i].ini) {
            s.insert(make_pair(a[ind].fim, ind));
            ind++;
        }
        
        it = s.lower_bound(make_pair(p[i].fim, 0));

        while (it != s.end() && a[it->second].qtd == 0) {
            s.erase(it);
            it = s.lower_bound(make_pair(p[i].fim, 0));
        }

        if (it == s.end()) {
            printf("NO\n");
            
            /*
            printf("peca %d %d [%d]\n", p[i].ini, p[i].fim, i);
            for (it = s.begin(); it != s.end(); it++)
                printf("%d %d %d [%d]\n", a[it->second].ini, a[it->second].fim, a[it->second].qtd, a[it->second].ind);
            */
            
            return 0;
        }
        
       // printf("peca %d %d [%d] -> ator %d %d %d [%d]\n", p[i].ini, p[i].fim, i, a[it->second].ini, a[it->second].fim, a[it->second].qtd, a[it->second].ind);

        res[p[i].ind] = a[it->second].ind;
        if (a[it->second].qtd-- == 1)
            s.erase(it);
    }
    
    printf("YES\n");
    for (int i = 0; i < n; i++)
        printf("%d ", res[i]+1);
    printf("\n");
}
