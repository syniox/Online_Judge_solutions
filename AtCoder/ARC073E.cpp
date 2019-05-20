#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=2e5+5;
int n;
struct data{
	int x,y;
	friend bool operator < (const data &a,const data &b){
		return a.x==b.x?a.y<b.y:a.x<b.x;
	}
}dt[N];

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
	inline void apx(T &x,const T y){
		x<y?x=y:0;
	}

	template <class T>
	inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
}
using namespace utils;

lint s1(){
	int n1,x1,n2,x2;
	n1=x1=dt[1].x;
	n2=x2=dt[1].y;
	for(int i=2; i<=n; ++i){
		apn(n1,dt[i].x),apx(x1,dt[i].x);
		apn(n2,dt[i].y),apx(x2,dt[i].y);
	}
	return (lint)(x1-n1)*(x2-n2);
}

lint s2(){
	int xr=0;
	for(int i=1; i<=n; ++i){
		apx(xr,dt[i].y);
	}
	const int wgt=xr-dt[1].x;
	int len=2e9,npos=2e9,xpos=0;
	for(int i=1; i<n; ++i){
		apn(npos,dt[i].y);
		apx(xpos,dt[i].y);
		int l=std::min(npos,dt[i+1].x);
		int r=std::max(xpos,dt[n].x);
		apn(len,r-l);
	}
	return (lint)len*wgt;
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		dt[i].x=nxi(),dt[i].y=nxi();
		if(dt[i].x>dt[i].y){
			std::swap(dt[i].x,dt[i].y);
		}
	}
	std::sort(dt+1,dt+n+1);
	printf("%lld\n",std::min(s1(),s2()));
	return 0;
}
