#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
const int N=2e5+5;
int n,q,val[N],tot;
struct opt{
	int x,v;
}op[N];

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

namespace D{
	int cnt,val[N*2];
	inline void insert(const int v){
		val[++cnt]=v;
	}
	inline int build(){
		std::sort(val+1,val+cnt+1);
		cnt=std::unique(val+1,val+cnt+1)-val-1;
		return cnt;
	}
	inline int ask(const int v){
		return std::lower_bound(val+1,val+cnt+1,v)-val;
	}
}

namespace B{
	int tr[N*2];
	inline void add(int x,const int v){
		for(; x<=tot; x+=x&-x) tr[x]+=v;
	}
	inline int ask(int x){
		int ans=0;
		for(; x; x-=x&-x) ans+=tr[x];
		return ans;
	}
}

void mod(const int x,const int f){
	if(val[x]>val[x-1]){
		B::add(val[x-1]+1,f);
		B::add(val[x]+1,-f);
	}
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		D::insert(val[i]);
	}
	for(int i=1; i<=q; ++i){
		if(nxi()==1) op[i].v=nxi();
		else op[i].x=nxi(),op[i].v=nxi();
		D::insert(op[i].v);
	}
	tot=D::build();
	for(int i=1; i<=n; ++i){
		val[i]=D::ask(val[i]);
	}
	for(int i=1; i<=q; ++i){
		op[i].v=D::ask(op[i].v);
	}
	for(int i=1; i<=n; ++i){
		mod(i,1);
	}
	for(int i=1; i<=q; ++i){
		const int x=op[i].x;
		if(x==0) printf("%d\n",B::ask(op[i].v));
		else{
			mod(x,-1);
			if(x<n) mod(x+1,-1);
			val[x]=op[i].v;
			mod(x,1);
			if(x<n) mod(x+1,1);
		}
	}
	return 0;
}
