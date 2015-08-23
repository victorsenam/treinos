#include <bits/stdc++.h>

using namespace std;

int main()
{
    int vf, vg, d;
    while (scanf("%d %d %d", &d, &vf, &vg) != EOF)
    {
        if (vf*vf*(d*d+144) <= 144*vg*vg)
            printf("S\n");
        else printf("N\n");
    }
}
