#include <bits/stdc++.h>
using namespace std;

stack <pair<int,int> > s;
pair<int,int> p,pp;
long long f[1000100],value;
int h=1000000+1,n,q,i,x;

void update(int x,int i) {
	while (s.top().first<x) {
		p=s.top();
		s.pop();
		value=((long long)i-p.second)*(p.second-s.top().second);
		f[p.first]+=value;
	}
	s.push(make_pair(x,i));
}

int main() {
	cin>>n>>q;
	memset(f,0,sizeof(f));
	s.push(make_pair(h,-1));
	for (i=0;i<n;i++) {
		scanf("%d",&x);
		update(x,i);
	}
	update(h,n);
	for (i=1;i<h;i++) {
		f[i]+=f[i-1];
	}
	for (;q;q--) {
		scanf("%d",&x);
		printf("%lld\n",f[x]);
	}
    return 0;
}
