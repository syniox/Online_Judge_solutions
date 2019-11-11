#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
typedef long long lint;
const int N=5005;
const int mod=1e9+9;
int n,tot,val[N],buk[N],sum[N],dp[N][N],C[N][N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace D{
	int tot,v[N<<1];
	inline void insert(const int x){
		v[++tot]=x;
	}
	inline void build(){
		std::sort(v+1,v+tot+1);
		tot=std::unique(v+1,v+tot+1)-v-1;
	}
	inline int ask(const int x){
		return std::lower_bound(v+1,v+tot+1,x)-v;
	}
}

inline void apadd(int &x,const lint y){
	x=(x+y)%mod;
}

int getC(const int x,const int y){
	if(x<0||y<0) return 0;
	return C[x][y];
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		D::insert(val[i]=nxi());
	}
	D::build();
	for(int i=1; i<=n; ++i){
		++buk[val[i]=D::ask(val[i])];
	}
	tot=D::tot;
	for(int i=0; i<=n; ++i){
		C[i][0]=1;
		for(int j=1; j<=i; ++j){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
		}
		if(i) sum[i]=sum[i-1]+buk[i];
	}
	dp[1][1]=1;
	for(int i=1; i<tot; ++i){
		for(int j=1; j<=sum[i]+1; ++j){
			if(!dp[i][j]) continue;
			const int cur=dp[i][j],rem=C[sum[i+1]-j][buk[i+1]];
			apadd(dp[i+1][j],(lint)cur*rem);
			for(int k=sum[i]+2; k<=sum[i+1]+1; ++k){
				int rst=buk[i+1]-(sum[i+1]-k+1),tot=C[sum[i]+rst-1][rst];
				apadd(dp[i+1][k],(lint)cur*(tot-getC(sum[i]+rst-1-j,rst)));
			}
		}
		apadd(dp[i+1][sum[i]+1],dp[i][sum[i]+1]);
	}
	printf("%d\n",(dp[tot][n+1]+mod)%mod);
	return 0;
}
