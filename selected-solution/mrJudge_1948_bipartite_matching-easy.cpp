#include <bits/stdc++.h>
using namespace std;

int n,m,i,j,k,l[2010];
vector<int>e[1010];
bool v[2010];

bool dfs(int d) {
	if (v[d]) {
		return 0;
	}
	v[d]=1;
    int a,b;
    for (a=e[d].size()-1;a>=0;a--) {
        b=e[d][a];
        if (l[b]==-1 || dfs(l[b])) {
        	l[b]=d;
            return 1;
        }
    }
    return 0;
}

int main() {
    cin>>n>>m;
    for (i=0;i<n;i++) {
        for (j=0;j<m;j++) {
            scanf("%d",&k);
            if (k) {
                e[i].push_back(j+n);
            }
        }
    }
    k=0;
    memset(l,-1,sizeof(l));
    for (i=0;i<n;i++) {
        memset(v,0,sizeof(v));
        if (dfs(i)) {
            k++;
        }
    }
    cout<<k<<endl;
}
