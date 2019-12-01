#include <bits/stdc++.h>
using namespace std;

int f[1000010],p[1000010],c[1000010];
stack <int> s;
long long t=0;

int main() {
	int n,i,j;
	memset(c,0,sizeof(c));
	cin>>n;
	for (i=0;i<n;i++) {
		scanf("%d%d",p+i,f+i);
		if (p[i]>-1) {
			c[p[i]]++;
		}
	}
	for (i=0;i<n;i++) {
		if (!c[i]) {
			s.push(i);
		}
	}
	while (!s.empty()) {
		i=s.top();
		s.pop();
		f[i]--;
		t+=abs(f[i]);
		if (p[i]>-1) {
			c[p[i]]--;
			if (!c[p[i]]) {
				s.push(p[i]);
			}
			f[p[i]]+=f[i];
		}
	}
	cout<<t<<endl;
}
