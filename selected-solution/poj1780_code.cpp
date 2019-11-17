//for a password of length n, it can be uniquely decided by two code of length n-1. for example pass word 345 can be formed as 34->45
//Hence construct a graph with node as all number of length n-1 (with leading 0s)
//and edges between two nodes if the last n-2 digits is same as the first n-2 digits for the two nodes.
//each edge is now representing one unique length n password
//It is clear that by generating the euler path on this graph, we get a sequence of passwords as required
//and this is the shortest sequence since all possible password is visited once only
//Two additional note:
//1. mind the order of search, because problem wants lexicographically smallest sequence
//2. Use stack to simulate backtracking instead of recursive dfs, or RTE
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
using namespace std;

#define M 1001000

int to[M],head[M],len[M],next[M],top,cnt,n,dk,ans[M];
bool vis[M];
int fc[8]={1,10,100,1000,10000,100000,1000000};
struct STACK
{
    int x,p;
}stack[M];
void add(int u,int v,int w)
{
    to[cnt]=v; len[cnt]=w; next[cnt]=head[u]; head[u]=cnt++;
}
void create()
{
    memset(head,-1,sizeof head);
    memset(vis,0,sizeof vis);
    cnt=0;
    for(int i=0,tmp;i<fc[n-1];i++)
    {
        tmp=i%fc[n-2];
        //here the edges are added so that later search will end up with lexico smallest seq
        for(int j=9;j>=0;j--)
            add(i,tmp*10+j,i*10+j);
    }
}
void euler()
{
//here is the main algo to generate euler path. Study how recursive is writeen in non-recursive way, with the aid of a stack
    int u,pos;
    top=2; dk=0;
    stack[1].x=0; stack[1].p=head[0];
    while(top)
    {
        u=stack[top-1].x; pos=stack[top-1].p;
        for(;~pos;pos=next[pos])
            if(!vis[pos])
            {
                stack[top-1].p=pos;
                vis[pos]=true;
                stack[top].p=head[to[pos]]; stack[top].x=to[pos];  ++top;
                break;
            }
        if(pos==-1)
        {
            ans[++dk]=stack[top-1].p;
            top--;
        } 
    }
}
void prt()
{
    for(int i=1;i<n;i++) printf("0");
    for(int i=dk-1;i>=2;i--) printf("%d",len[ans[i]]%10);
    printf("\n");
}
void go()
{
    create();
    euler();
    prt();
}
int main()
{
     while(scanf("%d",&n),n)
    {
        if(n==1) printf("0123456789\n");
        else go();
    }
    return 0;
}
