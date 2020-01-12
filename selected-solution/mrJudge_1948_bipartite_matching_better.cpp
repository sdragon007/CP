#include <bits/stdc++.h>
using namespace std;

int n,m,i,j,k,d[2010],l[2010];
vector<int>e[1010];
bool v[2010];

bool bfs() {
	int i,j,k;
	queue<int>q;
    for (i=1;i<=n;i++) {
    	if (!l[i]) {
    		d[i]=0;
    		q.push(i);
		}
		else {
			d[i]=-1;
		}
	}
	d[0]=-1;
	while (!q.empty()) {
		i=q.front();
		q.pop();
		if (d[0]==-1 || d[0]>d[i]) {
			for (j=e[i].size()-1;j>=0;j--) {
				k=e[i][j];
				if (d[l[k]]==-1) {
					d[l[k]]=d[i]+1;
					q.push(l[k]);
				}
			}
		}
	}
    return d[0]>-1;
}

bool dfs(int i) {
	int j,k;
	if (i) {
		for (j=e[i].size()-1;j>=0;j--) {
			k=e[i][j];
			if (d[l[k]]==d[i]+1) {
				if (dfs(l[k])) {
					l[i]=k;
					l[k]=i;
					return 1;
				}
			}
		}
		d[i]=-1;
		return 0;
	}
	return 1;
}

int main() {
    cin>>n>>m;
    for (i=1;i<=n;i++) {
        for (j=1;j<=m;j++) {
            scanf("%d",&k);
            if (k) {
                e[i].push_back(j+n);
            }
        }
    }
    k=0;
    memset(l,0,sizeof(l));
    while (bfs()) {
    	for (i=1;i<=n;i++) {
    		if (!l[i] && dfs(i)) {
    			k++;
			}
		}
	}
    cout<<k<<endl;
}
