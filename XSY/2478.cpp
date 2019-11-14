#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <bitset>
typedef long long lint;
const int N=102;
int n,m;
struct edge{
	int x,y,t;
	friend bool operator < (const edge &a,const edge &b){
		return a.t<b.t;
	}
}eg[N];

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

struct mtrx{
	std::bitset <N> v[N];
	inline void clear(){
		for(int i=1; i<=n; ++i){
			v[i].reset();
		}
	}
	friend mtrx operator * (const mtrx &a,const mtrx &b){
		mtrx c;
		memset(c.v,0,sizeof(c.v));
		for(int i=1; i<=n; ++i){
			for(int j=1; j<=n; ++j){
				if(!a.v[i][j]) continue;
				c.v[i]|=b.v[j];
			}
		}
		return c;
	}
};

struct vec{
	std::bitset <N> v;
	inline void clear(){
		v.reset();
	}
	vec operator * (const mtrx &b){
		vec c;
		c.v.reset();
		for(int i=1; i<=n; ++i){
			c.v[i]=(v&b.v[i]).any();
		}
		return c;
	}
};

int solve(){
	if(eg[1].t) return -1;
	vec cur;
	cur.clear();
	cur.v[1]=1;
	mtrx step,mul;
	step.clear();
	for(int i=1; i<=m; ++i){
		int tmp=std::min(n,eg[i].t-eg[i-1].t);
		for(int j=1; j<=tmp; ++j){
			cur=cur*step;
			if(cur.v[n]){
				return eg[i-1].t+j;
			}
		}
		tmp=eg[i].t-eg[i-1].t-tmp;
		if(tmp){
			mul=step;
			for(; tmp; mul=mul*mul,tmp>>=1){
				if(tmp&1) cur=cur*mul;
			}
		}
		step.v[eg[i].y][eg[i].x]=1;
	}
	for(int i=1; i<=n; ++i){
		cur=cur*step;
		if(cur.v[n]) return eg[m].t+i;
	}
	return -1;
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=m; ++i){
		eg[i].x=nxi(),eg[i].y=nxi(),eg[i].t=nxi();
	}
	std::sort(eg+1,eg+m+1);
	int ans=solve();
	if(ans<0) puts("Impossible");
	else printf("%d\n",ans);
	return 0;
}
