#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=525015;
int n,val[N],rt[N];
lint ans;

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
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

namespace T{
	int cnt;
	struct node{
		int ls,rs,s;
		bool sz;
	}tr[N*22];

	inline void upd(const int k){
		node *l=tr+tr[k].ls,*r=tr+tr[k].rs;
		tr[k].s=((l->s^r->s)<<1)+r->sz;
		tr[k].sz=l->sz^r->sz;
	}

	void merge(int &rt,const int l,const int r){
		if(!l||!r) return rt=l+r,void();
		rt=l;
		merge(tr[rt].ls,tr[l].ls,tr[r].ls);
		merge(tr[rt].rs,tr[l].rs,tr[r].rs);
		if(tr[rt].ls||tr[rt].rs) upd(rt);
		else tr[rt].sz^=tr[r].sz;
	}
	void apl(int k){
		if(!(tr[k].ls||tr[k].rs)) return;
		std::swap(tr[k].ls,tr[k].rs);
		if(tr[k].ls) apl(tr[k].ls);
		upd(k);
	}
	int build(int x){
		int k=++cnt;
		assert(cnt<N*22);
		tr[k].sz=1;
		for(int c,i=0,l=k; i<21; l=c,x>>=1,++i){
			c=++cnt;
			tr[c].sz=1;
			tr[l].s=x;
			if(x&1) tr[l].rs=c;
			else tr[l].ls=c;
		}
		return k;
	}
}

namespace G{
	int cnt,fir[N];
	struct edge{
		int to,nx;
	}eg[N<<1];
	
	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs(const int x){
		//eprintf("in%d\n",x);
		for(int i=fir[x]; i; i=eg[i].nx){
			dfs(eg[i].to);
			//eprintf("out%d\n",x);
			T::merge(rt[x],rt[x],rt[eg[i].to]);
		}
		T::apl(rt[x]);
		T::merge(rt[x],rt[x],T::build(val[x]));
		ans+=T::tr[rt[x]].s;
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i)
		val[i]=nxi();
	for(int i=2; i<=n; ++i)
		G::add(nxi(),i);
	G::dfs(1);
	printf("%lld\n",ans);
	return 0;
}
