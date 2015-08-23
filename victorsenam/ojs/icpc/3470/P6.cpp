#include <bits/stdc++.h>

using namespace std;

int main ()
{
    int n, d, ctr;
    bool students[100];
    while (scanf("%d %d", &n, &d) != EOF && n != 0 && d != 0)
    {
        ctr = 0;
        for (int i = 0; i < n; i++)
            students[i] = true;

        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int input;
                scanf("%d", &input); 
                if (input == 0 && students[j])
                {
                    students[j] = false;
                    ctr++;
                }
            }
        }

        if (ctr < n) printf("yes\n");
        else printf("no\n");
    }
}
