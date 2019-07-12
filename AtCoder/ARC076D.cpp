#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
int n;
struct _pair{
	int id,x,y;
}pnt[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
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

bool cmp_x(const _pair &a,const _pair &b){
	return a.x<b.x;
}

bool cmp_y(const _pair &a,const _pair &b){
	return a.y<b.y;
}

namespace G{
	int cnt,fa[N];
	struct edge{
		int x,y,v;
		friend bool operator < (const edge &a,const edge &b){
			return a.v<b.v;
		}
	}eg[N<<2];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){a,b,v};
	}

	int find_rt(const int x){
		return fa[x]?fa[x]=find_rt(fa[x]):x;
	}

	int kruskal(){
		std::sort(eg+1,eg+cnt+1);
		int ans=0;
		for(int i=1; i<=cnt; ++i){
			int x=find_rt(eg[i].x),y=find_rt(eg[i].y);
			if(x==y) continue;
			fa[x]=y;
			ans+=eg[i].v;
		}
		return ans;
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		pnt[i].id=i;
		pnt[i].x=nxi(),pnt[i].y=nxi();
	}
	std::sort(pnt+1,pnt+n+1,cmp_x);
	for(int i=1; i<n; ++i){
		int res=std::min(pnt[i+1].x-pnt[i].x,cabs(pnt[i+1].y-pnt[i].y));
		G::add(pnt[i].id,pnt[i+1].id,res);
	}
	std::sort(pnt+1,pnt+n+1,cmp_y);
	for(int i=1; i<n; ++i){
		int res=std::min(pnt[i+1].y-pnt[i].y,cabs(pnt[i+1].x-pnt[i].x));
		G::add(pnt[i].id,pnt[i+1].id,res);
	}
	printf("%d\n",G::kruskal());
	return 0;
}
