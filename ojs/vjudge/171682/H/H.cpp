#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back
#define double long double

int ts;
const int N = 1e3;
stack<vector<ll> > st;
string str;

void rev (vector<ll> & a) {
    for (int i = 0; i < a.size(); i++)
        a[i] = -a[i];
    a[0]++;
}

vector<ll> prod (vector<ll> & a, vector<ll> & b) {
    vector<ll> res(a.size() + b.size() - 1, 0);
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < b.size(); j++)
            res[i+j] += a[i]*b[j];
    return res;
}

double eval (vector<ll> & a) {
    double res = 0;
    for (ll i = 0; i < a.size(); i++) {
        res += (double)(i*a[i])/(double)(i+1);
    }
    return res;

}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> ts;
    while (ts--) {
        cin >> str;

        for (int i = str.size() - 1; i >= 0; i--) {
            if (str[i] == 'x') {
                st.push(vector<ll>({0,1}));
            } else {
                vector<ll> a = st.top();
                st.pop();
                vector<ll> b = st.top();
                st.pop();
                if (str[i] == 'm') {
                    rev(a);
                    rev(b);
                }
                st.push(prod(a,b));
                if (str[i] == 'm')
                    rev(st.top());
            }
        }

        cout << setprecision(20) << eval(st.top()) << endl;
        st.pop();
        assert(st.empty());
    }
}
