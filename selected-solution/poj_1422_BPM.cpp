#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<iomanip>
#include<vector>
#include<list>
#include<iterator>
#include<stack>
#include<queue>
using namespace std;

#include<fstream>
//FILE *fin=freopen("a.in","r",stdin);
//FILE *fout=freopen("a.out","w",stdout);

int g[200][200],s[200],n,m,t,i,j,l[400];
bool v[200];

bool dfs(int d)
{
     if (v[d])
     return 0;
     v[d]=1;
     int k,w;
     for (k=0;k<s[d];k++)
     if (!l[g[d][k]] || dfs(l[g[d][k]]))
     {
           l[g[d][k]]=d;
           return 1;
           }
     return 0;
}

int main()
{
    cin>>t;
    for (;t;t--)
    {
        cin>>n>>m;
        memset(s,0,sizeof(s));
        for (;m;m--)
        {
            scanf("%d%d",&i,&j);
            g[i][s[i]++]=j+n;
            }
        m=0;
        memset(l,0,sizeof(l));
        for (i=1;i<=n;i++)
        {
            memset(v,0,sizeof(v));
            if (dfs(i))
            m++;
            }
        printf("%d\n",n-m);
        }
    return 0;
}
