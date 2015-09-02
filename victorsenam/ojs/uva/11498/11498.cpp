#include <bits/stdc++.h>

using namespace std;

int x, y, n, dx, dy;

int main () {
	while (scanf("%d", &n) != EOF && n) {
		scanf("%d %d", &dx, &dy);

		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			x -= dx;
			y -= dy;

			if (x == 0 || y == 0)
				printf("divisa\n");
			else if (x > 0) {
				if (y > 0)
					printf("NE\n");
				else
					printf("SE\n");
			} else {
				if (y > 0)
					printf("NO\n");
				else
					printf("SO\n");
			}
		}
	}
}
