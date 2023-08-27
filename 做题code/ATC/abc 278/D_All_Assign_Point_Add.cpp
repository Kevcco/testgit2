/*
给定长为2e5的序列,进行2e5次操作,操作分三种:
(1)整个序列覆盖成新值 (2)单点加 (3)单点查询


维护单点加的操作,遇到赋值将单点加操作清空即可
时间复杂度 O(n + q)
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
map<int,ll> mp;

void solve()
{
    cin >> n;
    for(int i=1;i<=n;i++)
    {
        ll x;
        scanf("%lld",&x);
        mp[i]=x;
    }

    ll tag=0;
    cin >> m;
    while(m--)
    {
        int ty,x,y;
        scanf("%d%d",&ty,&x);
        if(ty==1) mp.clear(),tag=x;
        else if(ty==2)
        {
            scanf("%d",&y);
            mp[x]+=y;
        }
        else printf("%lld\n",tag+mp[x]);
    }
}

int main()
{
    solve();
    return 0;
}