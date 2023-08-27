#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=3e5+10,M=26;

int ch[N][M],fail[N],len[N],cnt[N],last,idx;
int s[N],now;
char str[N];
bool st[M];
ll res;

void dfs(int u,int nums)
{
    res+=(ll)cnt[u]*nums;
    for(int i=0;i<M;i++)
    {
        if(!ch[u][i]) continue;
        if(st[i]) dfs(ch[u][i],nums);
        else
        {
            st[i]=1;
            dfs(ch[u][i],nums+1);
            st[i]=0;
        }
    }
}

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
        len[q]=len[cur]+2; 
        fail[q]=ch[get_fail(fail[cur],now)][c];
        // 一定要最后赋值
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

void solve()
{
    init();
    scanf("%s",str+1);
    int n=strlen(str+1);
    for(int i=1;i<=n;i++) add(str[i]-'a');
    build();
    dfs(0,0);
    dfs(1,0);
    printf("%lld\n",res);
}

int main()
{
    solve();
    return 0;
}