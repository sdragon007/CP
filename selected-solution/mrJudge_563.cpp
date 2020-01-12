#include <bits/stdc++.h>
using namespace std;

#define ls (id<<1)
#define rs ((id<<1)^1)
#define mid ((l+r)>>1)
#define LBS(i) ((i)&-(i))
#define max(i,j) ((i)>(j)?(i):(j))
#define min(i,j) ((i)<(j)?(i):(j))
typedef long long ll;

const int N = 100001;
const int M = 1000001;

int n,m;
vector <int> a[N];
int i,j,d[N],low[N],s,depth,st[N],top,in[N],t[N],f[N];

void tarjan(int u)
{
    int i,x;
    d[u]=low[u]=depth++;
    st[++top]=u;
    in[u]=1;
    for(i=a[u].size()-1;i>=0;i--) {
    	x=a[u][i];
    	if (d[x]==-1) {
            tarjan(x);
            low[u]=min(low[u],low[x]);
        }
        else if(in[x]) {
            low[u]=min(low[u],d[x]);
        }
        else {
        	t[u]=n;
		}
    }
    if(low[u]==d[u]) {
    	i=0;
        while(top) {
            x=st[top--];
            in[x]=0;
            i+=t[x]+1;
            if(x==u) {
            	break;
			}
        }
        if (top) {
        	t[st[top]]+=i;
		}
		s=min(s,i);
    }
}

int main() {
    cin>>n>>m;
    s=n;
    for (;m;m--) {
    	scanf("%d%d",&i,&j);
    	a[i].push_back(j);
	}
	memset(t,0,sizeof(t));
	memset(d,-1,sizeof(d));
	memset(in,0,sizeof(in));
	depth=top=0;
	for (i=1;i<=n;i++) {
		if (d[i]==-1) {
			tarjan(i);
		}
	}
	cout<<s<<endl;
}
