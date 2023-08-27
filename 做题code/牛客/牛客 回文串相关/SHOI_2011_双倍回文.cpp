#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e6+10;

int n,m,k,len[N];
char p[N],t[N];

void manacher()
{
    t[0]='@';
    t[++m]='$';
    for(int i=1;i<=n;i++) t[++m]=p[i],t[++m]='$';
    t[m+1]='~';

    int res=0;
    int M=0,R=0;
    for(int i=1;i<=m;i++)
    {
        if(i>R) len[i]=1;
        else len[i]=min(len[2*M-i],R-i+1);
        while(t[i-len[i]]==t[i+len[i]]) len[i]++;
        if(i+len[i]-1>R)
        {
            if(i&1)
            {
                for(int j=max(i+1,R+1);j<=i+len[i]-1;j++)
                {
                    if((j-i)%4) continue;
                    int mid=j+i+1>>1;
                    mid=2*i-mid;
                    if(mid+len[mid]-1>=i) res=max(res,j-i);
                }
            }
            M=i,R=i+len[i]-1;
        }
    }
    printf("%d\n",res);
}

void solve()
{
    cin >> n;
    scanf("%s",p+1);
    manacher(); 
}

int main()
{
    solve();
    return 0;
}