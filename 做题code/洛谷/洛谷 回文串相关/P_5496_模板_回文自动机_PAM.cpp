// Luogu 5496
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=1e6+10,M=26;

int ch[N][M],fail[N],len[N],cnt[N],last,idx;
int s[N],now,times;
char str[N];

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
        cnt[q]=cnt[fail[q]]+1;
    }
    last=ch[cur][c];
    printf("%d ",cnt[last]);
    times=cnt[last];
}

void solve()
{
    init();
    scanf("%s",str+1);
    int n=strlen(str+1);
    for(int i=1;i<=n;i++)
    {
        char c=str[i];
        if(i>1) c=(c-97+times)%26+97;
        add(c-'a');
    }
}

int main()
{
    solve();
    return 0;
}