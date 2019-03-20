#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=5e5+5;
int n,tot,val[N],cdt,cur_mid[N];
class _Pair{
	public:
		int x,y;
}dt[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace D{
	int buk[N],*pt=buk;
	inline void insert(const int x){
		*pt++=x;
	}
	inline void build(){
		std::sort(buk,pt);
		pt=std::unique(buk,pt);
	}
	inline int ask(const int x){
		return std::lower_bound(buk,pt,x)-buk+1;
	}
}

namespace T{
	int x,v,cnt,rt[N];
	class tr{
		public:
			int ls,rs,v;
	}tr[N*21];

	inline void upd(const int k){
		tr[k].v=tr[tr[k].ls].v+tr[tr[k].rs].v;
	}

	void mod_t(int &k,const int p,const int l,const int r){
		k=++cnt;
		tr[k]=tr[p];
		if(l==r){
			++tr[k].v;
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(tr[k].ls,tr[p].ls,l,mid);
		else mod_t(tr[k].rs,tr[p].rs,mid+1,r);
		upd(k);
	}

	int ask_t(const int p,const int k,const int l,const int r){
		//assert(tr[k].v-tr[p].v>=v);
		if(l==r) return l;
		const int lsum=tr[tr[k].ls].v-tr[tr[p].ls].v;
		const int mid=(l+r)>>1;
		if(v<=lsum) return ask_t(tr[p].ls,tr[k].ls,l,mid);
		v-=lsum;
		return ask_t(tr[p].rs,tr[k].rs,mid+1,r);
	}

	inline void mod(const int ver,const int x){
		T::x=x;
		mod_t(rt[ver],rt[ver-1],1,tot);
	}

	inline int ask(const int x,const int y,const int v){
		//assert(x<=y);
		T::v=v;
		return ask_t(rt[x-1],rt[y],1,tot);
	}
}

inline int get_mid(_Pair x){
	return D::buk[T::ask(x.x,x.y,(x.y-x.x+1+1)>>1)-1];
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		D::insert(val[i]);
	}
	D::build();
	tot=D::pt-D::buk;
	for(int i=1; i<=n; ++i){
		T::mod(i,D::ask(val[i]));
	}
	for(int i=1; i<=n; ++i){
		dt[++cdt]=(_Pair){i,i};
		cur_mid[cdt]=val[i];
		for(; cdt>1; --cdt){
			if(cur_mid[cdt-1]<=cur_mid[cdt]) break;
			dt[cdt-1].y=dt[cdt].y;
			cur_mid[cdt-1]=get_mid(dt[cdt-1]);
		}
	}
	lint ans=0;
	for(int i=1; i<=cdt; ++i){
		for(int j=dt[i].x; j<=dt[i].y; ++j){
			ans+=abs(cur_mid[i]-val[j]);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
