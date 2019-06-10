#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=20005;
int n,ans,dp[N][4];

namespace utils{
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

int gcd(const int x,const int y){
	return y?gcd(y,x%y):x;
}

namespace G{
	int cnt,fir[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<1];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	inline void clear(){
		cnt=ans=0;
		memset(fir+1,0,n*sizeof(int));
	}

	void dfs(const int x,const int fa){
		static int tmp[4];
		dp[x][0]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa) continue;
			dfs(y,x);
			for(int j=0; j<4; ++j){
				tmp[(j+eg[i].wi)%4]=dp[y][j];
			}
			ans+=dp[x][0]*tmp[0];
			ans+=dp[x][1]*tmp[3];
			ans+=dp[x][2]*tmp[2];
			ans+=dp[x][3]*tmp[1];
			for(int j=0; j<4; ++j){
				dp[x][j]+=tmp[j];
			}
		}
	}
}

int main(){
	while(~scanf("%d",&n)){
		if(n==0) break;
		G::clear();
		memset(dp+1,0,n*sizeof(dp[0]));
		ans=0;
		for(int i=1; i<n; ++i){
			const int a=nxi(),b=nxi(),v=nxi();
			G::add(a,b,v);
			G::add(b,a,v);
		}
		G::dfs(1,1);
		ans=ans*2+n;
		int g=gcd(ans,n*n);
		printf("%d/%d\n",ans/g,n*n/g);
	}
	return 0;
}
