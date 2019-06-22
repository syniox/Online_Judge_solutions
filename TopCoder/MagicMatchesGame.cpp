#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=52;
int n,tot;
lint ans,val[N];
struct data{
	int a,b,c;
}dt[N];

namespace utils{
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
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

namespace X{
	int tot,val[25];
	inline void clear(){
		memset(val,0,sizeof(val));
		tot=0;
	}
	bool insert(int x){
		for(int i=24; ~i; --i){
			if((x>>i&1)==0) continue;
			if(val[i]) x^=val[i];
			else{
				val[i]=x;
				++tot;
				return 1;
			}
		}
		return 0;
	}
}

inline bool cmp_val(const int a,const int b){
	return val[a]<val[b];
}

std::pair <int,int> get_pr(const lint a,const lint b){
	static int idx[N];
	X::clear();
	for(int i=1; i<=n; ++i){
		idx[i]=i;
		val[i]=(lint)dt[i].b*a+dt[i].c*b;
	}
	std::sort(idx+1,idx+n+1,cmp_val);
	int cx=0,cy=0;
	for(int i=1; i<=n; ++i){
		const int x=idx[i];
		if(!X::insert(dt[x].a)) continue;
		cx+=dt[x].b;
		cy+=dt[x].c;
	}
	apn(ans,(lint)cx*cy);
	return std::make_pair(cx,cy);
}

template <class T>
void solve(const T &x,const T &y){
	int wx=x.second+y.second,wy=x.first+y.first;
	T mid=get_pr(wx,wy);
	if(mid==x||mid==y) return;
	solve(x,mid);
	solve(mid,y);
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		dt[i].a=nxi(),dt[i].b=nxi(),dt[i].c=nxi();
	}
	ans=1e12;
	std::pair <int,int> px=get_pr(1,0);
	std::pair <int,int> py=get_pr(0,1);
	if(px!=py){
		solve(px,py);
	}
	printf("%lld\n",ans);
	return 0;
}
