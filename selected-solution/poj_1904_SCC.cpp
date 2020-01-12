#include<stdio.h>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<vector>
using namespace std;

#define isdigit(x) (x>='0' && x<='9')
const int N = 2010;
const int M = 205000;

int n, tot, depth, top, ct, h[N+N], low[N+N], d[N+N], f[N+N], stack[N+N], nxt[M], v[M];
bool instack[N+N], map[N][N];

vector <int> ans;

void add(int a, int b)
{
    v[tot] = b;
    nxt[tot] = h[a];
    h[a] = tot++;
}

void dfs(int u, int &depth)
{
    int p, x;
    d[u] = low[u] = depth++;
    stack[++top] = u;
    instack[u] = true;
    for(p = h[u]; p != -1; p = nxt[p])
    {
        if(d[v[p]] == -1)
        {
            dfs(v[p], depth);
            low[u] = min(low[u], low[v[p]]);
        }
        else if(instack[v[p]])
            low[u] = min(low[u], d[v[p]]);
    }
    if(low[u] == d[u])
    {
        while(top)
        {
            x = stack[top--];
            instack[x] = false;
            f[x] = ct;
            if(x == u)  break;
        }
        ct++;
    }
}

int main()
{
    int i, j, k, x, len;
    char ss[1001000];
    memset(map, false, sizeof(map));
    gets(ss);
    sscanf(ss,"%d",&n);
    tot = 0;
    memset(h, -1, sizeof(h));
    for(i = 1; i <= n; i++)
    {
        gets(ss);
        sscanf(ss,"%d",&k);
        for (j=0;(ss[j] && isdigit(ss[j]));j++);
        while(k--)
        {
            sscanf(ss+j,"%d", &x);
            map[i][x] = true;
            add(i, x+n);
            for (;(ss[j] && ss[j]==' ');j++);
            for (;(ss[j] && isdigit(ss[j]));j++);
        }
    }
    for(i = 1; i <= n; i++)
    {
        scanf("%d", &x);
        add(x+n, i);
    }
    memset(d, -1, sizeof(d));
    memset(f, -1, sizeof(f));
    depth = top = ct = 0;
    memset(instack, 0, sizeof(instack));
    for(i = 1; i <= n; i++)
        if(d[i] == -1)
            dfs(i, depth);
    for(i = 1; i <= n; i++)
    {
        ans.clear();
        for(j = n+1; j <= (n<<1); j++)
            if(map[i][j-n] && f[j]==f[i])
                ans.push_back(j-n);
        len = ans.size();
        printf("%d", len);
        for(j = 0; j < len; j++)  printf(" %d", ans[j]);
        printf("\n");
    }
    return 0;
}
