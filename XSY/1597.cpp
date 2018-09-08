#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=3e5+2;
int n,vl[N];
lint dp[N][2][3];

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}
template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,fir[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<1];
	inline void init(){
		cnt=1;
		memset(fir,0,sizeof(fir));
	}
	inline void add(int a,int b,int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}
	void dfs(int x,int fa){
		if(vl[x]==0) dp[x][1][0]=0;
		else if(vl[x]==1) dp[x][0][1]=0;
		else dp[x][0][0]=0;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa){
				dfs(y,x);
				lint ndp=1e16;
				for(int j=0;j<2;++j){
					for(int k=0;k<3;++k) apn(ndp,dp[y][j][k]);
				}
				for(int j=1;j>=0;--j){
					for(int k=2;k>=0;--k){
						if(j==1&&k==2) continue;
						lint tp=1e16;
						for(int l=j;l>=0;--l){
							for(int m=k;m>=0;--m){
								if(dp[x][l][m]<1e15){
									apn(tp,dp[x][l][m]+dp[y][j-l][k-m]);
								}
							}
						}
						apn(tp,dp[x][j][k]+ndp+eg[i].wi);
						dp[x][j][k]=tp;
					}
				}
			}
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	int T=nxi();
	while(T--){
		G::init();
		memset(dp,1,sizeof(dp));
		n=nxi();
		for(int i=1;i<=n;++i){
			vl[i]=nxi();
		}
		for(int i=1;i<n;++i){
			const int a=nxi(),b=nxi(),v=nxi();
			G::add(a,b,v);
			G::add(b,a,v);
		}
		G::dfs(1,0);
		lint ans=1e18;
		for(int i=0;i<2;++i){
			apn(ans,std::min(dp[1][0][i],dp[1][1][i]));
		}
		apn(ans,dp[1][0][2]);
		printf("%lld\n",ans);
	}
	return 0;
}
