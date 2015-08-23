#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#define debugs(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...) //
#define debugs(...) //
#endif

#define N 200000

int n;
int in[N], ord[N], out[N];
int pos, sem;
multiset<int> st;

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &in[i]);

    while (true) {
        debugs("in: ");
        for (int i = 0; i < n; i++) {
            ord[i] = in[i];
            debugs("%d ", in[i]);
        }
        debugs("\n");

        st.clear();
        sort(ord, ord+n);
        for (int i = n-1; i >= 0; i--) {
            pos = upper_bound(ord, ord+n, in[i]) - ord - 1;
            pos -= st.count(in[i]);
            st.insert(in[i]);

            out[pos] = in[i] - (pos-i);
            debug("pos de %d[%d] em ord e %d, vira %d", in[i], i, pos, out[pos]);
        }

        debugs("ord: ");
        for (int i = 0; i < n; i++)
            debugs("%d ", ord[i]);
        debugs("\n");

        debugs("out: ");
        for (int i = 0; i < n; i++)
            debugs("%d ", out[i]);
        debugs("\n");

        for (sem = 1; sem < n; sem++)
            if (out[sem-1] > out[sem]) break;

        if (sem >= n) {
            for (int i = 0; i < n; i++) {
                printf("%d", out[i]);
                if (i < n-1) printf(" ");
            }
            printf("\n");
            return 0;
        }

        for (sem = 0; sem < n; sem++)
            if (out[sem] != in[sem]) break;

        if (sem >= n) {
            printf(":(\n");
            return 0;
        }
        
        for (int i = 0; i < n; i++) in[i] = out[i];
    }
}
