#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k,h;

void solve()
{
    cin >> n >> m >> k >> h;
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        int t=abs(h-x);
        if(t>0&&(t%k==0)&&t/k<m) cnt++;
    }
    printf("%d\n",cnt);
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}