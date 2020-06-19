#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=3005;
int n,m,pos[N],dsc[N],dp[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
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

struct vec{
	int x,y;
	friend lint crs(const vec &a,const vec &b){
		return (lint)a.x*b.y-(lint)a.y*b.x;
	}
	friend vec operator-(const vec &a,const vec &b){
		return (vec){a.x-b.x,a.y-b.y};
	}
};
struct dat:public vec{
	int id;
	dat(int a,int b,int c):vec((vec){a,b}),id(c){}
	dat(){}
};

inline int gety(const int x){
	return dp[x]+pos[x]*pos[x];
}
inline int getx(const int x){
	return pos[x];
}
inline int getans(const dat &c,const int x){
	return c.y+pos[x]*pos[x]-2*pos[x]*pos[c.id];
}

int jdg(const int offs){
	static dat stk[N];
	int res=1,top=0;
	memset(dp,63,(n+1)*sizeof(dp[0]));
	dp[0]=0;
	for(int i=1; i<=n; ++i){
		dat cur=(dat){getx(i-1),gety(i-1),i-1};
		for(; top>1&&crs(stk[top]-stk[top-1],cur-stk[top-1])<=0; --top);
		stk[++top]=cur;
		apn(res,top);
		for(; res<top&&getans(stk[res+1],i)<getans(stk[res],i); ++res);
		dsc[i]=dsc[stk[res].id]+1;
		dp[i]=getans(stk[res],i)+offs;
	}
	return dsc[n];
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		pos[i]=pos[i-1]+nxi();
	}
	{
		int l=0,r=1e9,mid;//每多选一段加上的权值
		while(l!=r){
			mid=(l+r)>>1;
			if(jdg(mid)>m) l=mid+1;
			else r=mid;
		}
		jdg(l);
		eprintf("l%d dp%d\n",l,dp[n]);
		lint ans=(dp[n]-(lint)l*m)*m;
		printf("%lld\n",ans-(lint)pos[n]*pos[n]);
	}
	return 0;
}
