#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int len[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int d;
char str[30];

int main () {
	scanf(" %s", str);

	if (str[0] == 'M')
		d = 0;
	else if (str[0] == 'T' && str[1] == 'u')
		d = 1;
	else if (str[0] == 'W')
		d = 2;
	else if (str[0] == 'T')
		d = 3;
	else if (str[0] == 'F')
		d = 4;
	else if (str[1] == 'a')
		d = 5;
	else
		d = 6;

	int r = 0;
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < len[i]; j++) {
			if (d == 4 && j == 12)
				r++;
			d++;
			d %= 7;
		}
	}

	printf("%d\n", r);
}
