//greedy as per released solution
//double linked list is used to speed up neighbour selection/deletion
#include <bits/stdc++.h>
using namespace std;

struct block{
	int id,l,r;
	long long s;
};
block b[300010];
priority_queue<pair<long long,int> >pq;
long long x[300010],ans;
bool v[300010];

int main() {
	int n,i,j,k,remaining,m=0,a[300010];
	long long t;
	cin>>n>>k;
	for (i=0;i<n;i++) {
		scanf("%d",a+i);
	}
	for (i=0;i<n;i=j) {
		b[m].s=0;
		b[m].l=m-1;
		b[m].r=m+1;
		for (j=i;j<n && ((a[i]>=0 && a[j]>=0) || (a[i]<0 && a[j]<=0));j++) {
			b[m].s+=a[j];
		}
		if (b[m].s<0 && m==0) {
		}
		else {
			m++;
		}
	}
	if (m && b[m-1].s<0) {
		m--;
	}
	if (!m) {
		printf("0\n");
		return 0;
	}
	b[0].l=b[m-1].r=-1;
	remaining=m/2+1;
	for (i=0;i<m;i++) {
		pq.push(make_pair(-abs(b[i].s),i));
	}
	memset(v,0,sizeof(v));
	while (remaining>k) {
		i=pq.top().second;
		pq.pop();
		if (v[i]) {
			continue;
		}
		v[i]=1;
		//in all possibilities, number of positive sum block is reduced by 1. (why?)
		remaining--;
		//merge it with left and right
		//if i is at border, both itself and its neighbour will be removed. (why?)
		if (b[i].l==-1) {
			v[b[i].r]=1;
			b[b[b[i].r].r].l=-1;
		}
		else if (b[i].r==-1) {
			v[b[i].l]=1;
			b[b[b[i].l].l].r=-1;
		}
		else {
			v[b[i].r]=1;
			v[b[i].l]=1;
			//merge with left and right block
			b[i].s+=b[b[i].l].s+b[b[i].r].s;
			if (b[b[i].l].l>-1) {
				b[b[b[i].l].l].r=i;
			}
			b[i].l=b[b[i].l].l;
			if (b[b[i].r].r>-1) {
				b[b[b[i].r].r].l=i;
			}
			b[i].r=b[b[i].r].r;
			//push it back to queue
			v[i]=0;
			pq.push(make_pair(-abs(b[i].s),i));
		}
	}
	ans=0;
	for (i=0;i<m;i++) {
		if (!v[i] && b[i].s>0) {
			ans+=b[i].s;
		}
	}
	printf("%lld\n",ans);
    return 0;
}
