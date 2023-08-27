/*
题意
给定 n * m的数字矩阵 (n, m <= 300),询问对于所有的 h * w的子矩阵
去掉这个子矩阵,剩下的图形中,不同数个数是多少


暴力是 O(n^4),考虑优化,
我们利用已求得的子矩阵通过变化两列来转移得到相邻的子矩阵的答案即可
O(n^3)
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=310;

int n,m,q,h,w;
int cnt[N],ans;
int res[N][N];
int g[N][N];

void add(int x)
{
    if(!cnt[x]) ans++;
    cnt[x]++;
}

void del(int x)
{
    cnt[x]--;
    if(!cnt[x]) ans--;
}

void solve()
{
    cin >> n >> m >> q >> h >> w;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&g[i][j]);
    
    for(int i=1;i+h-1<=n;i++)
    {
        for(int j=1;j<=q;j++) cnt[j]=0;
        ans=0;
        for(int j=1;j<=n;j++)
            for(int k=1;k<=m;k++) {
                if(j>=i&&j<=i+h-1&&k<=w) continue;
                add(g[j][k]);
            }
        res[i-1][0]=ans;
        for(int j=w+1;j<=m;j++)
        {
            for(int k=i;k<=i+h-1;k++) add(g[k][j-w]);
            for(int k=i;k<=i+h-1;k++) del(g[k][j]);
            res[i-1][j-w]=ans;
        }
    }

    for(int i=0;i<n-h+1;i++)
        for(int j=0;j<m-w+1;j++)
            printf("%d%c",res[i][j]," \n"[j==m-w]);
}

int main()
{
    solve();
    return 0;
}