// https://ac.nowcoder.com/acm/contest/33548/A

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e6+10;

int n,m,k;
int len[N*2];
char s[N],t[N*2];
ll res[N];
vector<array<int,3>> q1,q2;
struct node
{
    ll sum,tag;
}tr[N*4];

void manacher()
{
    t[k]='$';
    for(int i=1;i<=n;i++) t[++k]='#',t[++k]=s[i];
    t[++k]='#';
    t[k+1]='~';
    int M=0,R=0;
    for(int i=1;i<=k;i++)
    {
        if(i>R) len[i]=1;
        else len[i]=min(R-i+1,len[2*M-i]);
        while(t[i+len[i]]==t[i-len[i]]) len[i]++;
        if(i+len[i]-1>R) M=i,R=i+len[i]-1;
    }
}

void pushup(node &u,node &l,node &r)
{
    u.sum=l.sum+r.sum;
}

void pushup(int u)
{
    pushup(tr[u],tr[u<<1],tr[u<<1|1]);
}

void pushdown(int u,int L,int R)
{
    if(tr[u].tag)
    {
        int mid=L+R>>1;
        tr[u<<1].tag+=tr[u].tag,tr[u<<1].sum+=tr[u].tag*(mid-L+1);
        tr[u<<1|1].tag+=tr[u].tag,tr[u<<1|1].sum+=tr[u].tag*(R-mid);
        tr[u].tag=0;
    }
}

//区间修改
void modify(int u,int L,int R,int l,int r,int d)
{
    if(L>=l&&R<=r)
    {
        tr[u].tag+=d;
        tr[u].sum+=(ll)d*(R-L+1);
        return;
    }
    pushdown(u,L,R);
    int mid=L+R>>1;
    if(l<=mid) modify(u<<1,L,mid,l,r,d);
    if(r>mid) modify(u<<1|1,mid+1,R,l,r,d);
    pushup(u);
}

node query(int u,int L,int R,int l,int r)
{
    if(L>=l&&R<=r) return tr[u];
    pushdown(u,L,R);
    int mid=L+R>>1;
    if(l>mid) return query(u<<1|1,mid+1,R,l,r);
    else if(r<=mid) return query(u<<1,L,mid,l,r);
    node res,ls=query(u<<1,L,mid,l,r),rs=query(u<<1|1,mid+1,R,l,r);
    pushup(res,ls,rs);
    return res;
}

void solve()
{
    cin >> n >> m;
    scanf("%s",s+1);
    manacher();
    n=k;
    for(int i=1;i<=m;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        res[i]-=r-l+2;
        l<<=1,l--;
        r<<=1,r++;
        q1.push_back({l+r>>1,l,i});
        q2.push_back({(l+r>>1)+1,r,i});
    }

    sort(q1.begin(),q1.end());
    sort(q2.begin(),q2.end());
    reverse(q2.begin(),q2.end());

    int last=0;
    for(auto x : q1)
    {
        while(last<x[0])
        {
            last++;
            modify(1,1,n,last-len[last]+1,last,1);
        }
        res[x[2]]+=query(1,1,n,x[1],x[0]).sum;
    }

    for(int i=0;i<4*N;i++) tr[i].sum=tr[i].tag=0;
    last=n+1;
    for(auto x : q2)
    {
        while(last>x[0])
        {
            last--;
            modify(1,1,n,last,last+len[last]-1,1);
        }
        res[x[2]]+=query(1,1,n,x[0],x[1]).sum;
    }
    for(int i=1;i<=m;i++) printf("%lld\n",res[i]/2);
}

int main()
{
    solve();
    return 0;
}