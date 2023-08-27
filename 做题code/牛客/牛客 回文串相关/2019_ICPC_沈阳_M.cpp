#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e6+10,M=26;

int ch[N][M],fail[N],len[N],last,idx;
int diff[N],slink[N],g1[N],g2[N];
int s[N],now;
char t[N];
int dp1[N],dp2[N];
int res;

void init()
{
    res=0;
    len[0]=0,len[1]=-1,fail[0]=1,fail[1]=0;
    s[0]=-1,last=0,idx=1,now=0;
}

int get_fail(int u,int i)
{
    while(s[i]!=s[i-len[u]-1]) u=fail[u];
    return u;
}

void add(int c)
{
    s[++now]=c;
    int cur=get_fail(last,now);
    if(!ch[cur][c])
    {
        int q=++idx;
        fail[q]=ch[get_fail(fail[cur],now)][c];
        len[q]=len[cur]+2; 
        ch[cur][c]=q;

        diff[q]=len[q]-len[fail[q]];
        if(diff[q]==diff[fail[q]]) slink[q]=slink[fail[q]];
        else slink[q]=fail[q];
    }

    last=ch[cur][c];
}

void solve()
{
    init();
    scanf("%s",t+1);
    int n=strlen(t+1);
    for(int i=1;i<=n;i++) dp1[i]=dp2[i]=0;

    for(int i=1;i<=n;i++)
    {
        add(t[i]-'a');

        dp1[i]=max(len[last],dp1[i-1]);
        dp2[i]=dp2[i-1];

        int dp3=0;
        for(int j=last;j>1;j=slink[j])
        {
            g1[j]=dp1[i-len[slink[j]]-diff[j]]+len[slink[j]]+diff[j];
            g2[j]=dp2[i-len[slink[j]]-diff[j]]+len[slink[j]]+diff[j];
            if(diff[j]==diff[fail[j]])
                g1[j]=max(g1[j],g1[fail[j]]+diff[j]),
                g2[j]=max(g2[j],g2[fail[j]]+diff[j]);

            dp2[i]=max(dp2[i],g1[j]);
            dp3=max(dp3,g2[j]);
        }
        res=max(res,dp3);
        res=max(res,dp1[i]);
        res=max(res,dp2[i]);
    }

    printf("%d\n",res);

    for(int i=0;i<=idx;i++)
    {
        fail[i]=len[i]=0;
        diff[i]=slink[i]=0;
        for(int j=0;j<M;j++) ch[i][j]=0;
        g1[i]=g2[i]=0;
    }
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}