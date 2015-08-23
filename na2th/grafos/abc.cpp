#include <bits/stdc++.h>

using namespace std;

char grid[100][100];
int visited[10000],
    dx[8] = {-1, 0, 1,-1,1,-1,0,1},
    dy[8] = {-1,-1,-1, 0,0, 1,1,1};

int dfs(int pos, int h, int w)
{
    char key = grid[pos/w][pos%w];
    if( key == 'Z' )
        return 1;
    int range = 1, path;

    for(int m = 0; m < 9; m++)
    {
        int x = pos%w + dx[m],
            y = pos/w + dy[m];
        if( visited[y*w + x] < 8 )
            if( x < w && x >= 0 && y < h && y >= 0 && (grid[y][x] == key+1) )
            {
                path = 1 + dfs((y*w + x), h, w);
                range = max(path, range);
                visited[y*w + x] += 1;
            }
    }
    return range;
}

int main()
{
    int h, w, c = 1, ans, A[10000], As;
    char line[100];

    while( scanf("%d %d", &h, &w) > 0 && h != 0 && w != 0 )
    {
        // limpar a casa
        memset(visited, 0, sizeof(visited));
        As = 0;
        ans = 0;

        for(int i = 0; i < h ; i++)
        {
            scanf("%s ", line);
            for(int j = 0; j < w ; j++)
            {
                if( line[j] == 'A' )
                    A[As++] = i*w + j;
                grid[i][j] = line[j];
            }
        }

        for(int i = 0; i < As ; i++ )
            ans = max( ans, dfs(A[i],h,w) );
        printf("Case %d: %d\n", c++ , ans);
    }
}
