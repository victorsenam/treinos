#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

string beat[][2] = {{"scissors", "paper"}, {"paper", "rock"}, {"rock", "moon"}, {"moon", "sun"}, {"sun", "scissors"}, {"scissors", "moon"}, {"moon", "paper"}, {"paper", "sun"}, {"sun", "rock"}, {"rock", "scissors"}};


int n;
string a, b;

int main () {
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> a >> b;
		if (a == b) {
			printf("drew\n");
			continue;
		}
		bool ok = 0;
		for (int j = 0; j < 10; j++) if (beat[j][0] == a && beat[j][1] == b) {
			printf("akira\n");
			ok = 1;
			break;
		}
		if (ok == 0)
			printf("hideki\n");
	}
}

