#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=3e5+5;
int n,row,col;
struct _pair{
	int x,y;
}pnt[N];

inline bool cmp_x(const _pair &a,const _pair &b){
	return a.x<b.x;
}

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

template <class T,size_t S>
class _Disc{
	public:
		T buk[S],*pt;
		int tot;
		_Disc(){pt=buk;}

		inline void insert(const T &v){
			*++pt=v;
		}
		inline void build(){
			std::sort(buk+1,pt+1);
			pt=std::unique(buk+1,pt+1)-1;
			tot=pt-buk;
		}
		inline int ask(const T &v){
			return std::lower_bound(buk+1,pt+1,v)-buk;
		}
};
_Disc <int,N<<1> D;

namespace T{
	int x,y,v,tot;
	struct node{
		int delta,v;
		inline void get_v(const int dlt){
			v+=dlt;
			delta+=dlt;
		}
	}tr[N<<2];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		tr[idx(l,r)].v=std::max(tr[idx(l,mid)].v,tr[idx(mid+1,r)].v);
	}

	inline void psh(const int l,const int r){
		int &d=tr[idx(l,r)].delta;
		if(l==r||!d) return;
		const int mid=(l+r)>>1;
		tr[idx(l,mid)].get_v(d);
		tr[idx(mid+1,r)].get_v(d);
		d=0;
	}

	void build(const int l,const int r){
		if(l==r){
			tr[idx(l,r)].v=v-D.buk[l];
			return;
		}
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
		upd(l,r);
	}

	void add_t(const int l,const int r){
		assert(l<=r);
		if(l>=x&&r<=y){
			tr[idx(l,r)].get_v(v);
			return;
		}
		psh(l,r);
		const int mid=(l+r)>>1;
		if(x<=mid) add_t(l,mid);
		if(y>mid) add_t(mid+1,r);
		upd(l,r);
	}

	inline int qry(){
		return tr[idx(0,tot)].v;
	}

	inline void add(const int x,const int y,const int v){
		if(!v||x>y) return;
		assert(x<=y&&x>=0&&y<=tot);
		T::x=x,T::y=y,T::v=v;
		add_t(0,tot);
	}
}

int solve(const int row,const int col){
	static _pair stk_up[N],stk_dn[N];
	const int tot=D.tot;
	int top_up=0,top_dn=0;
	T::tot=D.tot;
	std::sort(pnt+1,pnt+n+1,cmp_x);
	T::v=row;
	T::build(0,tot);
	pnt[n+1]=(_pair){D.ask(col),0};
	stk_up[++top_up]=(_pair){0,row};
	stk_dn[++top_dn]=(_pair){0,0};
	int ans=std::max(row+1,col+1);
	for(int i=1; i<=n+1; ++i){
		const int x=pnt[i].x,y=pnt[i].y;
		apx(ans,T::qry()+D.buk[x]);
		if(y>row>>1){
			for(int d=stk_up[top_up].y-D.buk[y]; top_up&&d>=0; --top_up){
				T::add(stk_up[top_up].x,x-1,-d);
			}
			stk_up[++top_up]=(_pair){x,D.buk[y]};
		}
		else{
			for(int d=D.buk[y]-stk_dn[top_dn].y; top_dn&&d>=0; --top_dn){
				T::add(stk_dn[top_dn].x,x-1,-d);
			}
			stk_dn[++top_dn]=(_pair){x,D.buk[y]};
		}
	}
	return ans<<1;
}

int main(){
	row=nxi(),col=nxi();
	n=nxi();
	for(int i=1; i<=n; ++i){
		pnt[i].x=nxi(),pnt[i].y=nxi();
		D.insert(pnt[i].x);
		D.insert(pnt[i].y);
	}
	D.insert(0);
	D.insert(row);
	D.insert(col);
	D.build();
	for(int i=1; i<=n; ++i){
		pnt[i].x=D.ask(pnt[i].x);
		pnt[i].y=D.ask(pnt[i].y);
	}
	int ans=solve(row,col);
	for(int i=1; i<=n; ++i){
		std::swap(pnt[i].x,pnt[i].y);
	}
	apx(ans,solve(col,row));
	printf("%d\n",ans);
	return 0;
}
