#include <bits/stdc++.h>
using namespace std;

typedef pair <int,int> p;
pair<p,int> e[2000100];
int n,m,i,j,k,d[100010],st[100001];
bool v[100010];
set <p> s;
set <p>::iterator it;

int main() {
    cin>>n>>m;
    memset(st,0,sizeof(st));
    for (i=0;i<m;i++) {
        scanf("%d%d%d",&e[i*2].first.first,&e[i*2].first.second,&e[i*2].second);
        e[i*2+1]=e[i*2];
        swap(e[i*2+1].first.first,e[i*2+1].first.second);
        st[e[i*2].first.first]++;
        st[e[i*2].first.second]++;
    }
    sort(e,e+2*m);
    for (i=1;i<=n;i++) {
        st[i]+=st[i-1];
    }
    memset(v,0,sizeof(v));
    memset(d,-1,sizeof(d));
    d[1]=0;
    s.insert(make_pair(0,1));
    while (!s.empty() && !v[n]) {
        i=s.begin()->second;
        s.erase(s.begin());
        v[i]=1;
        for (j=st[i-1];j<st[i];j++) {
            k=e[j].first.second;
            if (!v[k] && (d[k]==-1 || d[i]+e[j].second<d[k])) {
                it=s.find(make_pair(d[k],k));
                if (it!=s.end()) {
                    s.erase(it);
                }
                d[k]=d[i]+e[j].second;
                s.insert(make_pair(d[k],k));
            }
        }
    }
    printf("%d\n",v[n]?d[n]:-1);
}