#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

ll n,m,k;
ll p[N];

void solve()
{
    cin >> n >> m >> k;
    for(int i=1;i<=n;i++) scanf("%lld",p+i);
    multiset<int> s;
    ll res=0,sum=0,cnt=0;
    for(int i=1;i<=n;i++)
    {
        ll t=sum+p[i]-i*k;
        res=max(res,t);
        if(p[i]>0)
        {
            if(cnt<m-1) s.insert(p[i]),cnt++,sum+=p[i];
            else if(m>1&&p[i]>*s.begin())
            {
                sum+=p[i]-(*s.begin());
                s.erase(s.begin());
                s.insert(p[i]);
            }
        }
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