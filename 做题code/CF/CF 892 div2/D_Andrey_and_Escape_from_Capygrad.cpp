#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=3e5+10;

int n,m,k;
array<int,2> p[N];
array<int,2> q[N];
int res[N];

void solve()
{
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        int l1,r1,l2,r2;
        scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
        p[i]={l1,r2};
    }
    cin >> m;
    for(int i=1;i<=m;i++)
    {
        int x;
        scanf("%d",&x);
        q[i]={x,i};
    }
    sort(p+1,p+n+1);sort(q+1,q+m+1);
    
    int l=p[1][0],r=p[1][1],now=1;
    while(now<=m&&q[now][0]<l) res[q[now][1]]=q[now][0],++now;
    for(int i=2;i<=n;i++)
    {
        if(p[i][0]<=r) r=max(r,p[i][1]);
        else
        {
            while(now<=m&&q[now][0]<=r) res[q[now][1]]=r,++now;
            l=p[i][0],r=p[i][1];
            while(now<=m&&q[now][0]<l) res[q[now][1]]=q[now][0],++now;
        }
    }
    while(now<=m&&q[now][0]<=r) res[q[now][1]]=r,++now;
    while(now<=m) res[q[now][1]]=q[now][0],++now;
    for(int i=1;i<=m;i++) printf("%d%c",res[i]," \n"[i==m]);
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}