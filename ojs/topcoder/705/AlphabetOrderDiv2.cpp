#line 2 "AlphabetOrderDiv2.cpp"
#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int N = 700;

vector<int> adj[N];
int visi[N];

class AlphabetOrderDiv2 {
    public:
    bool dfs (int u) {
        if (visi[u] == 1) return 0;
        if (visi[u] == 2) return 1;
        visi[u] = 1;
        for (int i = 0; i < adj[u].size(); i++)
            if (!dfs(adj[u][i]))
                return 0;
        visi[u] = 2;
        return 1;
    }

    string isOrdered(vector <string> words) {
        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j < words[i].size() - 1; j++) {
                if (words[i][j] != words[i][j+1])
                    adj[words[i][j] - 'a'].push_back(words[i][j+1] - 'a');
            }
        }

        for (int i = 'a'; i <= 'z'; i++)
            if (!dfs(i-'a')) return "Impossible";
        return "Possible";
    }
};


// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
