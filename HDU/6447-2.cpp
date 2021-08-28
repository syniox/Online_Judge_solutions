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
	int tr[N<<2];
	inline void reset(){
		//memset(tr+1,0,n*sizeof(int));
		memset(tr+1,0,(n*4)*sizeof(int));
	}
	int qry(const int k,const int l,const int r,const int x,const int y){
		assert(k);
		if(l>=x&&r<=y) return tr[k];
		const int mid=(l+r)>>1;
		int ans=0;
		if(x<=mid) apx(ans,qry(k<<1,l,mid,x,y));
		if(y>mid) apx(ans,qry(k<<1|1,mid+1,r,x,y));
		return ans;
	}
	void apl(const int k,const int l,const int r,const int x,const int v){
		apx(tr[k],v);
		if(l==r) return;
		const int mid=(l+r)>>1;
		if(x<=mid) apl(k<<1,l,mid,x,v);
		else apl(k<<1|1,mid+1,r,x,v);
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
			int mx=pr[i].y>1?T::qry(1,1,tot,1,pr[i].y-1):0;
			T::apl(1,1,tot,pr[i].y,pr[i].v+mx);
		}
		printf("%d\n",T::tr[1]);
	}
	return 0;
}
