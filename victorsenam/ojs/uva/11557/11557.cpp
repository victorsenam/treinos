#include <bits/stdc++.h>

using namespace std;

const int N = 107;
const int S = 257;
const int M = 10000;
const string ender = "***END***";

int n;
string names[N];
int lin[N];
string codes[N][M];
char temp[S];

int main () {
	while (scanf("%d", &n) != EOF) {
		int code = 0;
			lin[0] = 0;
		bool ok = 0;
		while (code <= n && scanf(" %[ -~]", temp)) {
			if (strcmp(temp, ender.c_str())) {
				lin[code++] = 0;
				ok = 0;
				continue;
			}
			if (!ok) {
				names[code] = temp;
				ok = 1;
			}
			int i, j;
			j = 0;
			for (i = 0; temp[i] != '\0'; i++) {
				if (temp[i] != temp[i+1] || temp[i] != ' ')
					temp[j++] = temp[i];
			}
			temp[j++] = ' ';

			codes[code][lin[code]++] = temp;
		}

		int maxi = 0;
		int vmax = -1;
		for (int i = 0; i < n; i++) {
			int att = 0;
			for (int j = 0; j < min(lin[i], lin[n]); j++) {
				if (codes[i][j] == codes[n][j])
					att++;
				if (att > maxi) {
					vmax = i;
					maxi = att;
				}
			}
		}
		if (maxi == 0)
			printf("%d\n", 0);
		else
			printf("%s\n", names[vmax].c_str());
	}
}
