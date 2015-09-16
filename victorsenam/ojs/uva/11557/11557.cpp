#include <bits/stdc++.h>

using namespace std;

const int N = 107;
const int S = 257;
const int M = 10000;
const string ender = "***END***";

int n;
char names[N];
string codes[N][M];
int lin[N];
char temp[S];

int main () {
	while (scanf("%d", &n) != EOF) {
        int code = 0;
		bool ok = 0;
        for (code = 0; code <= n; code++) {
            lin[code] = 0;
            scanf(" %[ -~]", names[code]);
            printf("%s\n", names[code]);
            while (scanf(" %[ -~]", temp)) {
                printf("%s\n", temp);
                if (strcmp(temp, ender.c_str()) == 0)
                    break;

                int i, j;
                j = 0;
                for (i = 0; temp[i] != '\0'; i++)
                    if (temp[i] != temp[i+1] || temp[i] != ' ')
                        temp[j++] = temp[i];
                temp[j++] = '\0';

                codes[code][lin[code]++] = temp;
            }
		}

        for (int i = 0; i <= n; i++) {
            printf("* %s *\n", names[i]);
            for (int j = 0; j < lin[i]; j++)
                printf("%s\n", codes[i][j].c_str());
            printf("===\n");
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
			printf("%s\n", names[vmax]);
	}
}
