#include <cstdio>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 100007

struct bit {
    int n;
    num freq[N];

    void set (int siz) {
        n = siz;
        for (int i = 0; i <= n; i++)
            freq[i] = 0;
    }

    void insert (int i, num val) {
 //       printf("Insert %d on %d\n", val, i);
        while (i <= n) {
            freq[i] += val;
            i += i&-i;
        }
    }

    num count (int i) {
 //       printf("Count %d\n", i);
        num sum = 0;
        while (i > 0) {
            sum += freq[i];
            i -= i&-i;
        }
        return sum;
    }
};

int n, m, a, b, noe;
char c;
int chs[N], pre[N];
bool ex[N];
bit tree;
int value[2*N];
int next[2*N];
int cnt;

int dfs (int v) {
    if (pre[v] != -1) return 0;
    
    pre[v] = cnt++;
    chs[v] = 1;

    int u = next[v];
    while (u != v) {
        chs[v] += dfs(value[u]);
        u = next[u];
    }

    return chs[v];
}

int main () {
    scanf("%d", &n);
    
    noe = n-1;
    tree.set(n);

    for (int i = 0; i < n; i++) {
        value[i] = i;
        next[i] = i;
        tree.insert(i+1, 1);
        pre[i] = -1;
        chs[i] = 0;
        ex[i] = 1;
    }
    for (int i = 0; i < n-1; i++) {
        scanf("%d %d", &a, &b);
        a--; 
        b--;
        value[noe] = b;
        next[noe] = next[a];
        next[a] = noe;
        noe++;
        
        value[noe] = a;
        next[noe] = next[b];
        next[b] = noe;
        noe++;
    }

    cnt = 1;
    dfs(0);

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf(" %c %d", &c, &a);
        a--;
        if (c == 'Q')
            printf("%d\n", tree.count(pre[a]+chs[a]-1) - tree.count(pre[a] - 1));
        else {
            tree.insert(pre[a], 1 - (ex[a])*2);
            ex[a] = !ex[a];
        }
    }
}
