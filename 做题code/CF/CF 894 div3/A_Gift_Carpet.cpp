#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
int p[N];
string s[N];
string st="vika?";

void solve()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++) cin >> s[i];
    int last=0;
    for(int j=0;j<m;j++)
    {
        for(int i=1;i<=n;i++)
        {
            if(s[i][j]==st[last])
            {   last++;
                break;
            }
        }
    }
    if(last>3) puts("YES");
    else puts("NO");
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}