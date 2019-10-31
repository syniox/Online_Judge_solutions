#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
typedef long long lint;
const int N=5e5+5;
int n,q,val[N];
lint ans[N];
struct qry{
	int l,id;
};
std::vector <qry> qbuk[N];

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

namespace T{
	int x,y,v;
	struct node{
		int min,cntn,dlt,dcnt;
		lint cnt0;
		void getpsh(const int d,const int dc){
			dlt+=d,min+=d;
			dcnt+=dc;
			cnt0+=(lint)dc*cntn;
			assert(min>=0);
		}
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		node &k=tr[idx(l,r)],&ls=tr[idx(l,mid)],&rs=tr[idx(mid+1,r)];
		k.min=std::min(ls.min,rs.min);
		k.cntn=0;
		if(k.min==ls.min) k.cntn+=ls.cntn;
		if(k.min==rs.min) k.cntn+=rs.cntn;
		k.cnt0=ls.cnt0+rs.cnt0;
	}

	inline void psh(const int l,const int r){
		const int k=idx(l,r),mid=(l+r)>>1;
		const int ls=idx(l,mid),rs=idx(mid+1,r);
		int &d=tr[k].dlt,&dc=tr[k].dcnt;
		if(!d&&!dc) return;
		tr[ls].getpsh(d,dc*(tr[ls].min+d==tr[k].min));
		tr[rs].getpsh(d,dc*(tr[rs].min+d==tr[k].min));
		d=dc=0;
	}

	void build(const int l,const int r){
		if(l==r){
			tr[idx(l,r)].cntn=tr[idx(l,r)].cnt0=1;
			return;
		}
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
		upd(l,r);
	}

	void add_t(const int l,const int r){
		if(l>=x&&r<=y){
			tr[idx(l,r)].getpsh(v,tr[idx(l,r)].min==-v);
			return;
		}
		psh(l,r);
		const int mid=(l+r)>>1;
		if(x<=mid) add_t(l,mid);
		if(y>mid) add_t(mid+1,r);
		upd(l,r);
	}

	lint ask_t(const int l,const int r){
		if(l>=x&&r<=y) return tr[idx(l,r)].cnt0;
		psh(l,r);
		const int mid=(l+r)>>1;
		lint ans=0;
		if(x<=mid) ans+=ask_t(l,mid);
		if(y>mid) ans+=ask_t(mid+1,r);
		return ans;
	}

	inline void add(const int l,const int r,const int v){
		if(!v||l>r) return;
		T::x=l,T::y=r,T::v=v;
		add_t(1,n);
	}

	inline lint ask(const int l,const int r){
		T::x=l,T::y=r;
		return ask_t(1,n);
	}
}

void solve(){
	static int st_x[N],st_n[N];
	int topx=0,topn=0;
	for(int i=1; i<=n; ++i){
		for(; topx&&val[st_x[topx]]<=val[i]; --topx){
			T::add(st_x[topx-1]+1,st_x[topx],val[i]-val[st_x[topx]]);
		}
		st_x[++topx]=i;
		for(; topn&&val[st_n[topn]]>=val[i]; --topn){
			T::add(st_n[topn-1]+1,st_n[topn],val[st_n[topn]]-val[i]);
		}
		st_n[++topn]=i;
		if(i>1) T::add(1,i-1,-1);
		for(std::vector <qry> ::iterator it=qbuk[i].begin(); it!=qbuk[i].end(); ++it){
			ans[it->id]=T::ask(it->l,i);
		}
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	T::build(1,n);
	q=nxi();
	for(int i=1; i<=q; ++i){
		const int l=nxi(),r=nxi();
		qbuk[r].push_back((qry){l,i});
	}
	solve();
	for(int i=1; i<=q; ++i){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
