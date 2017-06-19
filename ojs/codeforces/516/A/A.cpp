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

int n;
string str;
vector<char> res;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    cin >> str;

    for (int i = 0; i < n; i++) {
        if (str[i] == '0' || str[i] == '1') continue;
        if (str[i] == '2' || str[i] == '3' || str[i] == '5' || str[i] == '7') {
            res.push_back(str[i]);
        } else if (str[i] == '4') {
            res.push_back('2');
            res.push_back('2');
            res.push_back('3');
        } else if (str[i] == '6') {
            res.push_back('3');
            res.push_back('5');
        } else if (str[i] == '8') {
            res.push_back('2');
            res.push_back('2');
            res.push_back('2');
            res.push_back('7');
        } else if (str[i] == '9') {
            res.push_back('2');
            res.push_back('3');
            res.push_back('3');
            res.push_back('7');
        }
    }

    sort(res.begin(), res.end(), [] (char a, char b) { return b < a; });
    for (char c : res)
        cout << c;
    cout << endl;
}
