//standard solution (ElogE)
//be careful about stackover flow for dfs tree building, below code use recursive tree traversal to establish father information
//remember to merge nodes for MST edges anytime after labeling
#include <bits/stdc++.h>
using namespace std;

int f[310000],father[310000],father_edge_id[310000],depth[310000],s,a[310000],sa;
bool v[310000];
int st[310000],ss;
int mst_s[310000],n,ne,i,j,rx,ry,k,ans[310000],in_mst[310000];
pair<int,int> e[310000],p,mst_e[610000];

//union find get root
inline int root(int x) {
	int p=x,q=x,r;
	while (p!=f[p]) {
		p=f[p];
	}
	while (q!=p) {
		r=f[q];
		f[q]=p;
		q=r;
	}
	return p;
}

inline void merge_edge(int id) {
	ans[id]=s++;
	if (father[e[id].first]==e[id].second) {
		f[e[id].first]=root(e[id].second);
	}
	else {
		f[e[id].second]=root(e[id].first);
	}
}

int main() {
	//read input and create mapping of edge to index
	cin>>n>>ne;
	for (i=0;i<ne;i++) {
		scanf("%d%d",&e[i].first,&e[i].second);
	}
	
	//construct MST by letting 1 as the root, using explicit stack and backtracking
	memset(father,0,sizeof(father));
	memset(in_mst,0,sizeof(in_mst));
	memset(mst_s,0,sizeof(mst_s));
	for (i=0;i<n-1;i++) {
		scanf("%d",&j);
		j--;
		in_mst[j]=1;
		mst_e[i*2]=mst_e[i*2+1]=e[j];
		swap(mst_e[i*2].first,mst_e[i*2].second);
		mst_s[e[j].first]++;
		mst_s[e[j].second]++;
	}
	sort(mst_e,mst_e+2*n-2);
	for (i=1;i<=n;i++) {
		mst_s[i]+=mst_s[i-1];
	}
	memset(v,0,sizeof(v));
	st[ss=1]=1;
	v[1]=1;
	depth[1]=1;
	while (ss) {
		i=st[ss];
		ss--;
		for (j=mst_s[i-1];j<mst_s[i];j++) {
			if (!v[mst_e[j].second]) {
				st[++ss]=mst_e[j].second;
				v[mst_e[j].second]=1;
				father[mst_e[j].second]=i;
				depth[mst_e[j].second]=depth[i]+1;
			}
		}
	}
	for (i=0;i<ne;i++) {
		if (father[e[i].first]==e[i].second) {
			father_edge_id[e[i].first]=i;
		}
		else if (father[e[i].second]==e[i].first) {
			father_edge_id[e[i].second]=i;
		}
	}

	//sequentially assign weights
	for (i=1;i<=n;i++) {
		f[i]=i;
	}
	s=1;
	memset(ans,0,sizeof(ans));
	for (i=0;i<ne;i++) {
		if (in_mst[i]) {
			//if edge i in mst and not assigned weight, assign next weight and merge with father
			if (!ans[i]) {
				merge_edge(i);
			}
		}
		else {
			//find LCA and push all unlabeled edge into vector a
			rx=root(e[i].first);
			ry=root(e[i].second);
			sa=0;
			while (rx!=ry) {
				if (depth[rx]>depth[ry]) {
					a[sa++]=father_edge_id[rx];
					rx=root(father[rx]);
				}
				else {
					a[sa++]=father_edge_id[ry];
					ry=root(father[ry]);
				}
			}
			//assign next weight to sorted values in a, and then edge i
			sort(a,a+sa);
			for (j=0;j<sa;j++) {
				merge_edge(a[j]);
			}
			ans[i]=s++;
			//merge all nodes along the 2 paths
			ry=root(e[i].first);
			while (ry!=rx) {
				j=f[ry];
				f[ry]=rx;
				ry=j;
			}
			ry=root(e[i].second);
			while (ry!=rx) {
				j=f[ry];
				f[ry]=rx;
				ry=j;
			}
		}
	}
	for (i=0;i<ne-1;i++) {
		printf("%d ",ans[i]);
	}
	printf("%d\n",ans[ne-1]);
    return 0;
}

