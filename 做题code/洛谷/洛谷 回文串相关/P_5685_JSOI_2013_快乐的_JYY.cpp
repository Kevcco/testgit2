// Luogu P5685
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=5e4+10,M=26;

struct PAM
{
    int ch[N][M],fail[N],len[N],cnt[N],last,idx;
    int s[N],now;

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
        }
        last=ch[cur][c];
        cnt[last]++;
    }

    void build()
    {
        for(int i=idx;i>1;i--)
            cnt[fail[i]]+=cnt[i];
        cnt[0]=cnt[1]=0;
    }

}P1,P2;
char s1[N],s2[N];
ll res;

void dfs(int p,int q)
{
    res+=(ll)P1.cnt[p]*P2.cnt[q];
    for(int j=0;j<M;j++)
        if(P1.ch[p][j]&&P2.ch[q][j]) 
            dfs(P1.ch[p][j],P2.ch[q][j]);
}

void solve()
{
    scanf("%s",s1+1);
    scanf("%s",s2+1);
    P1.init();
    int n=strlen(s1+1);
    for(int i=1;i<=n;i++) P1.add(s1[i]-'A');
    P1.build();
    P2.init();
    n=strlen(s2+1);
    for(int i=1;i<=n;i++) P2.add(s2[i]-'A');
    P2.build();
    
    dfs(0,0);
    dfs(1,1);
    printf("%lld\n",res);
}

int main()
{
    solve();
    return 0;
}