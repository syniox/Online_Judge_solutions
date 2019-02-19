#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=13;
const int mod=1e7+7;
const lint _lim=6e18;
int n,m;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

class mtrx{
	public:
		int n,x[N][N];
		mtrx(int len){
			n=len;
			memset(x,0,sizeof(x));
			for(int i=1; i<=n; ++i) x[i][i]=1; 
		}

		friend mtrx operator * (const mtrx &a,const mtrx &b){
			mtrx c(a.n);
			for(int i=1; i<=c.n; ++i){
				for(int j=1; j<=c.n; ++j){
					lint tp=0;
					for(int k=1; k<=c.n; ++k){
						tp+=(lint)a.x[i][k]*b.x[k][j];
						if(tp>_lim) tp%=mod;
					}
					c.x[i][j]=tp%mod;
				}
			}
			return c;
		}
}stp(0);

class vec{
	public:
		int n,x[N];

		friend vec operator * (const vec &a,const mtrx &b){
			vec c;
			c.n=a.n;
			for(int i=1; i<=c.n; ++i){
				lint tp=0;
				for(int j=1; j<=c.n; ++j){
					tp+=(lint)a.x[j]*b.x[j][i];
					if(tp>_lim) tp%=mod;
				}
				c.x[i]=tp%mod;
			}
			return c;
		}
};

inline void build_stp(){
	memset(stp.x,0,sizeof(stp.x));
	stp.n=n+2;
	stp.x[1][1]=10,stp.x[n+2][1]=3;
	for(int i=2; i<=n+1; ++i){
		for(int j=1; j<=i; ++j) stp.x[j][i]=1;
	}
	stp.x[n+2][n+2]=1;
}

inline mtrx fpow(mtrx x,int t){
	mtrx ans(x.n);
	for(; t; x=x*x,t>>=1){
		if(t&1) ans=ans*x;
	}
	return ans;
}

int main(){
	vec ans;
	while(~scanf("%d%d",&n,&m)){
		ans.n=n+2;
		ans.x[1]=233;
		for(int i=1; i<=n; ++i){
			ans.x[i+1]=nxi();
		}
		ans.x[n+2]=1;
		build_stp();
		stp=fpow(stp,m);
		ans=ans*stp;
		printf("%d\n",ans.x[n+1]);
	}
	return 0;
}
