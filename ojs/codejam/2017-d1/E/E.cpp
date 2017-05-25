#include "query_of_death.h"
#include <message.h>

#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int c, idx, n;

int main () {
    c = NumberOfNodes();
    idx = MyNodeId();

    n = GetLength();

    if (!idx) {
        int mn = n;
        for (int i = 1; i < c; i++) {
            Receive(i);
            mn = min(mn, GetInt(i));
        }

        assert(mn != n);

        int sm = 0;
        for (int i = 0; i < n; i++) 
            if (i != mn)
                sm += GetValue(i);
        sm += GetValue(mn);
        
        printf("%d\n", sm);
    } else {
        int mn = n;
        for (int i = 0; mn == n && i < n; i++) {
            int a = GetValue(i);
            int k = 50;
            while (mn == n && k--) {
                if (a != GetValue(i))
                    mn = i;
            }
        }

        //assert(mn != n);

        PutInt(0, mn);
        Send(0);
    }
}
