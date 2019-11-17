//This is subopitimal solution of O(nlogn) complexity that can solve until subtask 9
//It is a common trick to solve this kind of counting/maximizing problem in linear space using sorting+sequential updating, leading to O(nlogn) solution
//we consider height y from 10000000 to 1, and sequentially remove mountain of height more than currently considered y
//in this way, all subsequences that can be formed using remaining mountains.
//When a mountain i is removed, it will break its current consecutive segment (l,r) into (l,i-1) and (i+1,r)
//This will cause the number of possible segments to be reduced by (r-l+2)*(r-l+1)/2---all possible segments in (l,r)
//And add back remaining possible segments in (l,i-1) and (i+1,r) by similar formula. 
//Initially, number of possible segment is n*(n+1)/2 when y=10000000
//Using segment tree to query and maintain index of left/right most consecutive remaining mountain of removed mountain i, we get O(nlogn) solution as belo
//Optimal solution is in code mrjudge1824_pilot.cpp where typical optimal solution is linear O(n) using monotonic stack/queue
#include <bits/stdc++.h>
using namespace std;

int a[1000010],q[1000010];
long long ans[1000010],t,d;
struct node{
	int left,right,p,left_link,right_link;
	bool operator<(const node &b) const {return a[p]<a[b.p];}
};
node nx,ny,tree[2000010];
priority_queue<node> pq;

void build(int id, int left, int right) {
	tree[id].left=left;
	tree[id].right=right;
	tree[id].left_link=tree[id].right_link=-1;
	if (left==right) {
		tree[id].p=left;
	}
	else {
		d++;
		tree[id].left_link=d;
		build(d,left,(left+right)/2);
		d++;
		tree[id].right_link=d;
		build(d,(left+right)/2+1,right);
		if (a[tree[tree[id].left_link].p]>a[tree[tree[id].right_link].p]) {
			tree[id].p=tree[tree[id].left_link].p;
		}
		else {
			tree[id].p=tree[tree[id].right_link].p;
		}
	}
}

int find_max(int id, int left, int right) {
	if (left<=tree[id].left && right>=tree[id].right) {
		return tree[id].p;
	}
	if (left>tree[id].right || right<tree[id].left) {
		return -1;
	}
	int x=find_max(tree[id].left_link,left,right),y=find_max(tree[id].right_link,left,right);
	if (x==-1) {
		return y;
	}
	else if (y==-1) {
		return x;
	}
	else if (a[x]>a[y]) {
		return x;
	}
	else {
		return y;
	}
}

int main() {
	int n,m,i,j,k;
	cin>>n>>m;
	memset(ans,0,sizeof(ans));
	for (i=0;i<n;i++) {
		scanf("%d",a+i);
	}
	for (i=0;i<m;i++) {
		scanf("%d",q+i);
		ans[q[i]]=1;
	}
	t=(long long)n*(n+1)/2;
	build(d=0,0,n-1);
	pq.push(tree[0]);
	for (k=1000000;k;k--) {
		if (ans[k]) {
			while (!pq.empty() && a[pq.top().p]>k) {
				nx=pq.top();
				pq.pop();
				t-=(long long)(nx.right-nx.left+1)*(nx.right-nx.left+2)/2;
				if (nx.left<nx.p) {
					ny.left=nx.left;
					ny.right=nx.p-1;
					ny.p=find_max(0,ny.left,ny.right);
					t+=(long long)(ny.right-ny.left+1)*(ny.right-ny.left+2)/2;
					pq.push(ny);
				}
				if (nx.right>nx.p) {
					ny.left=nx.p+1;
					ny.right=nx.right;
					ny.p=find_max(0,ny.left,ny.right);
					t+=(long long)(ny.right-ny.left+1)*(ny.right-ny.left+2)/2;
					pq.push(ny);
				}
			}
			ans[k]=t;
		}
	}
	for (i=0;i<m;i++) {
		printf("%lld\n",ans[q[i]]);
	}
    return 0;
}

