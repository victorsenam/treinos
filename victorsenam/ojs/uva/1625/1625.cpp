#include <bits/stdc++.h>

using namespace std;

const int K = 28;
const int N = 5007;

typedef unsigned long long int num;

int n, m, t;
num isOpen[2][N];
int att[K];
int tot[2][K];
int memo[N][N];
char str[2][N];
int vis[N][N];
int turn;

void printanums (num v) {
	printf("%llu: ", v);
	while (v) {
		printf("%d ", v%2);
		v = (v>>1);
	}
	printf("\n");
}

int pd (int i, int j) {
    if (i == n && j == m)
        return 0;

    int & me = memo[i][j];

    if (vis[i][j] == turn)
        return me;
    
    me = INT_MAX;

    if (i < n)
        me = min(me, pd(i+1, j));
    if (j < m)
        me = min(me, pd(i, j+1));

	me = max(me, me + __builtin_popcount(isOpen[0][i]|isOpen[1][j]));
    return me;
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf(" %s %s", str[0], str[1]);
        n = strlen(str[0]);
        m = strlen(str[1]);

        turn++;
        for (int k = 0; k < 26; k++)
            tot[0][k] = tot[1][k] = 0;
		
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= m; j++)
				memo[i][j] = -1;

        for (int i = 0; i < n; i++)
            tot[0][str[0][i]-'A']++;
        for (int i = 0; i < m; i++)
            tot[1][str[1][i]-'A']++;

		for (int k = 0; k < 26; k++)
			att[k] = 0;
		for (int i = 0; i < n; i++) {
			int aux = str[0][i] - 'A';
			att[aux]++;

			if (att[aux] > 0 && att[aux] < tot[0][aux])
				isOpen[0][i] = (isOpen[0][i-1]|(1llu<<aux));
			else
				isOpen[0][i] = (isOpen[0][i-1]&(~(1llu<<aux)));
		}

		for (int k = 0; k < 26; k++)
			att[k] = 0;
		for (int j = 0; j < m; j++) {
			int aux = str[1][j] - 'A';
			att[aux]++;

			if (att[aux] > 0 && att[aux] < tot[1][aux])
				isOpen[1][j] = (isOpen[1][j-1]|(1llu<<aux));
			else
				isOpen[1][j] = (isOpen[1][j-1]&(~(1llu<<aux)));
		}

        printf("%d\n", pd(0,0));
    }
}
