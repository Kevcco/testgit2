#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
int p[N];

void solve()
{
    cin >> n >> k;
    for(int i=1;i<=n;i++) scanf("%d",p+i);
    if(p[1]==p[n])
    {
        int cnt=0;
        for(int i=1;i<=n;i++)
            if(p[i]==p[1]) cnt++;
        if(cnt>=k) puts("YES");
        else puts("NO");
    }
    else
    {
        int pos1=0,pos2=n;
        int cnt1=0,cnt2=0;
        while(pos1<=n)
        {
            if(p[pos1]==p[1]) cnt1++;
            if(cnt1>=k) break;
            pos1++;
        }
        while(pos2>0)
        {
            if(p[pos2]==p[n]) cnt2++;
            if(cnt2>=k) break;
            pos2--;
        }
        if(pos1<pos2) puts("YES");
        else puts("NO");
    }
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}