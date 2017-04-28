#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 2e5+6;

struct node {
    int cl, op, in;

    bool operator < (const node & ot) {
        return cl < ot.cl;
    }
};

char str[N];
int n;
node v[N], u[N];

void fail () {
    printf("NO\n");
    exit(0);
}

int solve (node * v, node * vf) {
    sort(v, vf);

    int n = vf - v;
    debug("--\n");
    int cred = 0;
    for (int i = 0; i < n; i++) {
        debug("%d %d\n", v[i].cl, v[i].op);
        if (v[i].cl > cred)
            fail();
        assert(v[i].op - v[i].cl >= 0);
        cred += v[i].op - v[i].cl;
    }
    debug("%d\n", cred);
    return cred;
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf(" %s", str);
        int c = 0, mn = 0;
        for (int j = 0; str[j]; j++) {
            if (str[j] == '(')
                c++;
            else
                c--;
            mn = min(mn, c);
        }

        v[i].cl = - mn;
        v[i].op = c - mn;
        v[i].in = i + 1;
    }

    int na = 0, nb = 0;
    for (int i = 0; i < n; i++) {
        if (v[i].op >= v[i].cl)
            u[na++] = v[i];
        else {
            swap(v[i].cl, v[i].op);
            u[n-1-(nb++)] = v[i];
        }
    }

    int a = solve(u, u+na);
    int b = solve(u+na, u+na+nb);

    if (a != b)
        fail();

    printf("YES\n");
    for (int i = 0; i < na; i++)
        printf("%d ", u[i].in);
    for (int i = n-1; i >= na; i--)
        printf("%d ", u[i].in);
    printf("\n");
}
