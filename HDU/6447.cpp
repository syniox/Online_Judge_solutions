#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;
using lint=long long;

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<=y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>=y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	static struct{
		template <class T> operator T(){
			T x=0;
			char c;
			while(((c=getchar())>'9'||c<'0')&&c!='-');
			const bool f=c=='-'&&(c=getchar());
			while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
			return f?-x:x;
		}
	}ni;
}
using namespace utils;

const int N=1e5+5;
int n,tot;
struct par{
	int x,y,v;
}pr[N];

namespace D{
	int cnt,v[N];
	inline void insert(const int i){
		v[++cnt]=i;
	}
	inline void build(){
		sort(v+1,v+cnt+1);
		cnt=unique(v+1,v+cnt+1)-v-1;
	}
	int ask(const int x){
		return lower_bound(v+1,v+cnt+1,x)-v;
	}
}

namespace T{
	int tr[N];
	inline void reset(){
		memset(tr+1,0,n*sizeof(int));
	}
	inline int qry(int x){
		int ans=0;
		for(; x; x-=x&-x) apx(ans,tr[x]);
		return ans;
	}
	inline void apl(int x,const int v){
		for(; x<=tot; x+=x&-x) apx(tr[x],v);
	}
}

int main(){
	for(int T=ni; T--; ){
		n=ni;
		T::reset();
		D::cnt=0;
		for(int i=1; i<=n; ++i){
			pr[i].x=ni,pr[i].y=ni,pr[i].v=ni;
		}
		for(int i=1; i<=n; ++i) D::insert(pr[i].x);
		D::build();
		for(int i=1; i<=n; ++i) pr[i].x=D::ask(pr[i].x);
		D::cnt=0;
		for(int i=1; i<=n; ++i) D::insert(pr[i].y);
		D::build();
		for(int i=1; i<=n; ++i) pr[i].y=D::ask(pr[i].y);
		tot=D::cnt;
		sort(pr+1,pr+n+1,[](par a,par b){
				return a.x==b.x?a.y>b.y:a.x<b.x; 
				});
		for(int i=1; i<=n; ++i){
			int mx=T::qry(pr[i].y-1);
			T::apl(pr[i].y,pr[i].v+mx);
		}
		printf("%d\n",T::qry(tot));
	}
	return 0;
}
