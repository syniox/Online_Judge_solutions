#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
typedef long long lint;
const int N=302;
const int mod=1e9+7;
int n,m,dp[2][N][N];
struct limit{
    int l,r,x;
    bool operator < (const limit b) const {
        return r<b.r;
    }
}lt[N];
 
inline void twk(int &x){
    if(x>=mod) x-=mod;
}
 
inline int nxi(){
    int x=0;
    char c;
    while((c=getchar())>'9'||c<'0');
    while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
    return x;
}
 
int main(){
#ifndef ONLINE_JUDGE
//  freopen("a.in","r",stdin);
#endif
    n=nxi(),m=nxi();
    for(int i=1;i<=m;++i){
        lt[i].l=nxi();
        lt[i].r=nxi();
        lt[i].x=nxi();
    }
    std::sort(lt+1,lt+m+1);
    dp[1][0][0]=1;
    for(int q=1,i=1;i<n;++i){
        int p=i&1;
        memset(dp[p^1],0,sizeof(dp[p^1]));
        while(lt[q].r<i&&q<=m) ++q;
        for(int j=0;j<=i;++j){
//          for(int k=0;k<j;++k) printf("x ");
            for(int k=j;k<=i;++k){
//              printf("%d ",dp[p][j][k]);
                int tp=q,f=0;
                while(lt[tp].r==i){
                    if((k>=lt[tp].l)+(j>=lt[tp].l)+1!=lt[tp].x){
                        f=1;
                        break;
                    }
                    ++tp;
                }
                if(f==1) continue;
                int cur=dp[p][j][k];
                twk(dp[p^1][j][k]+=cur);
                twk(dp[p^1][j][i]+=cur);
                if(j!=k) twk(dp[p^1][k][i]+=cur);
            }
//          puts("");
        }
//      puts("\n-----\n");
    }
    for(int j=0;j<=n;++j){
        for(int k=j;k<=n;++k){
            int tp=m,f=0;
            while(lt[tp].r==n){
                if((k>=lt[tp].l)+(j>=lt[tp].l)+1!=lt[tp].x){
                    f=1;
                    break;
                }
                --tp;
            }
            if(f) dp[n&1][j][k]=0;
        }
    }
    int ans=0;
    for(int i=0;i<=n;++i){
        for(int j=i;j<=n;++j){
            if(i==0&&j==0) ans=(ans+(lint)dp[n&1][i][j]*3)%mod;
            else ans=(ans+(lint)dp[n&1][i][j]*6)%mod;
        }
    }
    printf("%d\n",ans);
    return 0;
}
