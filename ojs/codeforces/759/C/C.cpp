#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 1e6+7;
const int M = 1e4+3;

int n;
int m;
int p[N];
int t[N];
int x[N];

vector<int> v[M];
int c[M];

int curr;
int q[M];

int build (int k) {
    v[k].clear();
    c[k] = 0;
    for (int i = k*m; i < n && i < (k+1)*m; i++) {
        //printf(" %d", i);
        if (t[i] == 1) {
            //printf("[%d]", x[i]);
            v[k].push_back(x[i]);
        } else if (t[i] == 0) {
            //printf("[%d]", -1);
            if (v[k].empty())
                c[k]++;
            else
                v[k].pop_back();
        }
    }

    //printf(" | basin %d : rm %d put", k, c[k]);
    //for (int i : v[k])
        //printf(" %d", i);
    //printf("\n");
}

int get () {
    stack<int> curr;
    for (int i = 0; i < m; i++)
        q[i] = 0;

    for (int i = 0; i < m; i++) {
        int rm = c[i];
        while (!curr.empty() && rm) {
            int at = curr.top();
            int d = min(rm, q[at]);
            q[at] -= d;
            rm -= d;
            if (!q[at]) 
                curr.pop();
        }

        q[i] = v[i].size();
        if (q[i])
            curr.push(i);
    }

    if (curr.empty())
        return -1;
    int at = curr.top();
    return v[at][q[at]-1];
}

int main () {
    scanf("%d", &n);

    m = 1;
    while (m*m < n)
        m++;

    for (int i = 0; i <n ; i++)
        t[i] = -1;

    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
        p[i]--;
        scanf("%d", &t[p[i]]);
        
        if (t[p[i]] == 1)
            scanf("%d", &x[p[i]]);

        build(p[i]/m);
        printf("%d\n", get());
    }
}
