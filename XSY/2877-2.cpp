#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=2e5+5;
const int mod=1e9+7;
int n,m,q,tot,pl[N],pr[N],dp[N<<1][3];
int mxst[2][N<<1];//0: 找工作 1: 家里蹲

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

namespace D{
	int cnt,v[N<<1];
	inline void add(const int x){
		v[++cnt]=x;
	}
	inline void build(){
		sort(v+1,v+cnt+1);
		cnt=unique(v+1,v+cnt+1)-v-1;
	}
	inline int ask(const int x){
		return lower_bound(v+1,v+cnt+1,x)-v;
	}
}

inline int qsum(int pos,int stat){
	int ans=0;
	for(int i=0; i<3; ++i){
		if(stat>>i&1) ans=(ans+dp[pos][i])%mod;
	}
	return ans;
}

int main(){
	q=nxi(),n=nxi(),m=nxi();
	for(int i=1; i<=n+m; ++i){
		pl[i]=nxi(),pr[i]=nxi();
		D::add(pl[i]),D::add(pr[i]+1);
	}
	D::add(1);
	D::add(q+1);
	D::build();
	tot=D::cnt;
	for(int i=1; i<=n+m; ++i){
		pl[i]=D::ask(pl[i]);
		pr[i]=D::ask(pr[i]+1)-1;
		apx(mxst[i>n][pr[i]],pl[i]);
	}
	dp[0][2]=1;
	for(int p0=0,p1=0,i=1; i<tot; ++i){
		dp[i][2]=(lint)qsum(i-1,7)*(fpow(2,D::v[i+1]-D::v[i])-2+mod)%mod;
		if(i>1){
			for(int j=0; j<3; ++j){
				dp[i-1][j]=(dp[i-1][j]+dp[i-2][j])%mod;
			}
		}
		apx(p0,mxst[0][i]);
		apx(p1,mxst[1][i]);
		dp[i][0]=(qsum(i-1,6)-(p1?qsum(p1-1,6):0)+mod)%mod;
		dp[i][1]=(qsum(i-1,5)-(p0?qsum(p0-1,5):0)+mod)%mod;
	}
	printf("%d\n",qsum(tot-1,7));
	return 0;
}
