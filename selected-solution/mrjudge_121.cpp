#include <bits/stdc++.h>
using namespace std;
int main() {
    int n,m,w,v,i,f[510];
    memset(f,0,sizeof(f));
    cin>>n>>m;
    for (;n;n--) {
        scanf("%d%d",&w,&v);
        for (i=m;i>=w;i--)
        f[i]=max(f[i],f[i-w]+v);
    }
    v=0;
    for (i=1;i<=m;i++)
    v=max(v,f[i]);
    cout<<v;
}
