#include<stdio.h>
#include<iostream>
#include<string.h>
#include<queue>
using namespace std;
#define arr 103 
#define int_max 214748364
int S,T,M,N;
int room[1001],belong[1001],map[103][103],pre[103],flow[103];

int BFS()
{
    int i,j,k,v,u;
    for(i=S;i<=T;i++) flow[i]=int_max,pre[i]=-1;
    queue<int>que;
    pre[S]=0;
    que.push(S);
    while(!que.empty())
    {
           v=que.front();
           que.pop();
           for(u=1;u<=T;u++)
           {
               if(u==S||pre[u]!=-1||map[v][u]==0) continue;
               pre[u]=v;
               flow[u]=min(flow[v],map[v][u]);
               que.push(u);
           }
    }
    if(flow[T]==int_max) return -1;
    else return flow[T];
}
                     
        
    
int EK()
{
    int i,j,now,last,temp,ans=0;
    while(1)
    {
            if((temp=BFS())==-1) break;
            ans+=temp;
            now=T;
            while(now!=S)
            {
                 last=now; now=pre[now];
                 map[now][last]-=temp; map[last][now]+=temp;
            }
    }
    return ans;
}

int main()
{
    int i,j,t,num;
    while(scanf("%d%d",&M,&N)!=EOF)
    {
        S=0; T=N+1;
        memset(map,0,sizeof(map));
        for(i=1;i<=M;i++) scanf("%d",&room[i]),belong[i]=0;
        for(i=1;i<=N;i++)
        {
            scanf("%d",&num);
            for(j=1;j<=num;j++)
            {
                scanf("%d",&t);
                if(belong[t]==0)
                {
                    belong[t]=i;
                    map[S][i]+=room[t];
                }
                else
                {
                    map[belong[t]][i]=int_max;
                }
            }
            scanf("%d",&t);
            map[i][T]=t;
        }
        int ans=EK();
        printf("%d\n",ans);
    }
}
