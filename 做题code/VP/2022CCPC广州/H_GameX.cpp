#include<bits/stdc++.h>
using namespace std;
int n,k,t;
const int maxn = 1e6 + 6;
int a[maxn],c[maxn],b[maxn];
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        int x = 0,y = 0;
        scanf("%d%d",&n,&k);
        for(int i = 1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            c[a[i]] = 1;
        }
        //sort(a+1,a+n+1);
       // for(int i = 1;i<=n;i++)cout<<a[i]<<" ";
        //cout<<endl;
        int cn = 0;
        while(x<=k&&y<=k)
        {
            while(c[cn])cn++;
            if(cn%2==1)x++;
            else y++;
            cn++;
        }
        if(y==k+1)printf("Alice\n");
        else printf("Bob\n");

        for(int i = 1;i<=n;i++)
            c[a[i]] = 0;
        
    }
    return 0;
}