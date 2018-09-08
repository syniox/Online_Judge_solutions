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

inline char get_c(){
	static char buf[20000],*h,*t;
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
	}
	return h==t?EOF:*h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
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
		dp[x][vl[x]==0][vl[x]==1]=0;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa){
				dfs(y,x);
				lint ndp=1e16;
				for(int j=0;j<2;++j){
					for(int k=0;k<3;++k){
						if(j==1&&k==2) break;
						apn(ndp,dp[y][j][k]);
					}
				}
				for(int j=1;j>=0;--j){
					for(int k=2;k>=0;--k){
						if((j==1&&k==2)||dp[x][j][k]>1e15) continue;
						const lint tp=dp[x][j][k];
						dp[x][j][k]+=ndp+eg[i].wi;
						for(int l=0;l<2;++l){
							for(int m=0;m<3;++m){
								const int t1=std::min(1,j+l),t2=std::min(2,k+m);
								if(t1==1&&t2==2) continue;
								apn(dp[x][t1][t2],tp+dp[y][l][m]);
							}
						}
					}
				}
			}
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("6.in","r",stdin);
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
