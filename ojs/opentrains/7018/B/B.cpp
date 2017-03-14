#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

const int S = 1000007;
const int E = 107;

char str[S], aux[S];
ll c[E], d;

bool calc(ll x) {
    ll res = 0;
    ll dg = 1;
    for (int i = 0; i < E; i++) {
        res = (res + (dg*c[i])%d)%d;
        dg = (dg*x)%d;
    }
    return res;  
}

int main () {
    int ts = 0;
    while (scanf(" %s", str) && str[0] != '.') {
        int p = 1;
        memset(c, 0, sizeof c);
        while (str[p] != ')') {
            int cf = 1;
            if (str[p] == '-')
            { cf = -1; p++; }
            if (str[p] == '+')
            { p++; }

            int s = 0;
            while (isdigit(str[p]))
                aux[s++] = str[p++];
            aux[s] = 0;

            if (s)
                cf *= atoi(aux);

            int ex = 1;
            if (str[p] == 'n') {
                p++;
                p += (str[p] == '^');

                s = 0;
                while (isdigit(str[p]))
                    aux[s++] = str[p++];
                aux[s] = 0;
            
                if (s)
                    ex *= atoi(aux);
            } else {
                ex = 0;
            }

            c[ex] = cf;    
        }

        p += 2;
        int s = 0;
        while (isdigit(str[p]))
            aux[s++] = str[p++];
        aux[s] = 0;

        d = atoi(aux); 

        
        bool val = 0;
        for (int i = 1; !val && i < E; i++)
            val = calc(i);

        printf("Case %d: ", ++ts);
        if (!val)
            printf("Always an integer\n");
        else
            printf("Not always an integer\n");
    }
}
