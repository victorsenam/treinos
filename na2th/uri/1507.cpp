#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main()
{
    int n,q;
    char seq[100000], subs[101];
    map<char, vector<int> > match;

    scanf("%d", &n);
    for(; n > 0 ; n-- )
    {
        match.clear();
        scanf("%s", seq);
        for(int i = 0; seq[i] != 0 && i < 100000 ; i++)
        {
            if( match.find(seq[i]) == match.end() )
                match[seq[i]] = vector<int> (1,i);
            else
                match[seq[i]].push_back(i);
        }

        scanf("%d", &q);
        while( q > 0)
        {
            scanf("%s", subs);
            int pos = -1;
            for(int i = 0; subs[i] != 0 && pos < 100 ; i++)
            {
                if( match.find(subs[i]) == match.end() )
                {
                    pos = 1337;
                    printf("No\n");
                }
                else
                {
                    int ans = *upper_bound(match[subs[i]].begin(), match[subs[i]].end(), pos);
                    printf("%d ", ans);
                    if( ans < pos )
                    {
                        pos = 1337;
                        printf("No\n");
                    }
                    else
                        pos = ans;
                }
            }
                if(pos <= 100)
                printf("Yes\n");
            q--;
        }
    }
}
