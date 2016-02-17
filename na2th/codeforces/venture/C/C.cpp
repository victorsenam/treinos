#include <bits/stdc++.h>
using namespace std;
typedef long long num;

int hn, hm, reach;
set<int> conf, seen;

int main()
{
    scanf(" %d%d", &hn, &hm);
    hn *= 2; hm *= 3;
    reach = min(hn, hm)+1;
    for(int i=6;i<reach;i+=6) conf.insert(i);

    while(!conf.empty())
    {
        conf.erase(conf.begin());
        if(hn + 2 <= hm + 3)
        {
            hn += 2;
            if(seen.count(hn)) conf.insert(hn);
            seen.insert(hn);
        }
        else
        {
            hm += 3;
            if(seen.count(hm)) conf.insert(hm);
            seen.insert(hm);
        }
    }

    printf("%d\n", max(hn, hm));
}
