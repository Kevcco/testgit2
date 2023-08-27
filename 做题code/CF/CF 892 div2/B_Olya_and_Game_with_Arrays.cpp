#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e5+10;

int n,m,k;
vector<int> p[N];

void solve()
{
    cin >> n;
    for(int i=1;i<=n;i++) p[i].clear();
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&m);
        for(int j=1;j<=m;j++)
        {
            int x;
            scanf("%d",&x);
            p[i].push_back(x);
        }
        sort(p[i].begin(),p[i].end());
    }
    ll ans=0;
    int minv=2e9;
    for(int i=1;i<=n;i++)
    {
        ans+=p[i][1];
        minv=min(minv,p[i][0]);
    }
    ll res=0;
    for(int i=1;i<=n;i++)
    {
        ll t=ans-p[i][1];
        t+=minv;
        res=max(res,t);
    }
    printf("%lld\n",res);

}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}