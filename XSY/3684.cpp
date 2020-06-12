#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
const int mod=998244353;
const int inv2=(mod+1)>>1;
int n,m,cbuk[31][N];

namespace utils{
#define eprintf(fmt,...) fprintf(stderr,fmt,##__VA_ARGS__)
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

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		int v=nxi();
		for(int j=0; j<31; ++j){
			cbuk[j][i]=cbuk[j][i-1]+(v>>j&1);
		}
	}
	while(m--){
		int l=nxi(),r=nxi(),v=nxi();
		int ans=0;
		for(int w=1,i=0; i<31; w=(w*2)%mod,++i){
			int s1=cbuk[i][r]-cbuk[i][l-1],s0=(r-l+1)-s1;
			int res=((lint)fpow(1+v,s1)-fpow(1-v,s1))*inv2%mod;
			res=(lint)res*fpow(1+v,s0)%mod;
			ans=(ans+(lint)res*w)%mod;
		}
		printf("%d\n",(ans+mod)%mod);
	}
	return 0;
}
