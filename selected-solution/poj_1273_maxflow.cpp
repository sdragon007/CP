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

int main()
{
    int m,n,i,j,l[210],h,t,pre[210];
    long long k,g[210][210],ans;
    bool v[210];
    while (cin>>m>>n)
    {
          memset(g,0,sizeof(g));
          for (;m;m--)
          {
              scanf("%d%d%I64d",&i,&j,&k);
              g[i][j]+=k;
              }
          ans=0;
          while (1)
          {
                memset(v,0,sizeof(v));
                v[l[h=0]=1]=1;
                t=1;
                while (h<t)
                {
                      if (l[h]==n)
                      break;
                      for (i=1;i<=n;i++)
                      if (!v[i] && g[l[h]][i])
                      {
                           v[l[t]=i]=1;
                           pre[t]=h;
                           t++;
                           }
                      h++;
                      }
                if (h==t)
                break;
                k=999999999;
                i=h;
                while (i)
                {
                      k=min(k,g[l[pre[i]]][l[i]]);
                      i=pre[i];
                      }
                ans+=k;
                i=h;
                while (i)
                {
                      g[l[pre[i]]][l[i]]-=k;
                      g[l[i]][l[pre[i]]]+=k;
                      i=pre[i];
                      }
                }
          cout<<ans<<endl;
          }
    return 0;
}
