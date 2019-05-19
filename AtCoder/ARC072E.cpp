#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=5e5+5;
int n,m,val[N],pos[N],np[N];

namespace utils{
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}

	template <class T>
	inline T cabs(const T x){
		return x<0?-x:x;
	}

	template <class T>
	inline void apx(T &x,const T y){
		x<y?x=y:0;
	}

	template <class T>
	inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
}
using namespace utils;

int main(){
	n=nxi(),m=nxi();
	pos[0]=m;
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		pos[i]=std::min(pos[i-1],cabs(pos[i-1]-val[i]));
	}
	np[n+1]=1;
	for(int i=n; i; --i){
		np[i]=np[i+1]+val[i]*(val[i]<np[i+1]<<1);
	}
	for(int q=nxi(); q; --q){
		const int x=nxi();
		puts(pos[x-1]>=np[x+1]?"YES":"NO");
	}
	return 0;
}
