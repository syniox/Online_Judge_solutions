#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
lint val[N],v1[N];
struct _pair{
	lint x,y;
	friend bool operator < (const _pair &a,const _pair &b){
		return a.x==b.x?a.y<b.y:a.x<b.x;
	}
}pep[N];

namespace utils{
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	inline lint nxi(FILE *fd=stdin){
		lint x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

int main(){
	static lint buk[N];
	int n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<n; ++i){
		v1[i]=nxi();
	}
	{
		pep[1]=(_pair){val[1],-val[1]};
		lint pre1=0,pre2=0;
		for(int i=1; i<n; ++i){
			lint v2=nxi();
			if(v2<v1[i]){
				puts("-1");
				return 0;
			}
			pre1+=v1[i],pre2+=v2;
			pep[i+1]=(_pair){val[i+1]-pre1,pre2-val[i+1]};
		}
	}
	std::sort(pep+1,pep+n+1);
	int top=0;
	buk[0]=-1e18;
	for(int i=1; i<=n; ++i){
		if(pep[i].y>=buk[top]) buk[++top]=pep[i].y;
		else *std::upper_bound(buk+1,buk+top+1,pep[i].y)=pep[i].y;
	}
	printf("%d\n",n-top);
	return 0;
}
