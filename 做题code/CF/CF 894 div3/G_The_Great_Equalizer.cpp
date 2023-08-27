#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;
int p[N];
map<int,int> mp,mp2;
ll res;

void solve()
{
    cin >> n;
    set<int> s;
    res=0;
    mp.clear();mp2.clear();
    int maxv=0;
    for(int i=1;i<=n;i++) scanf("%d",p+i),mp[p[i]]++,s.insert(p[i]);
    int last=0;
    for(auto x : s)
    {
        if(last) res+=x-last,maxv=max(maxv,x-last),mp2[x-last]++;
        last=x;
    }
    if(maxv) res+=maxv;

   //  for(auto x : s) printf("%d ",x);
  //   puts("");
        // for(auto x : mp2) printf("%d %d\n",x.first,x.second);
        // puts("");

    cin >> m;
    while(m--)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        if(mp[p[a]]==1)
        {
            auto pos=s.find(p[a]);
            if(pos!=s.begin())
            {
                int t=p[a]-*(--pos);
                ++pos;
                mp2[t]--;
            //    if(a==3) printf("aaaa %d ",t);
                if(!mp2[t]) mp2.erase(t);
                res-=t;
            }
            if(pos!=(--s.end()))
            {
                int t=*(++pos)-p[a];
                --pos;
                mp2[t]--;
                if(!mp2[t]) mp2.erase(t);
                res-=t;
              //  if(a==3) printf("bbbb %d ",t);
            }
            if(pos!=s.begin()&&pos!=(--s.end()))
            {
                int t1=*(--pos);++pos;
                int t2=*(++pos);--pos;
                mp2[t2-t1]++;
                res+=t2-t1;
               // if(a==3) printf("cccc %d ",t2-t1);
            }
            s.erase(pos);
        } 
        mp[p[a]]--;

        p[a]=b;

        if(!mp[p[a]])
        {
            s.insert(p[a]);
            auto pos=s.find(p[a]);
            if(pos!=s.begin())
            {
                int t=p[a]-*(--pos);

                ++pos;
                mp2[t]++;
                res+=t;
            }
            if(pos!=(--s.end()))
            {
                int t=*(++pos)-p[a];
                --pos;
                mp2[t]++;
                res+=t;

            }
            if(pos!=s.begin()&&pos!=(--s.end()))
            {
                int t1=*(--pos);++pos;
                int t2=*(++pos);
             //   printf("asdd %d\n",t2-t1);
                mp2[t2-t1]--;
                if(!mp2[t2-t1]) mp2.erase(t2-t1);
                res-=t2-t1;
            }
        } 
        mp[p[a]]++;

        if(!mp2.empty())
        {
            int t=(*mp2.rbegin()).first;
            if(t!=maxv)
            {
                res-=maxv;
                res+=t;
                maxv=t;
            }
        }
        else res=0,maxv=0;
        // for(auto x : s) printf("%d ",x);
      //   puts("");
        // if(m<=2) {puts("");for(auto x : mp2) printf("%d %d\n",x.first,x.second);}
        printf("%lld ",res+*s.begin());
       // puts("");
    }
    puts("");
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}