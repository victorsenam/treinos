#include <bits/stdc++.h>

using namespace std;

int t;
int n;
int a, b;
char c;
int last;

int main () {
    scanf("%d", &t);
    while (t--) {
        priority_queue<pair<int, int> > sell, buy;
        scanf("%d", &n);
        last = 0;

        for (int i = 0 ; i < n; i++) {
            scanf(" %c", &c);
            if (c == 's') {
                scanf("ell %d shares at %d", &a, &b);
                sell.push(make_pair(-b, a));
            } else {
                scanf("uy %d shares at %d", &a, &b);
                buy.push(make_pair(b, a));
            }

            while (!buy.empty() && !sell.empty() && -sell.top().first <= buy.top().first ) {
                last = -sell.top().first;
                int qt = min(sell.top().second, buy.top().second);
                pair<int, int> aux;
                
                aux = sell.top();
                sell.pop();
                aux.second -= qt;
                if (aux.second > 0)
                    sell.push(aux);

                aux = buy.top();
                buy.pop();
                aux.second -= qt;
                if (aux.second > 0)
                    buy.push(aux);
            }

            if (!sell.empty())
                printf("%d", -sell.top().first);
            else
                printf("-");
            printf(" ");
            if (!buy.empty())
                printf("%d", buy.top().first);
            else
                printf("-");
            printf(" ");
            if (last)
                printf("%d", last);
            else
                printf("-");
            printf("\n");
        }
    }
}
