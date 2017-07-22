#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

size_t len;
int n;

stack<pii> st[300];
stack<vector<char> > scope;
string line;

bool ischar (char c) {
    return (c >= 'a' && c <= 'z');
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n;
    scope.push(vector<char>(0));

    getline(cin, line);
    for (int i = 1; i <= n; i++) {
        getline(cin, line);
        
        for (int j = 0; j < line.size(); j++) {
            if (line[j] == '{') {
                scope.push(vector<char>(0));
            } else if (line[j] == '}') {
                for (char c : scope.top())
                    st[c].pop();
                scope.pop();
            } else if (ischar(line[j])) {
                scope.top().push_back(line[j]);
                if (!st[line[j]].empty()) {
                    cout << i << ":" << j+1 << ": warning: shadowed declaration of " << line[j] << ", the shadowed position is ";
                    cout << st[line[j]].top().first << ":" << st[line[j]].top().second+1 << endl;
                }
                st[line[j]].push(pii(i, j));
            }
        }
    }

}
