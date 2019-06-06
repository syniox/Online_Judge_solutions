#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=2e5+5;
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

namespace G{
	int cnt,fa[N];
	struct edge{
		int x,y,v;
		friend bool operator < (const edge &a,const edge &b){
			return a.v<b.v;
		}
	}eg[N<<1];

	int find_rt(const int x){
		return ~fa[x]?fa[x]=find_rt(fa[x]):x;
	}

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){a,b,v};
	}

	lint kruskal(){
		memset(fa,-1,n*sizeof(int));
		std::sort(eg+1,eg+cnt+1);
		lint ans=0;
		for(int i=1; i<=cnt; ++i){
			const int x=find_rt(eg[i].x),y=find_rt(eg[i].y);
			if(x==y) continue;
			fa[x]=y;
			ans+=eg[i].v;
		}
		return ans;
	}
}

int main(){
	n=nxi();
	memset(val,20,n*sizeof(int));
	for(int q=nxi(); q; --q){
		const int a=nxi(),b=nxi(),c=nxi();
		G::add(a,b,c);
		apn(val[(a+1)%n],c+1);
		apn(val[(b+1)%n],c+2);
	}
	for(int i=1; i<n; ++i){
		apn(val[i],val[i-1]+2);
	}
	apn(val[0],val[n-1]+2);
	for(int i=1; i<n; ++i){
		apn(val[i],val[i-1]+2);
	}
	G::add(n-1,0,val[0]);
	for(int i=1; i<n; ++i){
		G::add(i-1,i,val[i]);
	}
	printf("%lld\n",G::kruskal());
	return 0;
}
