//Refer to NOI released solution for subtask 6 for algorithm description
//Basically DP f(n',k') to find out largest result of k' consecutive sequences till element n', then f(n,k) is the answer
//And to get O(NK) solution instead of O(N^2K) to pass task 6, need to construct 2 DP function to make transition complexity from O(N) to O(1)
//f(n',k') represents largest result of k' consecutive sequences till element n', where the k'th sequence ends already
//g(n',k') represents largest result of k' consecutive sequences till element n', where the k'th sequence includes n'th element
//This eliminates the need to check all previous 0~n'-1 position for optimal starting point of k'th sequence, while just check g(n'-1,k') and f(n'-1,k'-1)
#include <bits/stdc++.h>
using namespace std;

#include<fstream>
int n,i,j,k,p,a[300010];
long long ans,x,y,f[300010],g[300010];

int main() {
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	cin>>n>>k;
	ans=0;
	j=0;
	for (i=0;i<n;i++) {
		scanf("%d",a+i);
		ans+=a[i];
		if (a[i]<0) {
			j++;
			p=i;
		}
	}
	if (j==0) {
		printf("%lld\n",ans);
		return 0;
	}
	else if (j==1) {
		if (k>1) {
			printf("%lld\n",ans-a[p]);
		}
		else {
			x=y=0;
			for (i=0;i<p;i++) {
				x+=a[i];
			}
			for (i=p+1;i<n;i++) {
				y+=a[i];
			}
			printf("%lld\n",max(ans,max(x,y)));
		}
		return 0;
	}
	for (i=0;i<n;i++) {
		for (j=k;j;j--) {
			g[j]=max(g[j]+a[i],f[j-1]+a[i]);
			f[j]=max(f[j],g[j]);
		}
	}
	ans=0;
	for (i=k;i;i--) {
		ans=max(ans,f[i]);
	}
	printf("%lld\n",ans);
    return 0;
}
