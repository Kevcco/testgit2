#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
int p[N];
int res[N];

void solve()
{
    cin >> n;

    ll res=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<i;j++) p[j]=j;
        for(int j=i;j<=n;j++) p[j]=n-(j-i);
        ll ans=0;
        int ma=0;
        for(int j=1;j<=n;j++)
        {
            ans+=j*p[j];
            ma=max(ma,j*p[j]);
        }
        ans-=ma;
        res=max(res,ans);
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