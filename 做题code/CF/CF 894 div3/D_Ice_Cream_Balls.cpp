#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

ll n;
int p[N];

void solve()
{
    scanf("%lld",&n);
    ll l=2,r=1e18;
    while(l<r)
    {
        ll mid=l+r+1>>1;
        __int128 t=(__int128)mid*(mid-1)/2;
        if(t>n) r=mid-1;
        else l=mid;
    }
    ll t=l*(l-1)/2;
    l+=n-t;
    printf("%lld\n",l);
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}