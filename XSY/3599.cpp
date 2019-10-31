#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int mod=19491001;

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline lint nxi(){
		lint x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

struct mtrx{
	int v[2][2];
	friend mtrx operator * (const mtrx &a,const mtrx &b){
		mtrx c;
		c.v[0][0]=((lint)a.v[0][0]*b.v[0][0]+(lint)a.v[0][1]*b.v[1][0])%mod;
		c.v[0][1]=((lint)a.v[0][0]*b.v[0][1]+(lint)a.v[0][1]*b.v[1][1])%mod;
		c.v[1][0]=((lint)a.v[1][0]*b.v[0][0]+(lint)a.v[1][1]*b.v[1][0])%mod;
		c.v[1][1]=((lint)a.v[1][0]*b.v[0][1]+(lint)a.v[1][1]*b.v[1][1])%mod;
		return c;
	}
};

int main(){
	lint n=nxi();
	if(n==1||n==2){
		printf("%lld\n",n-1);
		return 0;
	}
	n-=2;
	mtrx step;
	step.v[0][1]=step.v[1][0]=step.v[1][1]=1;
	step.v[0][0]=0;
	mtrx ans;
	for(bool f=0; n; step=step*step,n>>=1){
		if(n&1){
			if(f) ans=ans*step;
			else ans=step,f=1;
		}
	}
	printf("%d\n",(ans.v[0][0]+ans.v[0][1]+ans.v[1][0]+ans.v[1][1]-1)%mod);
	return 0;
}
