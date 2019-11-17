//sort by increasing height
//record left and right of each position as itself (similar initialization as union find)
//for k=1 to 10^6 do
//  merge all position with height equal to k with its left and right, if they are merged already (marked by array v)
//  increase ans[k] by number of new segment generated during this merging,
//  and do a prefix sum after all iterations because these segments are valid for larger k as well
//here we can use union find, or simply maintain the left and right array because merged cluster are always consecutive
#include <bits/stdc++.h>
using namespace std;

#define MAX 1000001

pair<int,int>a[MAX];
long long ans[MAX];
int l[MAX],r[MAX];
bool v[MAX];

int main() {
   	int n,i,j,k,q;
   	memset(ans,0,sizeof(ans));
   	cin>>n>>q;
   	for (i=0;i<n;i++) {
   		scanf("%d",&a[i].first);
   		a[i].second=i;
   	}
   	sort(a,a+n);
   	for (i=0;i<n;i++) {
   		l[i]=r[i]=i;
	}
	memset(v,0,sizeof(v));
	for (i=0,k=1;i<n;k++) {
		ans[k]=0;
		for (;i<n && a[i].first==k;i++) {
			ans[k]++;
			j=a[i].second;
			v[j]=1;
			//merging is simpler than union find because merged are consecutive segment
			//merge left
			if (j && v[j-1]) {
				l[r[j]]=l[j-1];
				r[l[j-1]]=r[j];
				ans[k]+=(long long)(j-l[j-1])*(r[j]-j+1);
			}
			//merge right
			if (j<n-1 && v[j+1]) {
				l[r[j+1]]=l[j];
				r[l[j]]=r[j+1];
				ans[k]+=(long long)(r[j+1]-j)*(j-l[j]+1);
			}
		}
	}
	for (i=2;i<MAX;i++) {
		ans[i]+=ans[i-1];
	}
	for (;q;q--) {
		scanf("%d",&i);
		printf("%lld\n",ans[i]);
	}
}
