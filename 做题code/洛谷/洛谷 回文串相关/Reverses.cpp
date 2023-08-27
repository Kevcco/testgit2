// CF 906E
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e6+10,M=26;

int ch[N][M],fail[N],len[N],cnt[N],last,idx;
int diff[N],slink[N],g[N];
int s[N],now;
char str1[N],str2[N],t[N];
int dp[N],pre[N];

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
    scanf("%s",str1+1);
    scanf("%s",str2+1);
    int n=strlen(str1+1);
    for(int i=1;i<=n;i++) t[i*2-1]=str1[i],t[i*2]=str2[i];
    memset(dp,0x3f,sizeof dp);
    dp[0]=0;
    for(int i=1;i<=2*n;i++)
    {
        add(t[i]-'a');

        if(((i&1)==0)&&(s[i]==s[i-1])&&(dp[i]>dp[i-2])) dp[i]=dp[i-2],pre[i]=i-2;

        for(int j=last;j>1;j=slink[j])
        {
            g[j]=i-len[slink[j]]-diff[j];
            if(diff[j]==diff[fail[j]])
            {
                if(dp[g[j]]>dp[g[fail[j]]]) g[j]=g[fail[j]];
            }

            if((i&1)==0) 
            {
                if(dp[i]>dp[g[j]]+1)
                {
                    dp[i]=dp[g[j]]+1;
                    pre[i]=g[j];
                }
            }
        }
    }
    if(dp[2*n]>0x3f3f3f3f/2)
    {
        printf("-1\n");
        return;
    }
    printf("%d\n",dp[2*n]);
    int r=2*n;
    while(r)
    {
        if(r-pre[r]>2) printf("%d %d\n",pre[r]/2+1,r/2);
        r=pre[r];
    }
}

int main()
{
    solve();
    return 0;
}