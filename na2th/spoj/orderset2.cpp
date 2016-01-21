#include <bits/stdc++.h>
using namespace std;
const int T = 2e5+7;

int tree, l, r, ts;
int lc[T], rc[T];
int x[T], y[T], sum[T];

void update(int t)
{
    if(t == -1) return;
    sum[t] = 1;
    if(lc[t] != -1) sum[t] += sum[lc[t]];
    if(rc[t] != -1) sum[t] += sum[rc[t]];
}

void split(int t, int k)
{
    if(t == -1) return (void)(l = r = -1);
    if(k <= x[t]) split(lc[t], k), lc[t] = r, r = t;
    else          split(rc[t], k), rc[t] = l, l = t;
    update(t);
}

int merge(int tl, int tr)
{
    int ans = tr;
    if(min(tl,tr) == -1) return max(tl, tr);
    if(y[tl] < y[tr]) lc[tr] = merge(tl, lc[tr]);
    else rc[ans=tl] = merge(rc[tl], tr);
    update(tl); update(tr);
    return ans;
}

int find(int t, int k)
{
    if(t == -1) return 0;
    if(x[t] == k) return 1;
    if(x[t] < k) return find(rc[t], k);
    return find(lc[t], k);
}

int insert(int tree, int k)
{
    if(find(tree,k)) return tree;
    x[ts] = k; sum[ts] = 1;
    lc[ts] = rc[ts] = -1;
    split(tree, k);
    return merge(merge(l,ts++),r);
}

int remove(int t, int k)
{
    if(t == -1) return -1;
    if(x[t] == k) return merge(lc[t], rc[t]);
    if(k < x[t]) lc[t] = remove(lc[t], k);
    else rc[t] = remove(rc[t], k);
    update(t);
    return t;
}

int query(int t, int k)
{
    if(t == -1) return -1;
    int sl = (lc[t] == -1 ? 0 : sum[lc[t]]);
    if(k <= sl) return query(lc[t], k);
    k -= sl + 1;
    return k? query(rc[t], k): t;
}

int q;
int main()
{
    srand(time(NULL));
    for(int i=0;i<T;i++) y[i] = i;
    random_shuffle(y, y+T);
    tree = -1;

    scanf(" %d", &q);
    while(q--)
    {
        char cmd;
        int in;
        scanf(" %c%d", &cmd, &in);
        if(cmd == 'I') tree = insert(tree, in);
        else if(cmd == 'D') tree = remove(tree, in);
        else if(cmd == 'C')
        {
            split(tree, in);
            printf("%d\n", l != -1 ? sum[l] : 0);
            tree = merge(l, r);
        }
        else
        {
            if(in > sum[tree]) printf("invalid\n");
            else   printf("%d\n", x[query(tree, in)]);
        }
    }
}
