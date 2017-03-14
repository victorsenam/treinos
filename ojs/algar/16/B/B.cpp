#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+8;
ll n;
char str[N];


int main () {
    while (scanf(" %s %d", str, &n) != EOF && str[0] != '0') {
        vector<ll> v;

        stack<ll> num;
        stack<char> op;
        
        int i = 0;
        while (str[i] != ']') {
            while (str[i] == '[') i++;
            ll a;
            sscanf(str+i, " %lld", &a);
            num.push(a);
            
            if (str[i] == '-') i++;
            while (isdigit(str[i])) i++;

            if (str[i] == ']') break;
            op.push(str[i]);

            i++;
        }

        for (int i = 0; i < n; i++)
            v.push_back(num.top());
        num.pop();

        while (!num.empty()) {
            if (op.top() == '+') {
                for (int i = n-1; i > 0; i--)
                    v[i] = v[i-1];
                v[0] = num.top();
                for (int i = 1; i < n; i++)
                    v[i] += v[i-1];
            } else {
                v[0] *= num.top();
                for (int i = 1; i < n; i++)
                    v[i] *= v[i-1];
            }

            op.pop(); num.pop();
        }

        for (int i = 0; i < n; i++) {
            if (i) putchar(' ');
            printf("%lld", v[i]);
        }
        printf("\n");
    }
}
