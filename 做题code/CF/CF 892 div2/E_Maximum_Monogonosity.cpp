#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=3010;
const ll INF=1e18;

int n,m,k;
int a[N],b[N];
ll dp[N][N];
ll maxv[N][4];

void solve()
{
    cin >> n >> k;
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=n;i++) scanf("%d",b+i);
    for(int i=0;i<=n;i++)
        for(int j=0;j<=k;j++)
            dp[i][j]=-INF;
    for(int i=0;i<=n;i++)
        for(int j=0;j<4;j++)
            maxv[i][j]=-INF;
    dp[0][0]=0;
    maxv[0][0]=a[1]+b[1];
    maxv[0][1]=a[1]-b[1];
    maxv[0][2]=b[1]-a[1];
    maxv[0][3]=-a[1]-b[1];
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=min(i,k);j++)
        {
            dp[i][j]=dp[i-1][j];
            dp[i][j]=max(dp[i][j],maxv[i-j][0]-a[i]-b[i]);
            dp[i][j]=max(dp[i][j],maxv[i-j][1]+a[i]-b[i]);
            dp[i][j]=max(dp[i][j],maxv[i-j][2]-a[i]+b[i]);
            dp[i][j]=max(dp[i][j],maxv[i-j][3]+a[i]+b[i]);

            maxv[i-j][0]=max(maxv[i-j][0],dp[i][j]+a[i+1]+b[i+1]);
            maxv[i-j][1]=max(maxv[i-j][1],dp[i][j]+a[i+1]-b[i+1]);
            maxv[i-j][2]=max(maxv[i-j][2],dp[i][j]-a[i+1]+b[i+1]);
            maxv[i-j][3]=max(maxv[i-j][3],dp[i][j]-a[i+1]-b[i+1]);
        }
    }

    printf("%lld\n",dp[n][k]);
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}