#include<iostream>
#include<cstdio>
#include<cstring>
const int N=102;
int n,m,hx[N],amt[N];
bool dp[2][(int)1e5+2];

inline int nxi(){
    int x=0;
    char c;
    while((c=getchar())>'9'||c<'0');
    while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
    return x;
}

int main(){
#ifndef ONLINE_JUDGE
//    freopen("a.in","r",stdin);
#endif
    while(~scanf("%d%d",&n,&m)&&(n||m)){;
        memset(dp,0,sizeof(dp));
        int ans=0;
        for(int i=1;i<=n;++i){
            hx[i]=nxi();
        }
        for(int i=1;i<=n;++i){
            amt[i]=nxi();
        }
        dp[0][0]=1;
        for(int i=1;i<=n;++i){
            int p=hx[i],f=i&1;
            memcpy(dp[f],dp[f^1],sizeof(dp[f]));
            if(p>m) continue;
            for(int j=0;j<p;++j){
                int cur=0,l=0;
                for(int k=0;k*p+j<=m;++k){
                    const int now=k*p+j;
                    if(k-l>amt[i]){
                        cur-=dp[f^1][l*p+j];
                        ++l;
                    }
                    cur+=dp[f^1][now];
                    if(!dp[f][now]&&cur){
                        dp[f][now]=1;
                        ++ans;
                    }
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
