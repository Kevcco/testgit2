#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e6+10,M=26;

int ch[N][M],fail[N],len[N],cnt[N],last,idx;
int diff[N],slink[N],g[N];
int s[N],now;
char str[N],t[N];
int dp[N];

void init()
{
    len[0]=0,len[1]=-1,fail[0]=1,fail[1]=0;
    s[0]=-1,last=0,idx=1;
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
    scanf("%s",str+1);
    int n=strlen(str+1);
    for(int i=1,j=n;i<j;i++,j--) t[i*2-1]=str[i],t[i*2]=str[j];
    dp[0]=1;
    for(int i=1;i<=n;i++)
    {
        add(t[i]-'a');
        for(int j=last;j>1;j=slink[j])
        {
            g[j]=dp[i-len[slink[j]]-diff[j]];
            if(slink[j]!=fail[j]) g[j]=((ll)g[j]+g[fail[j]])%mod;
            if((i&1)==0) dp[i]=((ll)dp[i]+g[j])%mod;
        }
    }
    printf("%d\n",dp[n]);
}

int main()
{
    solve();
    return 0;
}