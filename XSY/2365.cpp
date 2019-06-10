#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=3e7+5;
int n,val[N];

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

void build(){
	unsigned s=nxi(),b=nxi(),c=nxi(),d=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=i;
		s=((unsigned long long)s*b+c)%d;
		std::swap(val[i],val[s%i+1]);
	}
}

int getans(){
	int ans=0;
	for(int i=1; i<=(int)n; ++i){
		apx(ans,i-(int)val[i]);
	}
	return ans;
}

int main(){
	n=nxi();
	build();
	printf("%d\n",getans());
	return 0;
}
