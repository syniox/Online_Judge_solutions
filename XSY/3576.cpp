#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
const int mod=998244353;
int n,val[N];

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

struct mtrx{
	int v00,v01,v10,v11;
	friend mtrx operator * (const mtrx &a,const mtrx &b){
		mtrx c;
		c.v00=((lint)a.v00*b.v00+(lint)a.v01*b.v10)%mod;
		c.v01=((lint)a.v00*b.v01+(lint)a.v01*b.v11)%mod;
		c.v10=((lint)a.v10*b.v00+(lint)a.v11*b.v10)%mod;
		c.v11=((lint)a.v10*b.v01+(lint)a.v11*b.v11)%mod;
		return c;
	}
}ps[N],ips[N];

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi()%mod;
		ps[i]=(mtrx){val[i],1,1,0};
		ips[i]=(mtrx){0,1,1,mod-val[i]};
	}
	for(int i=n-1; i>=1; --i){
		ps[i]=ps[i+1]*ps[i];
		ips[i]=ips[i]*ips[i+1];
	}
	for(int q=nxi(); q; --q){
		int l=nxi(),r=nxi(),ans;
		mtrx res=ips[r]*ps[l];
		ans=((lint)val[r]*res.v00+res.v10)%mod;
		ans=(lint)ans*fpow(((lint)val[r]*res.v01+res.v11)%mod,mod-2)%mod;
		printf("%d\n",ans);
	}
	return 0;
}
