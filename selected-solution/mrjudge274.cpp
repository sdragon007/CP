#include <bits/stdc++.h>
using namespace std;

#include<fstream>
//FILE *fin=freopen("a.in","r",stdin);
//FILE *fout=freopen("a.out","w",stdout);

int main() {
	int n,m,i,j,k,count[1100];
	cin>>n>>m;
	char s[110],c;
	vector<int> g[1100];
	memset(count,0,sizeof(count));
	for (;m;m--) {
		scanf("%s",s);
		for (i=0;i<strlen(s);i++) {
			if (!isdigit(s[i])) {
				c=s[i];
				s[i]=' ';
			}
		}
		sscanf(s,"%d%d%d",&i,&j,&k);
		if (c==',') {
			g[i].push_back(j);
			g[i].push_back(k);
			count[j]++;
			count[k]++;
		}
		else {
			g[i].push_back(k);
			g[j].push_back(k);
			count[k]+=2;
		}
	}
	queue <int> q;
	vector <int> ans;
	for (i=1;i<=n;i++) {
		if (!count[i]) {
			q.push(i);
		}
	}
	while (!q.empty()) {
		i=q.front();
		q.pop();
		ans.push_back(i);
		for (j=0;j<g[i].size();j++) {
			count[g[i][j]]--;
			if (!count[g[i][j]]) {
				q.push(g[i][j]);
			}
		}
	}
	if (ans.size()==n) {
		for (i=0;i<n-1;i++) {
			printf("%d ",ans[i]);
		}
		printf("%d\n",ans[n-1]);
	}
	else {
		printf("0\n");
	}
    return 0;
}
